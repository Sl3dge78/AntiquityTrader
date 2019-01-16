//
//  collision.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#ifndef collision_hpp
#define collision_hpp

#include "../ECS/ECS.hpp"
#include "../Components/components.hpp"

namespace systems {
    
class Collision : public ECS::ISystem, public ECS::UpdateSystem {
  public :
    Collision();
    void Update();
};
    
}
#endif /* collision_hpp */
