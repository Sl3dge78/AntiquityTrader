//
//  RendererSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef RendererSystem_hpp
#define RendererSystem_hpp

//#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Macros.hpp"

#include "../ECS/ECS.hpp"
#include "Components.hpp"

class RendererSystem : public ECS::System
{
    public :
    RendererSystem();
    ~RendererSystem();
    void Draw();
    
};

#endif /* RendererSystem_hpp */
