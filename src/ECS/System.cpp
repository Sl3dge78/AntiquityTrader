//
//  System.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "System.hpp"
namespace ECS
{

    void System::AddEntity(Entity * e) {
        m_entities.push_back(e);
        OnEntityAdded(e);
    }


    std::vector<Entity *> System::GetEntities() { 
        return m_entities;
    }
    
    void System::GetActiveEntities(std::vector<Entity *> * list) {
        
        //GO through all entities, and give only the ones that are activated
        for(auto&& e : m_entities)
        {
            if(e->isActive)
                list->push_back(e);
        }
    }
}
