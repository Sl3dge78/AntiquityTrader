//
//  collision.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#include "collision.hpp"

namespace systems {

Collision::Collision() {
    this->AddComponentFilter<components::Collider>();
    this->AddComponentFilter<components::Transform>();
    this->SetFilterType(ECS::FILTER_AND);
}

void Collision::Update() {
    // TODO : Call this only when needed
    
    std::forward_list<ECS::Entity*> test_list;
    for (auto& e : entities_) {
        if (e->GetComponent<components::Transform>()->has_moved_)
            test_list.push_front(e);
    }
    
    for (auto& e1 : test_list) {
        bool changed = false;
        for (auto& e2 : test_list) {
            if (e1 == e2)
                continue;
            if (e1->GetComponent<components::Transform>()->GetPosX() == e2->GetComponent<components::Transform>()->GetPosX() &&
                e1->GetComponent<components::Transform>()->GetPosY() == e2->GetComponent<components::Transform>()->GetPosY()) {
                auto e1col = e1->GetComponent<components::Collider>();
                auto e2col = e2->GetComponent<components::Collider>();
                
                e1col->colliding_entity_ = e2;
                e1col->colliding_flag_ = e2col->flag_;
                
                e2col->colliding_entity_ = e1;
                e2col->colliding_flag_ = e1col->flag_;
                test_list.remove(e1);
                test_list.remove(e2);
                changed = true;
                continue;
            }
            e2->GetComponent<components::Collider>()->colliding_entity_ = nullptr;
            e2->GetComponent<components::Collider>()->colliding_flag_ = components::COLLIDER_FLAG_NONE;
        }
        if(changed) continue;
        e1->GetComponent<components::Collider>()->colliding_entity_ = nullptr;
        e1->GetComponent<components::Collider>()->colliding_flag_ = components::COLLIDER_FLAG_NONE;
    }
}
    
} // Namespace systems
