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

}
