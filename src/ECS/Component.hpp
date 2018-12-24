//
//  Component.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

namespace ECS
{
    class Entity;
    
    class Component {
        public :
            Component() = default;
            virtual ~Component() = 0;
            Entity * GetEntity(){return this->entity;}
        
        protected :
        Entity * entity;
        
        friend class Entity;
        
    };
    
    inline Component::~Component() = default;
}
#endif /* Component_hpp */
