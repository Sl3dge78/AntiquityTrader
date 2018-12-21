//
//  Map.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 21/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Map.hpp"

Tile TILES_LIST[3] = {
    TILES_LIST[Water] = (Tile){.color = (ALLEGRO_COLOR){.r = 0.33, .g = 0.33, .b = 1, .a = 1}, .character = '~'},
    TILES_LIST[Land] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 0, .a = 1}, .character = 's'},
    TILES_LIST[Town] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 1, .a = 1}, .character = 'W'},
};

Map::Map(ALLEGRO_FONT * font, int width, int height)
{
    this->width = width;
    this->height = height;
    map = new TileType[width * height];
    for(int i = 0; i < width * height; i++)
    {
        map[i] = TileType::Water;
    }
    this->font = font;
}

Map::~Map()
{
    delete [] map;
}


void MapRendererSystem::Draw()
{
    auto entities = GetEntities();
    for(ECS::Entity* entity : entities)
    {
        auto map = entity->GetComponent<Map>();
        
        // the map's transform serves as an offset
        auto trsfm = entity->GetComponent<Transform>();
        int offX = 0, offY = 0;
        if(trsfm)
        {
            offX = trsfm->posX;
            offY = trsfm->posY;
        }
        
        //Draw each tile
        for (int y = 0; y < map->height;y++)
        {
            for (int x = 0; x < map->width;x++)
            {
                Tile tile = TILES_LIST[map->map[y*map->width+x]];
                
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
