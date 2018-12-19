//
//  Components.h
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Components_h
#define Components_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "ECS/ECS.h"

class FontRenderer : public ECS::Component {
public:
    FontRenderer(ALLEGRO_FONT * font, char character = 'x', ALLEGRO_COLOR color = al_map_rgb(255, 255, 255)):
    font(font),
    color(color),
    character(character)
    {
        
    };
    ~FontRenderer() = default;
    ALLEGRO_FONT * font;
    ALLEGRO_COLOR color;
    char character;
    
};

class Transform : public ECS::Component {
public:
    Transform(int posX = 10, int posY = 10) :
    posX(posX),
    posY(posY)
    {
        
    };
    ~Transform() = default;
    
    int posX;
    int posY;
    
};

#endif /* Components_h */
