//
//  InputSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "PlayerSystem.hpp"

namespace systems {
    
void PlayerSystem::Init() {
    using namespace components;
    
    player_ = world_->CreateEntity();
    player_->AddComponent<Transform>(220,45);
    player_->AddComponent<Rigidbody>();
    player_->AddComponent<Collider>(COLLIDER_FLAG_PLAYER);
    player_->AddComponent<TileSetRenderer>(Tile::GetVector2FromTileType(TILE_PLAYER), 0);
    auto comp = player_->AddComponent<Player>();
    
    auto inventory = world_->CreateEntity();
    comp->inventory_ = inventory->AddComponent<Inventory>();
    comp->inventory_->is_dirty_ = true;
    
    ui_money_ = world_->CreateEntity();
    auto txt = ui_money_->AddComponent<UIText>();
    txt->rect_.x = 8;
    txt->rect_.y = 4;
    txt->rect_.width = constants::kWindowWidth;
    
    auto blck_bar = world_->CreateEntity();
    auto pnl = blck_bar->AddComponent<UIPanel>();
    pnl->rect_.width = constants::kWindowWidth;
    pnl->rect_.height = 16;
    pnl->color_ = al_map_rgb(0, 0, 0);
}

void PlayerSystem::Input(ALLEGRO_EVENT* const ev) {
    if(is_active_) {
        components::Rigidbody* rigidbody = player_->GetComponent<components::Rigidbody>();
        
        if (ev->type == ALLEGRO_EVENT_KEY_CHAR) {
            if(!player_->GetComponent<components::Player>()->is_in_town_) {
                Vector2 movement;
                switch (ev->keyboard.keycode) {
                    case ALLEGRO_KEY_W:
                        movement.y = -1;
                        break;
                        
                    case ALLEGRO_KEY_S:
                        movement.y = 1;
                        break;
                        
                    case ALLEGRO_KEY_D:
                        movement.x = 1;
                        break;
                        
                    case ALLEGRO_KEY_A:
                        movement.x = -1;
                        break;
                    
                    case ALLEGRO_KEY_SPACE : {
                        player_->GetComponent<components::Player>()->inventory_->AddMoney(100000);
                        break;
                    }
                    default:
                        break;
                }
                rigidbody->Move(movement);
            }
        } else if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev->keyboard.keycode) {
                case ALLEGRO_KEY_ENTER:
                    PlayerSystem::Interact();
                    break;
                
                case ALLEGRO_KEY_ESCAPE:
                    PlayerSystem::OnEscPress();
                    break;
                    
                case ALLEGRO_KEY_I:
                    PlayerSystem::ToggleInventory();
                    
                default:
                    break;
            }
        }
    }
}

void PlayerSystem::Interact() {

    //Town interaction
    if (player_->GetComponent<components::Collider>()->colliding_flag_ == components::COLLIDER_FLAG_TOWN)
    {
        components::Player* p_comp = player_->GetComponent<components::Player>();
        if(!p_comp->is_in_town_) {
            p_comp->is_in_town_ = true;
            p_comp->current_town_ = player_->GetComponent<components::Collider>()->colliding_entity_->GetComponent<components::Town>();
            p_comp->current_town_->is_player_in_ = true;
        }
    }
}
    
void PlayerSystem::OnEscPress() {
    components::Player* p_comp = player_->GetComponent<components::Player>();
    if(p_comp->is_in_town_) {
        p_comp->is_in_town_ = false;
        p_comp->current_town_->is_player_in_ = false;
        p_comp->current_town_ = nullptr;
    }
}

void PlayerSystem::Update() {
    //Update UI
    if (player_->GetComponent<components::Player>()->inventory_->is_dirty_) {
        ui_money_->GetComponent<components::UIText>()->text_ = "Money: " + std::to_string(player_->GetComponent<components::Player>()->inventory_->money_) + "$";
        player_->GetComponent<components::Player>()->inventory_->is_dirty_ = false; 
    }
}

void PlayerSystem::ToggleInventory() {
    if (!player_->GetComponent<components::Player>()->inventory_ui_) {
        CreateInventory();
    } else {
        DestroyInventory();
    }
}

void PlayerSystem::CreateInventory() {
    player_->GetComponent<components::Player>()->inventory_ui_ = world_->CreateEntity();
    auto inventory_ui = player_->GetComponent<components::Player>()->inventory_ui_;
    player_->AddChildren(inventory_ui);
    auto border = inventory_ui->AddComponent<components::UIPanel>();
    border->rect_.x = 0;
    border->rect_.width = constants::kWindowWidth / 3;
    border->rect_.height = constants::kWindowHeight;
    border->color_ = al_map_rgba(0, 0, 0, 255);
    
    auto txt = inventory_ui->AddComponent<components::UIText>();
    txt->text_ = "=== INVENTORY ===\n";
    txt->rect_ = border->rect_;
    txt->rect_.x += constants::kTileWidth;
    txt->rect_.y += constants::kTileHeight;
    
    Rect position = Rect{.x = txt->rect_.x, .y = txt->rect_.y + constants::kTileHeight + 1, .width = border->rect_.width, .height = border->rect_.height};
    auto inventory_contents = player_->GetComponent<components::Player>()->inventory_->inventory_;
    if (inventory_contents.size() > 0) {
        for (auto& item : inventory_contents) {
            if (item.second > 0) { // If there are any items in this category
                auto item_entity = world_->CreateEntity();
                item_entity->order_ = -1;
                inventory_ui->AddChildren(item_entity);
                
                item_entity->AddComponent<components::InventoryObject>(components::kInventoryObjectList[item.first]);
                
                auto text = item_entity->AddComponent<components::UIText>();
                text->rect_ = position;
                text->text_ = std::to_string(item.second) + " " + components::kInventoryObjectList[item.first].name_;
                position.y += constants::kTileHeight + 1;
            }
        }
    } else {
        auto inventory_empty_label = world_->CreateEntity();
        inventory_empty_label->order_ = -1;
        inventory_ui->AddChildren(inventory_empty_label);
        auto text = inventory_empty_label->AddComponent<components::UIText>();
        text->rect_ = position;
        text->text_ = "Inventory is empty!";
    }
    
    inventory_ui->SetIsActive(true);
}

void PlayerSystem::DestroyInventory() {
    world_->DeleteEntity(player_->GetComponent<components::Player>()->inventory_ui_);
    player_->GetComponent<components::Player>()->inventory_ui_ = nullptr;
}
    
// === INVENTORY MANAGEMENT == //
    
InventorySystem::InventorySystem() {
    this->AddComponentFilter<components::Inventory>();
}
    

void InventorySystem::Update() {
    
}
    
void InventorySystem::TransferMoney(ECS::Entity* from, ECS::Entity* to, int amount) {
    if (!from->HasComponent<components::Inventory>() || !to->HasComponent<components::Inventory>()) {
        throw std::invalid_argument("Entity that you are transferring to or from doesn't have an inventory");
    }
    
    if (from) {
        from->GetComponent<components::Inventory>()->money_ -= amount;
        from->GetComponent<components::Inventory>()->is_dirty_ = true;
    }
    to->GetComponent<components::Inventory>()->money_ += amount;
    to->GetComponent<components::Inventory>()->is_dirty_ = true;
}
    
    
    
    
} // Namespace systems
