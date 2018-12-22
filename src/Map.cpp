//
//  Map.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 21/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Map.hpp"

using namespace std;

Tile TILES_LIST[4] = {
    TILES_LIST[Water] = (Tile){.color = (ALLEGRO_COLOR){.r = 0.33, .g = 0.33, .b = 1, .a = 1}, .character = '~'},
    TILES_LIST[Land] = (Tile){.color = (ALLEGRO_COLOR){.r = 0,04, .g = 0.64, .b = 0, .a = 1}, .character = 'M'},
    TILES_LIST[Town] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 1, .a = 1}, .character = 'W'},
    TILES_LIST[Coast] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 0, .a = 1}, .character = 'w'},
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


Map::Map(ALLEGRO_FONT * font, string fileName): font(font)
{
    //Open the file
    fstream file;
    file.open(fileName, ios::in);
    if(!file.is_open())
        throw std::runtime_error("Error : Unable to open file :"+ fileName);
    
    string rows, lines;

    getline (file,rows);
    getline (file,lines);
    
    this->width = std::stoi(rows);
    this->height = std::stoi(lines);
    
    map = new TileType[this->width * this->height];
    int currentPos = 0;
    char ch;
    
    while (EOF != (ch = file.get()))
    {
        if(ch != '\n')
        {
            
            if(ch == '`')
                map[currentPos] = TileType::Water;
            else if(ch=='M')
                map[currentPos] = TileType::Land;
            else
                map[currentPos] = TileType::Coast;
            
            currentPos++;
        }
    }
    
    file.close();
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
                //Tile tile = map->map[y*map->width+x];
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
