//
//  Component.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Component_h
#define Component_h
namespace ECS
{
    class Component {
        public :
            virtual ~Component() = 0;
        
    };
    
    inline Component::~Component() = default;
}
#endif /* Component_hpp */
