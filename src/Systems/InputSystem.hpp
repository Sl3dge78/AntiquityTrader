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
#include "../Components.hpp"

class InputSystem : public ECS::System
{
    public :
    InputSystem();
    void Update(ALLEGRO_EVENT * ev);
    void ChangeCurrentFocus(ECS::Entity * e);
    
private:
    void PlayerEvents(ALLEGRO_EVENT * ev);
    void UIEvents(ALLEGRO_EVENT * ev);
    
    
    
    ECS::Entity * currentFocus;
    
};

#endif /* InputSystem_hpp */
