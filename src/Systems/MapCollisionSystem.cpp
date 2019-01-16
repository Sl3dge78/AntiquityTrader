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
    this->AddComponentFilter<components::Rigidbody>();
    this->AddComponentFilter<components::Map>();
    this->filter_type_ = ECS::FILTER_OR;
}

void MapCollisionSystem::OnEntityListChanged() {
    for(auto& e : entities_) {
        if (e->HasComponent<components::Map>()) {
            map_ = e->GetComponent<components::Map>();
            entities_.remove(e);
        }
    }
}

void MapCollisionSystem::Update()
{
    for(auto& e : entities_) {
        auto transform = e->GetComponent<components::Transform>();
        auto rigidbody = e->GetComponent<components::Rigidbody>();
        if (rigidbody->GetCollisionCheck()) {
            Vector2 sum = transform->GetPosition() + rigidbody->GetMovement();
            components::TileType tile = map_->GetTileAtPosition(sum);
            if (tile != components::TILE_LAND && tile != components::TILE_COAST) {
                transform->Translate(rigidbody->GetMovement());
            }
            rigidbody->MovementDone();
        }
    }
}
} // Namespace systems
