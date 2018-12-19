#pragma once
#ifndef Core_h
#define Core_h

#include <stdexcept>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "DebugTools.hpp"
#include "Macros.h"


#include "ECS/ECS.h"
#include "RendererSystem.h"
#include "Components.h"


///Manages the engine. Initializes, updates and manages app events.
class Core
{

public:
	Core();
	~Core();
	void GameLoop();
	void CloseApplication();
	static float deltaTime;
	static float previousTime;

private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * eventQueue;
	ALLEGRO_FONT * coreFont;
	
	// Stops the loop when false
	bool keepCoreRunning;
	bool redraw = true;
    
    void initSystems();
    
	void Start();
	// Core game loop
	void Update();
	void Draw();
	
	// Time management
	ALLEGRO_TIMER * coreTimer; // Locks fps
    
    //ECS
    ECS::World * world;
    
    RendererSystem * rendererSystem;
    
    ECS::Entity * player;
	
};

#endif
