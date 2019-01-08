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

#include "../constants.hpp"

#include "../ECS/ECS.hpp"
#include "../types.hpp"

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

enum TileType {TILE_PLAYER = 0, TILE_LAND = 1, TILE_WATER = 2, TILE_COAST = 3, TILE_SMALL_TOWN = 4, TILE_TOWN = 5}; //DONT FORGET TO UPDATE THE TILE LIST
    
struct TileSetRenderer : public ECS::Component {
    /// pos_x and pos_y refer to positions on the tilemap. These will be multiplied by the tile height & width.
    TileSetRenderer(const Vector2 pos, const int pos_z = 10) : pos_(pos) {};
    
    Vector2 pos_;
    int pos_z_;
    
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
    bool do_collision_check = true;
    void Translate(int amt_x, int amt_y);
    int GetPosX() const { return pos_x_; };
    int GetPosY() const { return pos_y_; };
    int GetPositionID() const { return (pos_x_ + (pos_y_ * 500)); };
    
    //Children management
    void                        SetParent(ECS::Entity* parent);
    std::vector<ECS::Entity*>   GetChildren() const;
    void                        AddChildren(ECS::Entity* child);
    void                        RemoveChildren(ECS::Entity* child);
    void                        RemoveAllChildren();
    
  protected:
    int pos_x_;
    int pos_y_;
    
    ECS::Entity* parent_;
    std::vector<ECS::Entity*> childs_;
};

    
enum ColliderFlag { COLLIDER_FLAG_NONE = -1, COLLIDER_FLAG_PLAYER, COLLIDER_FLAG_TOWN };

struct Collider : ECS::Component {
    Collider (ColliderFlag flag = COLLIDER_FLAG_NONE) : flag_(flag) {};
    
    ColliderFlag    flag_;
    ECS::Entity*    colliding_entity_ = nullptr;
    ColliderFlag    colliding_flag_ = COLLIDER_FLAG_NONE;
};
    
/*
 * ==== MAP ====
 */

struct Tile {
    TileType tile_;
    
    static Vector2 GetVector2FromTileType(TileType tile) {
        switch (tile) {
            case TILE_PLAYER :      return Vector2 { .x = 0,  .y = 0 }; break;
            case TILE_LAND :        return Vector2 { .x = 1,  .y = 0 }; break;
            case TILE_WATER :       return Vector2 { .x = 2, .y = 0 }; break;
            case TILE_COAST :       return Vector2 { .x = 3, .y = 0 }; break;
            case TILE_SMALL_TOWN :  return Vector2 { .x = 0,  .y = 1 }; break;
            case TILE_TOWN :        return Vector2 { .x = 1,  .y = 1 }; break;
        }
    };
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

/*
 * == GAMEPLAY ==
 */

enum InventoryObjectType { INV_OBJECT_CHOUX, INV_OBJECT_FLEUR };
    
struct InventoryObject : public ECS::Component {
    InventoryObjectType type_;
    std::string name_;
};
    
struct Inventory : public ECS::Component {
    std::map<InventoryObjectType, int> inventory_;
};

struct MoneyPurse : public ECS::Component {
    int amount_;
};
    
struct Town : public ECS::Component {
    Town(std::string name) : name_(name) {} ;
    ~Town() = default;
    bool                  is_player_in_ = false;
    std::string           name_;
};

struct Player : public ECS::Component {
    bool is_in_town_ = false;
    Town* current_town_;
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
