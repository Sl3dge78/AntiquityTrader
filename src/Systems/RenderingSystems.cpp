//
//  RendererSystem.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//
#include "RenderingSystems.hpp"

namespace systems {
    
ObjectRendererSystem::ObjectRendererSystem() {
    this->AddComponentFilter<components::TileSetRenderer>();
    this->pos_z = 0;
}

void ObjectRendererSystem::OnEntityListChanged() {

    entities_.sort([](const ECS::Entity* e1, const ECS::Entity* e2)
                   {
                       return e1->GetComponent<components::TileSetRenderer>()->pos_z_ > e2->GetComponent<components::TileSetRenderer>()->pos_z_;
                   });
    
}
    
void ObjectRendererSystem::Draw() {
    
    Rect clip_rect = CameraSystem::GetClipRect();
    
    for(auto& entity : entities_)
    {
        auto rdr = entity->GetComponent<components::TileSetRenderer>();
        auto trfm = entity->GetComponent<components::Transform>();
        if(trfm->GetPosX() > clip_rect.x &&
           trfm->GetPosY() > clip_rect.y &&
           trfm->GetPosX() < clip_rect.x+clip_rect.width &&
           trfm->GetPosY() < clip_rect.y+clip_rect.height)
        {

            al_draw_scaled_bitmap(bitmap_,
                                  rdr->pos_.x * constants::kFileTileWidth,
                                  rdr->pos_.y * constants::kFileTileHeight,
                                  constants::kFileTileWidth,
                                  constants::kFileTileHeight,
                                  
                                  (trfm->GetPosX()-clip_rect.x) * constants::kTileWidth,
                                  (trfm->GetPosY()-clip_rect.y) * constants::kTileHeight,
                                  constants::kTileWidth,
                                  constants::kTileHeight,
                                  
                                  0);
            /*al_draw_bitmap_region(bitmap_,
                                  rdr->pos_.x * constants::kFileTileWidth,
                                  rdr->pos_.y * constants::kFileTileHeight,
                                  constants::kFileTileWidth,
                                  constants::kFileTileHeight,
                                  (trfm->GetPosX()-clip_rect.x) * constants::kTileWidth,
                                  (trfm->GetPosY()-clip_rect.y) * constants::kTileHeight,
                                  0);
             */
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
            
            int movement_x = target_transform->GetPosX() - camera_transform->GetPosX();
            int movement_y = target_transform->GetPosY() - camera_transform->GetPosY();
            camera_transform->Translate(movement_x, movement_y);
            
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
            CameraSystem::clip_rect_.x = camera_transform->GetPosX() - (constants::kAmoutOfTilesOnScreenX/2);
            CameraSystem::clip_rect_.y = camera_transform->GetPosY() - (constants::kAmoutOfTilesOnScreenY/2);
        }
    }
}

} // Namespace systems
