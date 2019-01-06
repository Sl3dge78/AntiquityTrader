//
//  TownSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 29/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef TownSystem_hpp
#define TownSystem_hpp

#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "../constants.hpp"

#include "../ECS/ECS.hpp"
#include "../Components/components.hpp"

#include "RenderingSystems.hpp"

namespace systems {
class MapSystem : public ECS::DrawSystem, public ECS::WorldSetSystem, public ECS::InitSystem {
  public:
    MapSystem(ALLEGRO_FONT* font){ font_ = font; };
    
    void Init();
    void Draw();
    
    ECS::Entity* map_entity_ = nullptr;
    
  private:
    std::vector<ECS::Entity*> town_entities_;
    
};

} // Namespace systems
#endif /* TownSystem_hpp */
