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
                //al_draw_text(font_, comp->GetColor(), comp->rect_.x, comp->rect_.y, ALLEGRO_ALIGN_LEFT, comp->text_.c_str());
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
                        comp->callback_(e); //TODO: test this
                    break;
            }
        }
    }
    }
}

//TODO : adapt below code to new architecture
    
    /*
     * == TOWN UI ==
     */
/*
TownUI::TownUI() {
    this->AddComponentFilter<components::Town>();
    this->pos_z = -1;
}

void TownUI::Input(ALLEGRO_EVENT* const ev) {
    for (auto& e : entities_) {
        if(e->GetComponent<components::Town>()->is_player_in_) {
            if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
            {
                switch (ev->keyboard.keycode) {
                    case ALLEGRO_KEY_W:
                        selection_ --;
                        if (selection_ < 0)
                            selection_ = 0;
                        break;
                        
                    case ALLEGRO_KEY_S:
                        selection_ ++;
                        if (selection_ > e->GetComponent<components::Inventory>()->inventory_.size()-1)
                            selection_ = e->GetComponent<components::Inventory>()->inventory_.size()-1;
                        break;
                    
                    case ALLEGRO_KEY_E:
                        e->GetComponent<components::Collider>()->colliding_entity_->GetComponent<components::Inventory>()->inventory_[current_selected_object_]+= 1;
                        break;
                }
            }
        }
    }
}


void TownUI::Draw() {
    for (auto& e : entities_) {
        if(e->GetComponent<components::Town>()->is_player_in_) {
            int pos_y = 0;
            // Black box
            al_draw_filled_rectangle(constants::kWindowWidth-200, 0, constants::kWindowWidth, constants::kWindowHeight, al_map_rgb(0, 0, 0));
            
            // TODO : MAKE THIS AUTOMATIC
            pos_y += 8;
            al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth-200, pos_y, ALLEGRO_ALIGN_LEFT, e->GetComponent<components::Town>()->name_.c_str());
            pos_y += 8;
            al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth-200, pos_y, ALLEGRO_ALIGN_LEFT, "Objets vendus:");
            
            int i = 0;
            for (auto& object : e->GetComponent<components::Inventory>()->inventory_) {
                pos_y += 8;
                std::string text;
                if (object.first == components::INV_OBJECT_CHOUX) {
                    text += "Choux";
                } else if (object.first == components::INV_OBJECT_FLEUR) {
                    text += "Fleur";
                }
                text += " : ";
                text += std::to_string(object.second);
                
                // Selection rectangle
                if (i == selection_) {
                    al_draw_filled_rectangle(constants::kWindowWidth-200, 24 + (selection_ * 8), constants::kWindowWidth, 24 + (selection_ * 8) + 8, al_map_rgb(100, 100, 100));
                    current_selected_object_ = object.first;
                }
                al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth-200, pos_y, ALLEGRO_ALIGN_LEFT, text.c_str());
                ++i;
            }
        }
    }
}
 */
}// Namespace systems
