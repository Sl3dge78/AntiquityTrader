//
//  TownSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 29/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "MapSystem.hpp"

using namespace std;
using namespace components;

namespace systems {
Tile TILES_LIST[4] = {
    TILES_LIST[TILE_WATER] = (Tile){.color_ = (ALLEGRO_COLOR){.r = 0.33, .g = 0.50, .b = 1, .a = 1}, .character_ = '~'},
    TILES_LIST[TILE_LAND] = (Tile){.color_ = (ALLEGRO_COLOR){.r = 0.04, .g = 0.64, .b = 0, .a = 1}, .character_ = 'M'},
    TILES_LIST[TILE_TOWN] = (Tile){.color_ = (ALLEGRO_COLOR){.r = 1, .g = 0, .b = 0, .a = 1}, .character_ = 'T'},
    TILES_LIST[TILE_COAST] = (Tile){.color_ = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 0, .a = 1}, .character_ = 'w'},
};

void MapSystem::Init() {
   
    // Creates the map entity
    map_entity_ = world_->CreateEntity();
    Map* mapComponent = map_entity_->AddComponent<Map>();
    map_entity_->AddComponent<Transform>();
   
    // Reads the map file
    fstream file;
    file.open(constants::kMapFile, ios::in);
    if(!file.is_open())
        throw std::runtime_error("Error : Unable to open map file");
    
    // The first two lines are the map's width and height
    string rows, lines;
    getline (file,rows);
    getline (file,lines);
    mapComponent->width_ = std::stoi(rows);
    mapComponent->height_ = std::stoi(lines);
    
    // Reads the contents of the map file ommiting \n
    mapComponent->map = new TileType[mapComponent->width_ * mapComponent->height_];
    int currentPos = 0;
    char ch;
    
    while (EOF != (ch = file.get())) {
        if(ch != '\n') {
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
    file.close(); // Map file
    
    // READ THE TOWN FILE
    ALLEGRO_CONFIG* townFile = al_load_config_file(constants::kTownFile);
    ALLEGRO_CONFIG_SECTION* it;
    auto sec = al_get_first_config_section(townFile, &it);
    
    while(it) {
        auto town = world_->CreateEntity();
        int position = std::stoi(al_get_config_value(townFile, sec, "PosX")) + std::stoi(al_get_config_value(townFile, sec, "PosY")) * mapComponent->width_;
        string name = al_get_config_value(townFile, sec, "Name");
        
        town->AddComponent<components::Town>(position, name);
        town_entities_.push_back(town);
        
        mapComponent->map[position] = TileType::TILE_TOWN;
        
        sec = al_get_next_config_section(&it);
    }
}

void MapSystem::Draw()
{
    Rect clipRect = CameraSystem::GetClipRect();
    
    auto map = map_entity_->GetComponent<components::Map>();
    
    // the map's transform serves as an offset
    auto trsfm = map_entity_->GetComponent<components::Transform>();
    int offX = 0, offY = 0;
    if(trsfm)
    {
        offX = trsfm->pos_x_;
        offY = trsfm->pos_y_;
    }
    
    //Draw each tile
    for (int y = 0; y < constants::kAmoutOfTilesOnScreenY; y++)
    {
        for (int x = 0; x < constants::kAmoutOfTilesOnScreenX; x++)
        {
            //Tile tile = map->map[y*map->width+x];
            
            int id = (y+clipRect.y)*map->width_+x+clipRect.x;
            
            Tile tile = TILES_LIST[map->map[id]];
            
            al_draw_text(font_,
                         tile.color_,
                         (offX + x)* constants::kTileWidth,
                         (offY + y) * constants::kTileHeight,
                         ALLEGRO_ALIGN_LEFT,
                         &tile.character_);
            
        }
    }
}
/*
ECS::Entity * MapSystem::GetTownAtPosition(int x, int y) {
    //TODO return town entity at position x & y;
    auto mapComp = mapEntity->GetComponent<components::Map>();
    int position = x + (y * mapComp->width);
    
    for(auto&& town : townEntities)
    {
        auto comp = town->GetComponent<components::Town>();
        if(comp->GetPosition() == position)
        {
            return town;
        }
    }
    
    return nullptr;
}
*/

} // Namespace systems
