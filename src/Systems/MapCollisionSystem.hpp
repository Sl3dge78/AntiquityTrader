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
class MapCollisionSystem : public ECS::UpdateSystem, public  ECS::InitSystem {
  public :
    MapCollisionSystem(ECS::Entity * map);
    
    void Init();
    void Update();
    
  private :
    components::Map* map;
    
};
} // Namespace systems
#endif /* MapCollisionSystem_hpp */
