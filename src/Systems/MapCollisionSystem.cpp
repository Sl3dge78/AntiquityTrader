//
//  MapCollisionSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "MapCollisionSystem.hpp"

namespace systems {

MapCollisionSystem::MapCollisionSystem(ECS::Entity *map) { 
    this->map = map->GetComponent<components::Map>();
}

void MapCollisionSystem::Init(){
    this->AddComponentFilter<components::Collider>();
}
    
void MapCollisionSystem::Update()
{
    for(auto && e : entities_)
    {
        auto col = e->GetComponent<components::Collider>();
        auto transform = e->GetComponent<components::Transform>();
        
        col->below_tile_ = map->map[transform->pos_y_ * map->width_ + transform->pos_x_];
        
    }
    
}
} // Namespace systems
