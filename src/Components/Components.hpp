//
//  Components.h
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Components_hpp
#define Components_hpp

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "../ECS/ECS.hpp"
#include "../Rect.hpp"

class Component_FontRenderer : public ECS::Component {
public:
    Component_FontRenderer(ALLEGRO_FONT * font, char text = 'x', ALLEGRO_COLOR color = al_map_rgb(255, 255, 255)):
    font(font),
    color(color),
    text(text)
    {
        
    };
    ~Component_FontRenderer() = default;
    ALLEGRO_FONT * font;
    ALLEGRO_COLOR color;
    char text;
    
};

class Component_Transform : public ECS::Component {
public:
    Component_Transform(int posX = 0, int posY = 0) :
    posX(posX),
    posY(posY)
    {
        parent = nullptr;
    };
    ~Component_Transform() = default;
    
    int posX;
    int posY;
    
    void SetParent(ECS::Entity * parent);
    std::vector<ECS::Entity *> GetChildren();
    void AddChildren(ECS::Entity * child);
    void RemoveChildren(ECS::Entity * child);
    void RemoveAllChildren();
    
protected:
    ECS::Entity * parent;
    std::vector<ECS::Entity *> childs;
};

class Component_Follow : public ECS::Component
{
public:
    Component_Follow(ECS::Entity * target, Rect bounds) : target(target), bounds(bounds) {};
    ~Component_Follow() = default;
    ECS::Entity * target;
    Rect bounds;
};

#endif /* Components_hpp */
