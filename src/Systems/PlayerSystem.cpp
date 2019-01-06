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
    player_ = world_->CreateEntity();
    player_->AddComponent<components::Transform>(225,45);
    player_->AddComponent<components::Collider>();
    player_->AddComponent<components::FontRenderer>('@', al_map_rgb(255, 255, 255));
    player_->AddComponent<components::Player>();
}

void PlayerSystem::Input(ALLEGRO_EVENT* const ev) {
    if(is_active_)
    {
        components::Transform* transform = player_->GetComponent<components::Transform>();
        
        if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
        {
            switch (ev->keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    transform->pos_y_ --;
                    break;
                    
                case ALLEGRO_KEY_S:
                    transform->pos_y_ ++;
                    break;
                    
                case ALLEGRO_KEY_D:
                    transform->pos_x_ ++;
                    break;
                    
                case ALLEGRO_KEY_A:
                    transform->pos_x_ --;
                    break;
                    
                default:
                    break;
            }
        }else if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
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
    if(player_->GetComponent<components::Collider>()->below_tile_ == components::TILE_TOWN)
    {
        std::cout << "Zradabaldjan";
        //TODO
        if(!isInTown)
        {
            //Todo : Get town at player position
            m_CurrentTown = nullptr;
            //m_UISystem->SetCurrentTown(m_CurrentTown);
            isInTown = true;
            
        }
        else
        {
            m_CurrentTown = nullptr;
            isInTown = false;
        }
        
        //m_UISystem->SetIsTownUIActive(isInTown);
    }
}
} // Namespace systems
