//
//  UIManager.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "UISystem.hpp"

void UISystem::Draw()
{
    std::vector<ECS::Entity * > entities;
    GetActiveEntities(&entities);
    
    for(auto&& e : entities)
    {
        UIPanel * panel = e->GetComponent<UIPanel>();
        if(panel)
        {
            al_draw_filled_rectangle(panel->rect.x, panel->rect.y, panel->rect.width+panel->rect.x, panel->rect.height+panel->rect.y, panel->color);
        }
        UIText * text = e->GetComponent<UIText>();
        if(text)
        {
            al_draw_multiline_text(font, text->color, text->rect.x, text->rect.y, text->rect.width, al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, text->text.c_str());
        }
    }
}
