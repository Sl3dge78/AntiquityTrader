//
//  MapCollisionSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "MapCollisionSystem.hpp"

namespace systems {

MapCollisionSystem::MapCollisionSystem() {
    this->AddComponentFilter<components::Collider>();
    this->AddComponentFilter<components::Map>();
    this->filter_type_ = ECS::FILTER_OR;
}

void MapCollisionSystem::OnEntityListChanged() {
    for(auto& e : entities_) {
        if (e->HasComponent<components::Map>()) {
            map_ = e->GetComponent<components::Map>();
            entities_.remove(e);
            break;
        }
    }
}

void MapCollisionSystem::Update()
{
    for(auto& e : entities_) {
        if (e->HasComponent<components::Collider>()) {
            auto col = e->GetComponent<components::Collider>();
            auto transform = e->GetComponent<components::Transform>();
            
            col->below_tile_ = map_->map[transform->pos_y_ * map_->width_ + transform->pos_x_];
        }
    }
    
}
} // Namespace systems
