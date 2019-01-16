//
//  Components.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "components.hpp"

namespace components {

void Transform::Translate(int amt_x, int amt_y) {
    
    position_.x += amt_x;
    position_.y += amt_y;
    has_moved_ = true;
}
    
void Transform::Translate(Vector2 amount) {
    
    position_ += amount;
    has_moved_ = true;
}

} // Namespace components
