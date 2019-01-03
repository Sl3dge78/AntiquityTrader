//
//  Entity.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Entity.hpp"

namespace ECS
{

    Entity::Entity(World *world, int id) {
        this->world = world;
        this->ID = id;
    }

    Entity::~Entity() {
        this->Entity::RemoveAllComponents();
    }

    void Entity::RemoveAllComponents(){
        components.clear();
    }
    
    Component * Entity::AddComponent(int id, Component * comp)
    {
        components[id] = comp;
        return comp;
    }
    
    bool Entity::HasComponent(int id) {
        return (components.find(id) != components.end()) ;
    }
    
    Component * Entity::GetComponent(int id) {
        if (HasComponent(id))
        {
            return components.at(id);
        }
        else
            return nullptr;
    }
    
    void Entity::RemoveComponent(int id)
    {
        if(HasComponent(id))
        {
            components.erase(id);
        }
    }
}
