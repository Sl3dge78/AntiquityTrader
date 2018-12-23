//
//  InputSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "PlayerInputSystem.hpp"


PlayerInputSystem::PlayerInputSystem()
{}

void PlayerInputSystem::Update(ALLEGRO_EVENT * ev)
{
    if(isActive)
    {
        for(auto&& e : m_entities)
        {
            Component_Transform * transform = e->GetComponent<Component_Transform>();
            
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
            }
            
            /*
            if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
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
            }*/
        }
    }
}
