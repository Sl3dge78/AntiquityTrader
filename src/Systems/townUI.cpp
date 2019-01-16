//
//  townUI.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#include "townUI.hpp"
namespace systems {

MainUI::MainUI() {
    this->AddComponentFilter<components::Player>();
    this->pos_z = -1;
}

void MainUI::Draw() {
    for (auto& e : entities_) {
        al_draw_filled_rectangle(0, 0, constants::kWindowWidth, 16, al_map_rgb(0, 0, 0));
        std::stringstream money_label_;
        money_label_ << "Money: " << std::to_string(e->GetComponent<components::MoneyPurse>()->amount_) << "$";
        
        al_draw_text(font_, al_map_rgb(255, 255, 255), 8, 4, ALLEGRO_ALIGN_LEFT, money_label_.str().c_str());
        
        std::stringstream inventory_label;
        inventory_label << "Inventory: " << components::kInventoryObjectList[0].name_ << ":" << e->GetComponent<components::Inventory>()->inventory_[components::kInventoryObjectList[0].type_] << "\0";
        al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth/2, 4, ALLEGRO_ALIGN_LEFT, inventory_label.str().c_str());
    }
}
    
    /*
     * == TOWN UI ==
     */

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

// TODO : DIS IS DIRTY CLEAN IT UP !!!!
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
}// Namespace systems
