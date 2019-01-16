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
    player_->AddComponent<Player>();
    player_->AddComponent<Inventory>();
    player_->AddComponent<MoneyPurse>();
}

void PlayerSystem::Input(ALLEGRO_EVENT* const ev) {
    if(is_active_)
    {
        components::Rigidbody* rigidbody = player_->GetComponent<components::Rigidbody>();
        
        if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
        {
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
                        
                    case ALLEGRO_KEY_ENTER : {
                        player_->GetComponent<components::MoneyPurse>()->amount_ += 10;
                        break;
                    }
                    
                    case ALLEGRO_KEY_SPACE : {
                        int* p = &(player_->GetComponent<components::MoneyPurse>()->amount_);
                        *p -= 10;
                        if (*p < 0) {
                            *p = 0;
                        }
                        break;
                    }
                    default:
                        break;
                }
                rigidbody->Move(movement);
            }
        } else if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev->keyboard.keycode) {
                case ALLEGRO_KEY_ENTER:
                    PlayerSystem::Interact();
                    
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
        if(p_comp->is_in_town_) {
            p_comp->is_in_town_ = false;
            p_comp->current_town_->is_player_in_ = false;
            p_comp->current_town_ = nullptr;
            
        } else {
            p_comp->is_in_town_ = true;
            p_comp->current_town_ = player_->GetComponent<components::Collider>()->colliding_entity_->GetComponent<components::Town>();
            p_comp->current_town_->is_player_in_ = true;
        }
    }
}
} // Namespace systems
