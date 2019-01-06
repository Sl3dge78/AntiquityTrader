//
//  townUI.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#ifndef townUI_hpp
#define townUI_hpp

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "../constants.hpp"

#include "../ECS/ECS.hpp"
#include "../Components/components.hpp"

namespace systems {
    
class TownUI : public ECS::DrawSystem {
  public:
    TownUI();
    
    void Draw();
    
};
    
}

#endif /* townUI_hpp */
