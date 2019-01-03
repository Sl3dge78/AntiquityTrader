//
//  RendererSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//
#include "RenderingSystems.hpp"

void ObjectRendererSystem::Draw(const Rect clipRect) {
    
    auto entities = GetEntities();
    for(ECS::Entity* entity : entities)
    {
        auto rdr = entity->GetComponent<Component_FontRenderer>();
        auto trfm = entity->GetComponent<Component_Transform>();
        if(trfm->posX > clipRect.x && trfm->posY > clipRect.y && trfm->posX < clipRect.x+clipRect.width && trfm->posY < clipRect.y+clipRect.height)
        {
            al_draw_text(rdr->font,
                     rdr->color,
                     (trfm->posX-clipRect.x) * TILE_WIDTH,
                     (trfm->posY-clipRect.y) * TILE_HEIGHT,
                     ALLEGRO_ALIGN_LEFT,
                     rdr->text);
        }
        
    }
}
/*
Tile TILES_LIST[4] = {
    TILES_LIST[TILE_WATER] = (Tile){.color = (ALLEGRO_COLOR){.r = 0.33, .g = 0.50, .b = 1, .a = 1}, .character = '~'},
    TILES_LIST[TILE_LAND] = (Tile){.color = (ALLEGRO_COLOR){.r = 0,04, .g = 0.64, .b = 0, .a = 1}, .character = 'M'},
    TILES_LIST[TILE_TOWN] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 1, .a = 1}, .character = 'W'},
    TILES_LIST[TILE_COAST] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 0, .a = 1}, .character = 'w'},
};

void MapRendererSystem::Draw(const Rect clipRect)
{
    auto entities = GetEntities();
    for(ECS::Entity* entity : entities)
    {
        auto map = entity->GetComponent<Component_Map>();
        
        // the map's transform serves as an offset
        auto trsfm = entity->GetComponent<Component_Transform>();
        int offX = 0, offY = 0;
        if(trsfm)
        {
            offX = trsfm->posX;
            offY = trsfm->posY;
        }
        
        //Draw each tile
        for (int y = 0; y < TILE_AMT_Y;y++)
        {
            for (int x = 0; x < TILE_AMT_X;x++)
            {
                //Tile tile = map->map[y*map->width+x];
                
                int id = (y+clipRect.y)*map->width+x+clipRect.x;
                
                Tile tile = TILES_LIST[map->map[id]];
                
                al_draw_text(map->font,
                             tile.color,
                             (offX + x)* TILE_WIDTH,
                             (offY + y) * TILE_HEIGHT,
                             ALLEGRO_ALIGN_LEFT,
                             &tile.character);
                
            }
        }
    }
}
*/
