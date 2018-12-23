//
//  Map.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 21/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Macros.hpp"
#include "DebugTools.hpp"

#include "../ECS/ECS.hpp"
#include "Components.hpp"

enum TileType { Water = 0, Land = 1, Town = 2 , Coast = 3}; //DONT FORGET TO UPDATE THE TILE LIST BELOW

struct Tile {
    ALLEGRO_COLOR color;
    char character;
};


class Map : public ECS::Component
{
    public :
    Map(ALLEGRO_FONT * font, int width, int height);
    Map(ALLEGRO_FONT * font, std::string fileName);
    ~Map();
    int width, height;
    TileType * map = NULL;
    ALLEGRO_FONT * font;
    
};
#endif /* Map_hpp */
