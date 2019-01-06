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

namespace components {

struct FontRenderer : public ECS::Component {
    FontRenderer(const char text = 'x', const ALLEGRO_COLOR color = al_map_rgb(255, 255, 255))
      : color_(color) {
        this->text_[0] = text;
    };
    ~FontRenderer() = default;
    
    ALLEGRO_COLOR const     color_;
    char text_[2] =         {'\0','\0'};
};

struct Transform : public ECS::Component {
  public:
    Transform(const int posX = 0, const int posY = 0) :
    pos_x_(posX),
    pos_y_(posY)
    {
        parent_ = nullptr;
    };
    ~Transform() = default;
    
    // Positions
    int pos_x_;
    int pos_y_;
    int GetPositionID() const { return (pos_x_ + (pos_y_ * 500)); };
    
    //Children management
    void                        SetParent(ECS::Entity* parent);
    std::vector<ECS::Entity*>   GetChildren() const;
    void                        AddChildren(ECS::Entity* child);
    void                        RemoveChildren(ECS::Entity* child);
    void                        RemoveAllChildren();
    
  protected:
    ECS::Entity* parent_;
    std::vector<ECS::Entity*> childs_;
};

/*
 * ==== MAP ====
 */

enum TileType { TILE_WATER = 0, TILE_LAND = 1, TILE_TOWN = 2 , TILE_COAST = 3}; //DONT FORGET TO UPDATE THE TILE LIST

struct Tile {
    ALLEGRO_COLOR   color_;
    char            character_;
};

struct Map : public ECS::Component {
  public :
    Map() = default;
    ~Map() { delete [] map; }
    
    int             width_;
    int             height_;
    TileType*       map = NULL;
    ALLEGRO_FONT *  font;
};

class Town : public ECS::Component {
  public :
    Town(int position, std::string name) : position_(position), name_(name), ui_string_(name) {} ;
    ~Town() = default;
    
    void            SetName(std::string name);
    std::string     GetUIString() const;
    int             GetPosition() const {return position_;}
    
  private :
    std::string     ui_string_;
    std::string     name_;
    int             position_;
};

struct Collider : ECS::Component {
    TileType        below_tile_; //tile type below the entity
};

struct Player : ECS::Component {
    // TODO : Add current town, etc
};
    
/*
 *  === UI ===
 */
struct UIElement : public ECS::Component {
    Rect            rect_;
    ALLEGRO_COLOR   color_ = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 1, .a = 1};
};

struct UIPanel : public UIElement {};

struct UIText : public UIElement {
    std::string text_;
};
    
} // Namespace
#endif /* Components_hpp */
