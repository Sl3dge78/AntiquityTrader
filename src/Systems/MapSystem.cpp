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

void MapSystem::Init() {
   
    this->pos_z = 1;
    
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
    constants::kMapWidth = mapComponent->width_;
    constants::kMapHeight = mapComponent->height_;
    
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
                mapComponent->map[currentPos] = TileType::TILE_TOWN;
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
        
        int pos_x = std::stoi(al_get_config_value(townFile, sec, "PosX"));
        int pos_y = std::stoi(al_get_config_value(townFile, sec, "PosY"));
        string name = al_get_config_value(townFile, sec, "Name");
        
        town->AddComponent<components::Town>(name);
        town->AddComponent<components::Transform>(pos_x, pos_y);
        town->AddComponent<components::Collider>(components::COLLIDER_FLAG_TOWN);
        auto inventory = town->AddComponent<components::Inventory>();
        inventory->inventory_[INV_OBJECT_CHOUX] = 10;
        inventory->inventory_[INV_OBJECT_FLEUR] = 20;
        town_entities_.push_back(town);
        
        int position = pos_x + pos_y * mapComponent->width_;
        mapComponent->map[position] = TileType::TILE_TOWN;
        
        sec = al_get_next_config_section(&it);
    }
    al_destroy_config(townFile);
}

void MapSystem::Draw()
{
    Rect clipRect = CameraSystem::GetClipRect();
    
    auto map = map_entity_->GetComponent<components::Map>();
    
    // the map's transform serves as an offset
    auto trsfm = map_entity_->GetComponent<components::Transform>();
    int off_x = 0, off_y = 0;
    if(trsfm)
    {
        off_x = trsfm->GetPosX();
        off_y = trsfm->GetPosY();
    }
    
    //Draw each tile
    for (int y = 0; y < constants::kAmoutOfTilesOnScreenY; y++)
    {
        for (int x = 0; x < constants::kAmoutOfTilesOnScreenX; x++)
        {
            int x_map_position = off_x + x;
            int y_map_position = off_y + y;
            
            int id = (y+clipRect.y)*map->width_+x+clipRect.x;
            if(id < 0 || id > map->width_ * map->height_)
                break;
            Vector2 blit = components::Tile::GetVector2FromTileType(map->map[id]);
            
            al_draw_scaled_bitmap(bitmap_,
                                  blit.x * constants::kFileTileWidth,
                                  blit.y * constants::kFileTileHeight,
                                  constants::kFileTileWidth,
                                  constants::kFileTileHeight,
                                  
                                  x_map_position * constants::kTileWidth,
                                  y_map_position * constants::kTileHeight,
                                  constants::kTileWidth,
                                  constants::kTileHeight,
                                  0);
            
            /*
            al_draw_bitmap_region(bitmap_,
                                  blit.x * constants::kFileTileWidth,
                                  blit.y * constants::kFileTileHeight,
                                  constants::kTileWidth, constants::kTileHeight,
                                  x_map_position * constants::kTileWidth,
                                  y_map_position * constants::kTileHeight,
                                  0);
            /*
            //Tile tile = TILES_LIST[map->map[id]];
             al_draw_text(font_,
                         tile.color_,
                         (offX + x)* constants::kTileWidth,
                         (offY + y) * constants::kTileHeight,
                         ALLEGRO_ALIGN_LEFT,
                         &tile.character_);
             */
            
        }
    }
}
    
} // Namespace systems
