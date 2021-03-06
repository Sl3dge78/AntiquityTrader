//
//  System.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef System_h
#define System_h

#include <vector>

namespace ECS
{

    class Entity;

    class System {
        public :
            System() = default;
            virtual ~System() = 0;
            void AddEntity(Entity * e);
            void Update();
            void Draw();
            std::vector<Entity *> GetEntities();
        
        protected:
            std::vector<Entity *> m_entities;
    };
    inline System::~System() = default;

}
#endif /* System_hpp */
