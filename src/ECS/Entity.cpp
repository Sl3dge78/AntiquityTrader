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

Entity::~Entity() {
    this->Entity::RemoveAllComponents();
}

void Entity::RemoveAllComponents() {
    for (auto pair : components_) {
        delete pair.second;
    }
    components_.clear();
}

Component* Entity::AddComponent(const int id, Component* comp) {
    components_[id] = comp;
    return comp;
}

bool Entity::HasComponent(const int id) const {
    return (components_.find(id) != components_.end()) ;
}

Component* Entity::GetComponent(const int id) const {
    if (HasComponent(id))
    {
        return components_.at(id);
    }
    else
        return nullptr;
}

void Entity::RemoveComponent(const int id) {
    if(HasComponent(id))
    {
        delete components_[id];
        components_.erase(id);
    }
}
}
