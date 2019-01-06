//
//  RendererSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//
#include "RenderingSystems.hpp"

namespace systems {
    
void ObjectRendererSystem::Init() {
    this->AddComponentFilter<components::FontRenderer>();
}

void ObjectRendererSystem::Draw() {
    
    Rect clip_rect = CameraSystem::GetClipRect();
    
    for(auto&& entity : entities_)
    {
        auto rdr = entity->GetComponent<components::FontRenderer>();
        auto trfm = entity->GetComponent<components::Transform>();
        if(trfm->pos_x_ > clip_rect.x &&
           trfm->pos_y_ > clip_rect.y &&
           trfm->pos_x_ < clip_rect.x+clip_rect.width &&
           trfm->pos_y_ < clip_rect.y+clip_rect.height)
        {
            al_draw_text(font_,
                         rdr->color_,
                         (trfm->pos_x_-clip_rect.x) * constants::kTileWidth,
                         (trfm->pos_y_-clip_rect.y) * constants::kTileHeight,
                         ALLEGRO_ALIGN_LEFT,
                         rdr->text_);
        }
    }
}

  //
  // CAMERA SYSTEM
  //

Rect CameraSystem::clip_rect_ = {0,0,0,0};

void CameraSystem::Init() {
    main_camera_ = world_->CreateEntity();
    main_camera_->AddComponent<components::Transform>();
    
    CameraSystem::clip_rect_.width = constants::kAmoutOfTilesOnScreenX;
    CameraSystem::clip_rect_.height = constants::kAmoutOfTilesOnScreenY;
    /*
    bounds_ = Rect{ .x = constants::kAmoutOfTilesOnScreenX/2,
                    .y = constants::kAmoutOfTilesOnScreenY/2,
                    map_->GetComponent<components::Map>()->width - constants::kAmoutOfTilesOnScreenX/2,
                    map_->GetComponent<components::Map>()->height - constants::kAmoutOfTilesOnScreenY/2
                    };
     */
    
    this->AddComponentFilter<components::Player>();
}

void CameraSystem::Update() {
    if(is_active_) {
        for (auto& e : entities_) {
            components::Transform* target_transform = e->GetComponent<components::Transform>();
            components::Transform* camera_transform = main_camera_->GetComponent<components::Transform>();
            
            camera_transform->pos_y_ = target_transform->pos_y_;
            camera_transform->pos_x_ = target_transform->pos_x_;
            
            //Test for collision
            /*
            if (camera_transform->posX < bounds_.x)
                camera_transform->posX = bounds_.x;
            else if (camera_transform->posX > bounds_.width)
                camera_transform->posX = bounds_.width;
            
            if(camera_transform->posY < bounds_.y)
                camera_transform->posY = bounds_.y;
            else if (camera_transform->posY > bounds_.height)
                camera_transform->posY = bounds_.height;
            */
            CameraSystem::clip_rect_.x = camera_transform->pos_x_ - (constants::kAmoutOfTilesOnScreenX/2);
            CameraSystem::clip_rect_.y = camera_transform->pos_y_ - (constants::kAmoutOfTilesOnScreenY/2);
        }
    }
}

} // Namespace systems
