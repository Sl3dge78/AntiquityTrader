//
//  MapCollisionSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef MapCollisionSystem_hpp
#define MapCollisionSystem_hpp

#include "../ECS/ECS.hpp"
#include "../Components/components.hpp"

namespace systems {
class MapCollisionSystem : public ECS::UpdateSystem {
  public :
    MapCollisionSystem();
    
    void OnEntityListChanged();
    
    void Init();
    void Update();
    
  private :
    components::Map* map_;
    
};
} // Namespace systems
#endif /* MapCollisionSystem_hpp */
