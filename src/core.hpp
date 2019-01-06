#pragma once
#ifndef Core_hpp
#define Core_hpp

#include <stdexcept>
#include <sstream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "DebugTools.hpp"
#include "constants.hpp"

#include "ECS/ECS.hpp"
#include "Systems/systems.hpp"
#include "Components/components.hpp"

///Manages the engine. Initializes, updates and manages app events.
class Core {
  public:
	Core();
	~Core();
	void GameLoop();
	void CloseApplication();

    static ALLEGRO_FONT*    CORE_FONT;
    
  private:
	ALLEGRO_DISPLAY*        display_ = nullptr;
	ALLEGRO_EVENT_QUEUE*    event_queue_ = nullptr;
	
	// Stops the loop when false
	bool keep_core_running_;
    
    // Should we call the draw function or not
	bool redraw_ = true;
    
    void InitSystems();
	void Start();
    
	// Core game loop
	void Update();
	void Draw();
	
	// Time management
	ALLEGRO_TIMER* core_timer_ = nullptr; // Locks fps
    
    ECS::World* world_ = nullptr;
};

#endif
