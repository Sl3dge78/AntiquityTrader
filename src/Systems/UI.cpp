//
//  townUI.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#include "UI.hpp"
namespace systems {

UIDraw::UIDraw() {
    this->AddComponentFilter<components::UIText>();
    this->AddComponentFilter<components::UIPanel>();
    this->SetFilterType(ECS::FILTER_OR);
    this->pos_z = -5;
}

void UIDraw::OnEntityListChanged() {
    entities_.sort([](const ECS::Entity* e1, const ECS::Entity* e2)
    {
        return e1->order_ > e2->order_;
    });
}

void UIDraw::Draw() {
    for (auto& e : entities_) {
        if (e->GetIsActive()) {
            if (e->HasComponent<components::UIPanel>()) {
                auto comp = e->GetComponent<components::UIPanel>();
                ALLEGRO_COLOR color;
                if (e->HasComponent<components::UISelectable>()) {
                    color = e->GetComponent<components::UISelectable>()->GetColor();
                } else {
                    color = comp->GetColor();
                }
                
                al_draw_filled_rectangle(comp->rect_.x, comp->rect_.y, comp->rect_.x + comp->rect_.width, comp->rect_.y + comp->rect_.height, color);
            }
            
            if (e->HasComponent<components::UIText>()) {
                auto comp = e->GetComponent<components::UIText>();
                
                ALLEGRO_COLOR color;
                if (e->HasComponent<components::UISelectable>()) {
                    color = e->GetComponent<components::UISelectable>()->GetColor();
                } else {
                    color = comp->GetColor();
                }
                
                al_draw_multiline_text(font_, color, comp->rect_.x, comp->rect_.y, comp->rect_.width, constants::kTileHeight + 1, ALLEGRO_ALIGN_LEFT, comp->text_.c_str());
            }
        }
    }
}
    
UIInput::UIInput() {
    this->AddComponentFilter<components::UISelectable>();
}
    
void UIInput::Input(ALLEGRO_EVENT *const ev) {
    if(ev->type == ALLEGRO_EVENT_KEY_DOWN) {
    for (auto& e : entities_) {
        auto comp = e->GetComponent<components::UISelectable>();
        if (e->GetIsActive() && comp->has_focus){
            switch (ev->keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    if (comp->above_) {
                        comp->has_focus = false;
                        comp->above_->GetComponent<components::UISelectable>()->has_focus = true;
                    }
                    break;
                    
                case ALLEGRO_KEY_S:
                    if (comp->below_) {
                        comp->has_focus = false;
                        comp->below_->GetComponent<components::UISelectable>()->has_focus = true;
                    }
                    break;
                
                case ALLEGRO_KEY_Q:
                    if (comp->left_) {
                        comp->has_focus = false;
                        comp->left_->GetComponent<components::UISelectable>()->has_focus = true;
                    }
                    break;
                    
                case ALLEGRO_KEY_D:
                    if (comp->right_) {
                        comp->has_focus = false;
                        comp->right_->GetComponent<components::UISelectable>()->has_focus = true;
                    }
                    break;
                    
                case ALLEGRO_KEY_E:
                case ALLEGRO_KEY_ENTER:
                    if (comp->callback_)
                        comp->callback_(e);
                    break;
            }
        }
    }
    }
}

}// Namespace systems
