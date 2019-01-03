//
//  TownSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 29/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "MapSystem.hpp"

using namespace std;

Tile TILES_LIST[4] = {
    TILES_LIST[TILE_WATER] = (Tile){.color = (ALLEGRO_COLOR){.r = 0.33, .g = 0.50, .b = 1, .a = 1}, .character = '~'},
    TILES_LIST[TILE_LAND] = (Tile){.color = (ALLEGRO_COLOR){.r = 0,04, .g = 0.64, .b = 0, .a = 1}, .character = 'M'},
    TILES_LIST[TILE_TOWN] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 0, .b = 0, .a = 1}, .character = 'T'},
    TILES_LIST[TILE_COAST] = (Tile){.color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 0, .a = 1}, .character = 'w'},
};


MapSystem::MapSystem(ALLEGRO_FONT * font, std::string mapFileName, std::string townFileName, ECS::World * world)
:font(font)
{
    //Open the map file
    mapEntity = world->AddEntity();
    Component_Map * mapComponent = mapEntity->AddComponent<Component_Map>();
    mapEntity->AddComponent<Component_Transform>();
    
    fstream file;
    file.open(mapFileName, ios::in);
    if(!file.is_open())
        throw std::runtime_error("Error : Unable to open file :"+ mapFileName);
    
    string rows, lines;
    
    getline (file,rows);
    getline (file,lines);
    
    mapComponent->width = std::stoi(rows);
    mapComponent->height = std::stoi(lines);
    
    mapComponent->map = new TileType[mapComponent->width * mapComponent->height];
    int currentPos = 0;
    char ch;
    
    while (EOF != (ch = file.get()))
    {
        if(ch != '\n')
        {
            
            if(ch == '`')
                mapComponent->map[currentPos] = TileType::TILE_WATER;
            else if(ch == 'M')
                mapComponent->map[currentPos] = TileType::TILE_LAND;
            else if (ch == 'T')
            {
                mapComponent->map[currentPos] = TileType::TILE_TOWN;
            }
            else
                mapComponent->map[currentPos] = TileType::TILE_COAST;
            
            currentPos++;
        }
    }
    
    file.close();
    
    // READ THE TOWN FILE
    //TODO Add all towns here. Via vector ?
    ALLEGRO_CONFIG * townFile = al_load_config_file(townFileName.c_str());
    ALLEGRO_CONFIG_SECTION * it;
    auto sec = al_get_first_config_section(townFile, &it);
    while(it)
    {
        auto town = world->AddEntity();
        int position = std::stoi(al_get_config_value(townFile, sec, "PosX")) + std::stoi(al_get_config_value(townFile, sec, "PosY")) * mapComponent->width;
        string name = al_get_config_value(townFile, sec, "Name");
        
        town->AddComponent<Component_Town>(position, name);
        townEntities.push_back(town);
        
        mapComponent->map[position] = TileType::TILE_TOWN;
        
        sec = al_get_next_config_section(&it);
    }
    
}

MapSystem::~MapSystem() {
    
}

ECS::Entity * MapSystem::GetTownAtPosition(int x, int y) {
    //TODO return town entity at position x & y;
    auto mapComp = mapEntity->GetComponent<Component_Map>();
    int position = x + (y * mapComp->width);
    
    for(auto&& town : townEntities)
    {
        auto comp = town->GetComponent<Component_Town>();
        if(comp->GetPosition() == position)
        {
            return town;
        }
    }
    
    return nullptr;
}

void MapSystem::Draw(const Rect clipRect)
{
    
    auto map = mapEntity->GetComponent<Component_Map>();
    
    // the map's transform serves as an offset
    auto trsfm = mapEntity->GetComponent<Component_Transform>();
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
            
            al_draw_text(font,
                         tile.color,
                         (offX + x)* TILE_WIDTH,
                         (offY + y) * TILE_HEIGHT,
                         ALLEGRO_ALIGN_LEFT,
                         &tile.character);
            
        }
    }
}



