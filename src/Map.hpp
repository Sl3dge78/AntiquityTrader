//
//  Map.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 21/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Macros.hpp"

#include "ECS/ECS.hpp"
#include "Components.hpp"

enum TileType { Water = 0, Land = 1, Town = 2 }; //DONT FORGET TO UPDATE THE TILE LIST BELOW

struct Tile {
    ALLEGRO_COLOR color;
    char character;
};




class Map : public ECS::Component
{
    public :
    Map(ALLEGRO_FONT * font, int width, int height);
    ~Map();
    int width, height;
    TileType * map = NULL;
    ALLEGRO_FONT * font;
    //tiles[Water] = Tile{al_map_rgb(100,100,255)}
    
};

struct MapRendererSystem : public ECS::System
{
public:
    void Draw();
};

#endif /* Map_hpp */
