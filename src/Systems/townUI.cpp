//
//  townUI.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#include "townUI.hpp"
namespace systems {
    
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
