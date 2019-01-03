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
#include "../Components/Component_Map.hpp"

class MapCollisionSystem : public ECS::System
{
    public :
    MapCollisionSystem(ECS::Entity * map);
    void Update();
    
    private :
    Component_Map * map;
    
};

#endif /* MapCollisionSystem_hpp */
