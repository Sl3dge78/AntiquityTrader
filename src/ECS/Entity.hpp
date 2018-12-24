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

#include "Component.hpp"

namespace ECS
{
    class World;

    class Entity {
      
    private:
        int ID;
        World * world;
        std::vector<Component *> components;
        
        
    public :
        Entity(World * world, int id);
        ~Entity();
        
        template <class T, class... Args>
        T * AddComponent(Args&&... args);
        
        template <class T>
        T * GetComponent();
        
        template <class T>
        void RemoveComponent();
        
        void RemoveAllComponents();
        
    };

    //Adds a component of type T to an entity
    template <class T, class...Args>
    T * Entity::AddComponent(Args&&...args){
        T * comp = new T{std::forward<Args>(args)...};
        components.push_back(comp);
        comp->entity = this;
        return comp;
    }
    
    template <class T>
    T * Entity::GetComponent(){
        for (std::vector<Component *>::iterator it = components.begin() ; it != components.end(); ++it)
        {
            if(typeid(**it) == typeid(T))
            {
                return dynamic_cast<T *>(*it);
            }
        }
        return nullptr;
    }
    
    //Removes a component from an entity
    template <class T>
    void Entity::RemoveComponent(){
        for (std::vector<Component *>::iterator it = components.begin() ; it != components.end(); ++it)
        {
            if(typeid(**it) == typeid(T))
            {
                //We found the component !
                delete *it;
                components.erase(it);
                return;
            }
            continue;
        }
        
        //Unable to find component, throw error
        throw std::invalid_argument(std::string("No component of type %s found !",typeid(T).name()));
    }
}
#endif /* Entity_hpp */
