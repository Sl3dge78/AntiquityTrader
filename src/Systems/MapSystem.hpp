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

#include "../ECS/ECS.hpp"
#include "../Components/Component_Map.hpp"

class MapSystem : public ECS::System
{
public:
    MapSystem(ALLEGRO_FONT * font, std::string mapFileName, std::string townFileName, ECS::World * world);
    ~MapSystem();
    void Draw(const Rect clipRect);
    
    ECS::Entity * mapEntity;
    
    ECS::Entity * GetTownAtPosition(int x, int y);
    
    
private:
    ALLEGRO_FONT * font;
    std::vector<ECS::Entity *> townEntities;
    
    
    
};


#endif /* TownSystem_hpp */
