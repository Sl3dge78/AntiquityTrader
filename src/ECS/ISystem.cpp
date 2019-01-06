//
//  System.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "ISystem.hpp"
namespace ECS
{

void ISystem::AddEntity(Entity* e) {
    entities_.push_front(e);
    OnEntityAdded(e);
}

//Go through all entities, and give only the ones that are activated
void const ISystem::GetActiveEntities(std::vector<Entity*> *list) {
    for(Entity* e : entities_)
    {
        if(e->GetIsActive())
            list->push_back(e);
    }
}
    
    void ISystem::AddComponentFilter(const int id) { 
        filter_.push_back(id);
    }
    
}
