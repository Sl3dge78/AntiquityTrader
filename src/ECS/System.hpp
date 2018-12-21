//
//  System.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

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
            void SetIsActive(bool val);
            bool GetIsActive();
        
        protected:
            std::vector<Entity *> m_entities;
            bool isActive = true;
        
        private:
        virtual void OnEntityAdded(Entity * entity) {}
    };
    inline System::~System() = default;

}
#endif /* System_hpp */
