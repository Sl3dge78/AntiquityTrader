//
//  UI.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 24/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef UI_hpp
#define UI_hpp

#include <allegro5/allegro.h>

#include "../ECS/ECS.hpp"
#include "../Rect.hpp"

struct UIElement : public ECS::Component
{
    Rect rect;
    ALLEGRO_COLOR color = (ALLEGRO_COLOR){.r = 1, .g = 1, .b = 1, .a = 1};
    
    friend struct UIRenderer;
    
};

struct UIPanel : public UIElement {};

struct UIText : public UIElement
{
    std::string text;
    
    friend struct UIRenderer;
};


#endif /* UI_hpp */
