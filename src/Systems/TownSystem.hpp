//
//  TownSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 07/02/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#ifndef TownSystem_hpp
#define TownSystem_hpp

#include "../constants.hpp"

#include "../ECS/ECS.hpp"
#include "../Components/components.hpp"

#endif /* TownSystem_hpp */
namespace systems {

class TownSystem : public ECS::ISystem, public ECS::WorldSetSystem, public ECS::UpdateSystem, public ECS::InitSystem {
  public:
    TownSystem();
    
    void Init();
    void Update();
    
    void OnButtonPress(ECS::Entity* caller);
    
  private:
    void CreateUI(ECS::Entity* town);
    void DestroyUI(ECS::Entity* town);
    void UpdateButton(ECS::Entity* button);
    
};
}
