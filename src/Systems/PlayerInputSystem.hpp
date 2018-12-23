//
//  InputSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef InputSystem_hpp
#define InputSystem_hpp

#include "allegro5/allegro.h"

#include "../ECS/ECS.hpp"
#include "../Components/Components.hpp"

class PlayerInputSystem : public ECS::System
{
    public :
    PlayerInputSystem();
    void Update(ALLEGRO_EVENT * ev);
    
};

#endif /* InputSystem_hpp */
