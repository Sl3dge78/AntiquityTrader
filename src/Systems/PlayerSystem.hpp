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

    class PlayerSystem : public ECS::ISystem, public ECS::InputSystem, public ECS::UpdateSystem, public ECS::WorldSetSystem, public ECS::InitSystem {
  public :
    void Init();
    void Input(ALLEGRO_EVENT* const ev);
    void Update();
    
  protected:
    void Interact();
    void OnEscPress();
    
    void ToggleInventory();
    void CreateInventory();
    void DestroyInventory();
    
    bool is_in_town_ = false;
    ECS::Entity* player_;
    ECS::Entity* ui_money_;
    
};
    
class InventorySystem : public ECS::ISystem, public ECS::UpdateSystem {
  public:
    InventorySystem();
    void Update();
    static void TransferMoney(ECS::Entity* from, ECS::Entity* to, int amount);
};
    
} // Namespace systems
#endif /* PlayerSystem_hpp */
