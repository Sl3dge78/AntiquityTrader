//
//  World.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <forward_list>

#include "Entity.hpp"
#include "Component.hpp"
#include "ISystem.hpp"

namespace ECS
{

class World {
  public:
    World() = default;
    ~World();
    
    //Entities
    Entity* CreateEntity();
    void    DeleteAllEntities();
    
    //Systems
    template <class T, class...Args> T* CreateSystem(Args&&...args);
    void                                DeleteAllSystems();
    
    void Init();
    void Input(ALLEGRO_EVENT* const ev);
    void Update();
    void Draw();
    
    void UpdateSystemsEntities();
    
    void SetMainBitmap(ALLEGRO_BITMAP* bmp) { main_bitmap_ = bmp; };
    void SetMainFont(ALLEGRO_FONT* font) { main_font_ = font; };

  private:
    ALLEGRO_BITMAP* main_bitmap_;
    ALLEGRO_FONT*   main_font_;
    
    std::vector<Entity*> entity_list;
    
    //Systems
    ISystem* AddSystem(ISystem* sys);
    std::forward_list<ISystem*> systems_;
    std::forward_list<InitSystem*> init_systems_;
    std::forward_list<InputSystem*> input_systems_;
    std::forward_list<UpdateSystem*> update_systems_;
    std::forward_list<DrawSystem*> draw_systems_;
    
    bool is_systems_entities_list_dirty_ = false;
    
};

//SYSTEMS
template <class T, class...Args> T* World::CreateSystem(Args&&...args) {
    return static_cast<T*>(AddSystem(new T(std::forward<Args>(args)...)));
}

}
#endif /* World_hpp */
