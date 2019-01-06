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
    
    pos_x_ += amt_x;
    pos_y_ += amt_y;
    do_collision_check = true;
    
}

} // Namespace components
