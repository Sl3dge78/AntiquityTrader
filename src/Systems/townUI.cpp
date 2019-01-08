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
        std::string money_label_ = "Money: ";
        money_label_ += std::to_string(e->GetComponent<components::MoneyPurse>()->amount_);
        money_label_ += "$";
        
        al_draw_text(font_, al_map_rgb(255, 255, 255), 8, 4, ALLEGRO_ALIGN_LEFT, money_label_.c_str());
    }
}
    
    /*
     * == TOWN UI ==
     */

TownUI::TownUI() {
    this->AddComponentFilter<components::Town>();
    this->pos_z = -1;
}

void TownUI::Draw() {
    for (auto& e : entities_) {
        if(e->GetComponent<components::Town>()->is_player_in_) {
            int pos_y = 0;
            al_draw_filled_rectangle(constants::kWindowWidth-200, pos_y, constants::kWindowWidth, constants::kWindowHeight, al_map_rgb(0, 0, 0));
            
            // TODO : MAKE THIS AUTOMATIC
            pos_y += 8;
            al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth-200, pos_y, ALLEGRO_ALIGN_LEFT, e->GetComponent<components::Town>()->name_.c_str());
            pos_y += 8;
            al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth-200, pos_y, ALLEGRO_ALIGN_LEFT, "Objets vendus:");
            
            
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
                    
                al_draw_text(font_, al_map_rgb(255, 255, 255), constants::kWindowWidth-200, pos_y, ALLEGRO_ALIGN_LEFT, text.c_str());
            }
        }
    }
}
}// Namespace systems
