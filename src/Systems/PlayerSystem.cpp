//
//  InputSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "PlayerSystem.hpp"


void PlayerSystem::Update(ALLEGRO_EVENT * ev)
{
    if(isActive)
    {
        
        Component_Transform * transform = player->GetComponent<Component_Transform>();
        
        if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
        {
            switch (ev->keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    transform->posY --;
                    break;
                    
                case ALLEGRO_KEY_S:
                    transform->posY ++;
                    break;
                    
                case ALLEGRO_KEY_D:
                    transform->posX ++;
                    break;
                    
                case ALLEGRO_KEY_A:
                    transform->posX --;
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

void PlayerSystem::Interact()
{

    //Town interaction
    if(player->GetComponent<Component_Collider>()->belowTile == TILE_TOWN)
    {
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

