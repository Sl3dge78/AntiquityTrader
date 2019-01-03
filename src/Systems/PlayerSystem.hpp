//
//  InputSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef PlayerSystem_hpp
#define PlayerSystem_hpp

#include "allegro5/allegro.h"

#include "../ECS/ECS.hpp"
#include "../Components/Components.hpp"
#include "../Systems/MapCollisionSystem.hpp"
#include "../Systems/UISystem.hpp"


class PlayerSystem : public ECS::System
{
    public :
    PlayerSystem(ECS::Entity * player):player(player){};
    void Update(ALLEGRO_EVENT * ev);
    
protected:
    void Interact();
    bool isInTown = false;
    ECS::Entity * m_CurrentTown = NULL;
    ECS::Entity * player;
    
};

#endif /* PlayerSystem_hpp */
