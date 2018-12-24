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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../ECS/ECS.hpp"
#include "../Rect.hpp"

struct UIPanel : public ECS::Component
{
    //Screenspace rect where to draw the panel;
    Rect rect;
    ALLEGRO_COLOR color;
    
    friend struct UIRenderer;
};

struct UIRenderer : public ECS::System
{
public:
    void Draw();
};

#endif /* UI_hpp */
