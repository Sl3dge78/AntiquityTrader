#pragma once
#ifndef Core_hpp
#define Core_hpp

#include <stdexcept>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "DebugTools.hpp"
#include "Macros.hpp"


#include "ECS/ECS.hpp"
#include "Systems/RenderingSystems.hpp"
#include "Systems/PlayerInputSystem.hpp"
#include "Components.hpp"
#include "Map.hpp"


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
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE * eventQueue = NULL;
	ALLEGRO_FONT * coreFont = NULL;
	
	// Stops the loop when false
	bool keepCoreRunning;
	bool redraw = true;
    
    void initSystems();
    
	void Start();
	// Core game loop
	void Update();
	void Draw();
	
	// Time management
	ALLEGRO_TIMER * coreTimer = NULL; // Locks fps
    
    //ECS
    ECS::World * m_world = NULL;
    
    ObjectRendererSystem * m_objctRenderer = NULL;
    MapRendererSystem * m_mapRenderer = NULL;
    PlayerInputSystem * m_playerInput = NULL;
    
    ECS::Entity * m_player = NULL;
    
    ECS::Entity * m_mainMap = NULL;
	
};

#endif
