//
//  World.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "World.h"

namespace ECS
{

    World::World() {
        
    }


    World::~World() {
        DeleteAllSystems();
        DeleteAllEntities();
    }

    Entity * World::AddEntity() {
        Entity * e = new Entity(this, getEntityID());
        entityList.push_back(e);
        return e;
    }


    int World::getEntityID() {
        //TODO
        return 0;
    }




    void World::DeleteAllSystems() {
        for (std::vector<System *>::iterator it = systemsList.begin() ; it != systemsList.end(); )
        {
            delete *it;
            systemsList.erase(it);
        }
    }


    void World::DeleteAllEntities() {
        for (std::vector<Entity *>::iterator it = entityList.begin() ; it != entityList.end(); )
        {
            delete *it;
            it = entityList.erase(it);
        }
    }


    void World::Update() {
        //Add entities automatically to systems
    }
}
