//
//  TownSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 07/02/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#include "TownSystem.hpp"

namespace systems {

TownSystem::TownSystem() {
    this->AddComponentFilter<components::Town>();
}

void TownSystem::Init() {
    // READ THE TOWN FILE
    ALLEGRO_CONFIG* townFile = al_load_config_file(constants::kTownFile);
    ALLEGRO_CONFIG_SECTION* it;
    auto sec = al_get_first_config_section(townFile, &it);
    
    while(it) {
        auto town = world_->CreateEntity();
        
        int pos_x = std::stoi(al_get_config_value(townFile, sec, "PosX"));
        int pos_y = std::stoi(al_get_config_value(townFile, sec, "PosY"));
        std::string name = al_get_config_value(townFile, sec, "Name");
        
        town->AddComponent<components::Town>(name);
        town->AddComponent<components::Transform>(pos_x, pos_y);
        town->AddComponent<components::Collider>(components::COLLIDER_FLAG_TOWN);
        auto inventory = town->AddComponent<components::Inventory>();
        inventory->inventory_[components::INV_OBJECT_CHOUX] = 10;
        inventory->inventory_[components::INV_OBJECT_FLEUR] = 20;
        
        town->GetComponent<components::Town>()->inventory_ = inventory;
        
        //CreateUI(town);
        
        sec = al_get_next_config_section(&it);
    }
}

void TownSystem::Update() {
    for (auto e : entities_) {
        auto town = e->GetComponent<components::Town>();
        if (town->is_player_in_) {
            if (!town->ui_) {
                CreateUI(e);
            }
        } else if (town->ui_){
            DestroyUI(e);
            town->ui_ = nullptr;
        }
    }
}

void TownSystem::CreateUI(ECS::Entity* town) {
    
    town->GetComponent<components::Town>()->ui_ = world_->CreateEntity();
    auto town_ui = town->GetComponent<components::Town>()->ui_;
    town->AddChildren(town_ui);
    auto border = town_ui->AddComponent<components::UIPanel>();
    border->rect_.x = constants::kWindowWidth * 2 / 3;
    border->rect_.width = constants::kWindowWidth / 3;
    border->rect_.height = constants::kWindowHeight;
    border->color_ = al_map_rgba(0, 0, 0, 255);
    
    auto txt = town_ui->AddComponent<components::UIText>();
    txt->text_ = "=== " + town->GetComponent<components::Town>()->name_ + " ===\n";
    txt->rect_ = border->rect_;
    txt->rect_.x += constants::kTileWidth;
    txt->rect_.y += constants::kTileHeight;
    
    ECS::Entity* previous_entity = nullptr;
    Rect position = Rect{.x = txt->rect_.x, .y = txt->rect_.y + constants::kTileHeight + 1, .width = border->rect_.width, .height = border->rect_.height};
    
    for (auto& item : town->GetComponent<components::Inventory>()->inventory_) {
        if (item.second > 0) { // If there are any items in this cat
            auto item_entity = world_->CreateEntity();
            item_entity->order_ = -1;
            town_ui->AddChildren(item_entity);
            
            item_entity->AddComponent<components::InventoryObject>(components::kInventoryObjectList[item.first]);
            
            auto text = item_entity->AddComponent<components::UIText>();
            UpdateButton(item_entity);
            text->rect_ = position;
            
            auto button = item_entity->AddComponent<components::UISelectable>();
            button->rect_ = position;
            button->focused_color_ = al_map_rgba(255, 128, 0, 255);
            button->callback_ = std::bind(&TownSystem::OnButtonPress, this, std::placeholders::_1);
            
            button->above_ = previous_entity;
            if (previous_entity)
                previous_entity->GetComponent<components::UISelectable>()->below_ = item_entity;
            
            position.y += constants::kTileHeight + 1;
            previous_entity = item_entity;
        }
    }
    
    town_ui->SetIsActive(true);
    town_ui->GetChildren().front()->GetComponent<components::UISelectable>()->has_focus = true;
}

void TownSystem::DestroyUI(ECS::Entity* town) {
    world_->DeleteEntity(town->GetComponent<components::Town>()->ui_);
}

void TownSystem::UpdateButton(ECS::Entity* button) {
    auto text = button->GetComponent<components::UIText>();
    auto item = button->GetComponent<components::InventoryObject>();
    auto quantity = button->GetParent()->GetParent()->GetComponent<components::Inventory>()->inventory_[item->type_];
    
    text->text_ = item->name_ + " (" + std::to_string(quantity) +") "+std::to_string(item->price_)+"$";
}
    
void TownSystem::OnButtonPress(ECS::Entity* caller) {
    auto town = caller->GetParent()->GetParent();
    if (town->GetComponent<components::Town>()->is_player_in_) {
        auto player = town->GetComponent<components::Collider>()->colliding_entity_->GetComponent<components::Player>();
        auto object = caller->GetComponent<components::InventoryObject>();
        if(player->inventory_->money_ >= object->price_ && town->GetComponent<components::Inventory>()->inventory_[object->type_] > 0) {
            player->inventory_->AddMoney(- object->price_);
            player->inventory_->inventory_[object->type_]++;
            town->GetComponent<components::Inventory>()->inventory_[object->type_]--;
            UpdateButton(caller);
        } else {
            return;
        }
        
    }
}
}
