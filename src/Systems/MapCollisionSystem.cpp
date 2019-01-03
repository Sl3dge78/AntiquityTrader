//
//  MapCollisionSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "MapCollisionSystem.hpp"

MapCollisionSystem::MapCollisionSystem(ECS::Entity *map) { 
    this->map = map->GetComponent<Component_Map>();
}

void MapCollisionSystem::Update()
{
    for(auto && e : m_entities)
    {
        auto col = e->GetComponent<Component_Collider>();
        auto transform = e->GetComponent<Component_Transform>();
        
        col->belowTile = map->map[transform->posY * map->width + transform->posX];
        
    }
    
}
