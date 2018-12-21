//
//  RendererSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//
#include "RenderingSystems.hpp"

void ObjectRendererSystem::Draw() {
    
    auto entities = GetEntities();
    for(ECS::Entity* entity : entities)
    {
        auto rdr = entity->GetComponent<FontRenderer>();
        auto trfm = entity->GetComponent<Transform>();
        al_draw_text(rdr->font,
                     rdr->color,
                     trfm->Transform::posX * TILE_WIDTH,
                     trfm->Transform::posY * TILE_HEIGHT,
                     ALLEGRO_ALIGN_LEFT,
                     &(rdr->text));
        
    }
}


