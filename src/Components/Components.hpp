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
    Component_FontRenderer(ALLEGRO_FONT * font, char text = 'x', ALLEGRO_COLOR color = al_map_rgb(255, 255, 255));
    ~Component_FontRenderer() = default;
    ALLEGRO_FONT * font;
    ALLEGRO_COLOR color;
    char text[2] = {'\0','\0'};;
    
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
    
    int GetPositionID();
    
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


enum TileType { TILE_WATER = 0, TILE_LAND = 1, TILE_TOWN = 2 , TILE_COAST = 3}; //DONT FORGET TO UPDATE THE TILE LIST

struct Tile {
    ALLEGRO_COLOR color;
    char character;
};


class Component_Map : public ECS::Component
{
    public :
    //MapComponent(ALLEGRO_FONT * font, int width, int height);
    //MapComponent(ALLEGRO_FONT * font, std::string fileName);
    Component_Map() = default;
    ~Component_Map() { delete [] map; }
    int width, height;
    TileType * map = NULL;
    ALLEGRO_FONT * font;
};

class Component_Town : public ECS::Component
{
    public :
    Component_Town(int position, std::string name);
    Component_Town(int position);
    ~Component_Town() = default;
    void SetName(std::string name);
    std::string GetUIString();
    
    int GetPosition(){return position;}
    
    private :
    std::string uiString;
    std::string name;
    int position;
    
    
};

struct Component_Collider : ECS::Component
{
    TileType belowTile; //tile type below the player
};

#endif /* Components_hpp */
