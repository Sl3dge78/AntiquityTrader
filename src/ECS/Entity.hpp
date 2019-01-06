//
//  Entity.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <utility>
#include <vector>
#include <stdexcept>
#include <string>
#include <map>

#include "Component.hpp"

namespace ECS
{
class World;

class Entity {
  
    friend class World;
    
  private:
    std::map <int, Component*> components_;
    
  public :
    Entity() = default;
    ~Entity();
    
    template <class T, class... Args> inline T*     AddComponent(Args&&... args);
    template <class T> inline bool                  HasComponent() const;
    template <class T> inline T*                    GetComponent() const;
    
    template <class T> inline void                  RemoveComponent();
    
    void                                            RemoveAllComponents();
    
    bool                                            GetIsActive() const { return is_active_;};
    
  protected :
    Component*    AddComponent(const int id, Component* comp);
    Component*    GetComponent(const int id) const;
    bool          HasComponent(const int id) const;
    void          RemoveComponent(const int id);
    bool          is_active_ = true;
};

//The following functions are user side functions for adding, getting and removing specific components
template <class T, class...Args> T * Entity::AddComponent(Args&&...args) {
    return static_cast<T*>(AddComponent(ComponentID::Get<T>(), new T{std::forward<Args>(args)...}) );
}

template <class T> bool Entity::HasComponent() const {
    return HasComponent(ComponentID::Get<T>());
}

template <class T> T* Entity::GetComponent() const {
    return static_cast<T*>(GetComponent(ComponentID::Get<T>()));
}

//Removes a component from an entity
template <class T> void Entity::RemoveComponent() {
    RemoveComponent(ComponentID::Get<T>());
}
    
}
#endif /* Entity_hpp */
