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
      
    private:
        int ID;
        World * world;
        //std::vector<Component *> components;
        std::map <int, Component *> components;
        
    public :
        Entity(World * world, int id);
        ~Entity();
        bool isActive = true;
        
        template <class T, class... Args> inline T *    AddComponent(Args&&... args);
        template <class T> inline bool                  HasComponent();
        template <class T> inline T *                   GetComponent();
        
        template <class T> inline void                  RemoveComponent();
        
        void RemoveAllComponents();
        //std::vector<Component *> GetAllComponents(){return components;}
        
    protected :
        Component *     AddComponent(int id, Component * comp);
        Component *     GetComponent(int id);
        bool            HasComponent(int id);
        void            RemoveComponent(int id);
    };

    //Adds a component of type T to an entity
    template <class T, class...Args>
    T * Entity::AddComponent(Args&&...args){
        return static_cast<T *>( AddComponent(ComponentID::Get<T>(), new T{std::forward<Args>(args)...}) );
    }

    template <class T> bool Entity::HasComponent()
    {
        return HasComponent(ComponentID::Get<T>());
    }
    
    template <class T>
    T * Entity::GetComponent(){
        return static_cast<T *>( GetComponent(ComponentID::Get<T>()) );
    }

    //Removes a component from an entity
    template <class T>
    void Entity::RemoveComponent(){
        RemoveComponent(ComponentID::Get<T>());
        
    }
}
#endif /* Entity_hpp */
