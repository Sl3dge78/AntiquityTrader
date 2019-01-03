//
//  UIManager.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../ECS/ECS.hpp"
#include "../Components/UI.hpp"

class UISystem : public ECS::System
{
    public :
    //GENERIC
    UISystem(ALLEGRO_FONT * font):font(font){};
    void Start();//Creates the UI Instances
    void Draw(); // Draws all activated UIs
    
    //TOWN
    void SetCurrentTown(ECS::Entity * town);
    void SetIsTownUIActive(bool value);
    
private:
    // GENERIC
    ALLEGRO_FONT * font;
    
    //TOWN
    ECS::Entity * townUI = nullptr;
    ECS::Entity * currentTown = nullptr;
    bool isTownUIActive = false;
    
};

#endif /* UIManager_hpp */
