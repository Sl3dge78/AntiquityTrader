//
//  World.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef World_h
#define World_h

#include <vector>

#include "Entity.h"
#include "Component.h"
#include "System.h"

namespace ECS
{

    class World {
    public:
        World();
        ~World();
        
        //Static Init
        //static void Init();
        
        //Loop
        void Update();
        
        //Entities
        static int getEntityID();
        
        //TODO : CHANGE SYNTAX TO CREATE
        Entity * AddEntity();
        void DeleteAllEntities();
        
        //Systems
        template <class T, class...Args>
        T * AddSystem(Args&&...args);
        void DeleteAllSystems();

    private:
        std::vector<Entity *> entityList;
        std::vector<System *> systemsList;
        
        //static int ENTITYID;
        
    };

    //SYSTEMS
    template <class T, class...Args>
    T * World::AddSystem(Args&&...args){
        T * sys = new T{std::forward<Args>(args)...};
        systemsList.push_back(sys);
        return sys;
    }

}
#endif /* World_hpp */
