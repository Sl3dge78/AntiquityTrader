//
//  InputSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "InputSystem.hpp"


InputSystem::InputSystem()
{}

void InputSystem::ChangeCurrentFocus(ECS::Entity *e)
{
    currentFocus = e;
}

void InputSystem::Update(ALLEGRO_EVENT * ev)
{
    /* PLAYER */
    if(currentFocus->GetComponent<PlayerController>() != nullptr)
    {
        PlayerEvents(ev);
        
    }
}

void InputSystem::PlayerEvents(ALLEGRO_EVENT *ev)
{
    Transform * transform = currentFocus->GetComponent<Transform>();
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
    }
}

