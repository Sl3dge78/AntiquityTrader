//
//  UI.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 24/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "UI.hpp"

void UIRenderer::Draw()
{
    auto entities = GetEntities();
    for(auto&& e : entities)
    {
        UIPanel * panel = e->GetComponent<UIPanel>();
        if(!panel)
            continue;
        
        al_draw_filled_rectangle(panel->rect.x, panel->rect.y, panel->rect.width+panel->rect.x, panel->rect.height+panel->rect.y, panel->color);
        
    }
    
    
}
