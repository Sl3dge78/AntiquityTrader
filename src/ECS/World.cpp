//
//  World.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "World.hpp"

namespace ECS
{

World::~World() {
    DeleteAllSystems();
    DeleteAllEntities();
}

// == ENTITIES ==

Entity* World::CreateEntity() {
    Entity* e = new Entity();
    entity_list.push_back(e);
    
    is_systems_entities_list_dirty_ = true;
    
    return e;
}

void World::DeleteAllEntities() {
    for(Entity* e : entity_list) {
        delete e;
    }
    
    is_systems_entities_list_dirty_ = true;
    
    entity_list.clear();
}

// == SYSTEMS ==

ISystem* World::AddSystem(ISystem* sys) {
    
    if (dynamic_cast<InitSystem*>(sys) != nullptr) {
        init_systems_.push_back(dynamic_cast<InitSystem*>(sys));
    }
    
    if (dynamic_cast<InputSystem*>(sys) != nullptr) {
        input_systems_.push_back(dynamic_cast<InputSystem*>(sys));
    }
    
    if (dynamic_cast<UpdateSystem*>(sys) != nullptr) {
        update_systems_.push_back(dynamic_cast<UpdateSystem*>(sys));
    }
    
    if (dynamic_cast<DrawSystem*>(sys) != nullptr) {
        draw_systems_.push_back(dynamic_cast<DrawSystem*>(sys));
    }
    
    if (dynamic_cast<WorldSetSystem*>(sys) != nullptr) {
        dynamic_cast<WorldSetSystem*>(sys)->SetWorld(this);
    }
    
    systems_.push_back(sys);
    return sys;
}

void World::DeleteAllSystems() {
    for(ISystem* sys : systems_) {
        delete sys;
    }
    systems_.clear();
    init_systems_.clear();
    input_systems_.clear();
    update_systems_.clear();
    draw_systems_.clear();
}

void World::Init() {
    for(InitSystem* system: init_systems_) {
        system->Init();
    }
}

void World::Input(ALLEGRO_EVENT* const ev) {
    for(InputSystem* system: input_systems_) {
        system->Input(ev);
    }
}

void World::Update() {
    for(UpdateSystem* system: update_systems_) {
        system->Update();
    }
}

void World::Draw() {
    for(DrawSystem* system: draw_systems_) {
        system->Draw();
    }
}
    
void World::UpdateSystemsEntities() {

    if(is_systems_entities_list_dirty_) {
        for (auto& system : systems_) { // for each system
            if (system->filter_.size() > 0) {
                system->entities_.clear();
                
                for (auto& entity : entity_list) { // Compare each entity to the filter list
                    bool add = false;
                    for (auto& id : system->filter_) {
                        if(!entity->HasComponent(id)) {
                            if(system->filter_type_ == FILTER_AND){
                                add = false;
                                break;
                            }
                        } else {
                            add = true;
                            if(system->filter_type_ == FILTER_OR)
                                break;
                        }
                    }
                    if(add)
                        system->entities_.push_front(entity);
                }
                system->OnEntityListChanged();
            }
        }
    }
}
    
}



