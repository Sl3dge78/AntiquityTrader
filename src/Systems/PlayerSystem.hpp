//
//  InputSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef PlayerSystem_hpp
#define PlayerSystem_hpp

#include <iostream>

#include "allegro5/allegro.h"

#include "../constants.hpp"

#include "../ECS/ECS.hpp"
#include "../Components/components.hpp"

namespace systems {

class PlayerSystem : public ECS::InputSystem, public ECS::WorldSetSystem, public ECS::InitSystem {
  public :
    void Init();
    void Input(ALLEGRO_EVENT* const ev);
    
  protected:
    void Interact();
    bool is_in_town_ = false;
    ECS::Entity * current_town_ = NULL;
    ECS::Entity * player_;
    
};
} // Namespace systems
#endif /* PlayerSystem_hpp */
