//
//  UIManager.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 28/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "UISystem.hpp"

namespace systems {
void UISystem::Draw()
{
    std::vector<ECS::Entity * > entities;
    GetActiveEntities(&entities);
    
    for(auto&& e : entities)
    {
        components::UIPanel * panel = e->GetComponent<components::UIPanel>();
        if(panel)
        {
            al_draw_filled_rectangle(panel->rect_.x, panel->rect_.y, panel->rect_.width+panel->rect_.x, panel->rect_.height+panel->rect_.y, panel->color_);
        }
        components::UIText * text = e->GetComponent<components::UIText>();
        if(text)
        {
            al_draw_multiline_text(font, text->color_, text->rect_.x, text->rect_.y, text->rect_.width, al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, text->text_.c_str());
        }
    }
}
} // Namespace systems
