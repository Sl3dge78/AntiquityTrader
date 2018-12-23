//
//  Systems.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 22/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Systems.hpp"

void CameraSystem::Update(Rect * clipRect)
{
    if(isActive)
    {
        for(auto&& e : m_entities)
        {
            Component_Transform * targetTransform = e->GetComponent<Component_Follow>()->target->GetComponent<Component_Transform>();
            Component_Transform * cameraTransform = e->GetComponent<Component_Transform>();
            Rect bounds = e->GetComponent<Component_Follow>()->bounds;
            
            cameraTransform->posY = targetTransform->posY;
            cameraTransform->posX = targetTransform->posX;
            
            //Test for collision
            if (cameraTransform->posX < bounds.x)
                cameraTransform->posX = bounds.x;
            else if (cameraTransform->posX > bounds.width)
                cameraTransform->posX = bounds.width;
            
            if(cameraTransform->posY < bounds.y)
                cameraTransform->posY = bounds.y;
            else if (cameraTransform->posY > bounds.height)
                cameraTransform->posY = bounds.height;
            
            if(clipRect)
            {
                clipRect->x = cameraTransform->posX - (TILE_AMT_X/2);
                clipRect->y = cameraTransform->posY - (TILE_AMT_Y/2);
                clipRect->width = TILE_AMT_X;
                clipRect->height = TILE_AMT_Y;
            }
        }
    }
}
