//
//  Systems.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 22/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Systems_hpp
#define Systems_hpp

#include "allegro5/allegro.h"
#include "../Macros.hpp"

#include "../ECS/ECS.hpp"
#include "../Components/Components.hpp"

class CameraSystem : public ECS::System
{
public:
    CameraSystem() = default;
    ~CameraSystem() = default;
    void Update(Rect * clipRect);
    
private:
    ECS::Entity * player = NULL;
};

#endif /* Systems_hpp */
