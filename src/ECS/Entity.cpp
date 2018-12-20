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

		for (std::vector<Component *>::iterator it = components.begin() ; it != components.end(); )
        {
                delete *it;
                it = components.erase(it);
        }
    }
}
