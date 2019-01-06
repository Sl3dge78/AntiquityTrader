//
//  RendererSystem.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef RendererSystem_hpp
#define RendererSystem_hpp

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "../types.hpp"
#include "../constants.hpp"

#include "../ECS/ECS.hpp"
#include "components.hpp"

namespace systems {

struct ObjectRendererSystem : public ECS::DrawSystem {
    ObjectRendererSystem();
    
    void ChangeFilters();
    void OnEntityAdded(ECS::Entity* entity);
    void Init();
    void Draw();
};

class CameraSystem : public ECS::UpdateSystem, public ECS::InitSystem, public ECS::WorldSetSystem {
public:
    void Init();
    void Update();
    
    static Rect     clip_rect_;
    static Rect     GetClipRect() { return clip_rect_; };
    
private:
    ECS::Entity*    main_camera_ = nullptr;
    ECS::Entity*    map_ = nullptr;
    Rect            bounds_; // TODO : Move bounds into its' separate component
    
};
} // Namespace systems
#endif /* RendererSystem_hpp */
