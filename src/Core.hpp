#pragma once
#ifndef Core_hpp
#define Core_hpp

#include <stdexcept>
#include <sstream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "DebugTools.hpp"
#include "Macros.hpp"


#include "ECS/ECS.hpp"
#include "Systems/RenderingSystems.hpp"
#include "Systems/PlayerInputSystem.hpp"
#include "Systems/Systems.hpp"

#include "Components/Components.hpp"
#include "Components/Map.hpp"


///Manages the engine. Initializes, updates and manages app events.
class Core
{

public:
	Core();
	~Core();
	void GameLoop();
	void CloseApplication();
	static float deltaTime, startUpdateTime, drawTime, endDrawTime;

private:
	ALLEGRO_DISPLAY * display = nullptr;
	ALLEGRO_EVENT_QUEUE * eventQueue = nullptr;
	ALLEGRO_FONT * coreFont = nullptr;
	
	// Stops the loop when false
	bool keepCoreRunning;
	bool redraw = true;
    
    void initSystems();
    
	void Start();
	// Core game loop
	void Update();
	void Draw();
	
	// Time management
	ALLEGRO_TIMER * coreTimer = nullptr; // Locks fps
    
    //ECS
    ECS::World * m_world = nullptr;
    
    ObjectRendererSystem * m_objctRenderer = nullptr;
    MapRendererSystem * m_mapRenderer = nullptr;
    PlayerInputSystem * m_playerInput = nullptr;
    CameraSystem * m_cameraSyst = nullptr;
    
    Rect m_cameraClipRect {0,0,0,0};
    
    // DEBUG
    void DrawDebug();
    int debugFrames = 0;
    std::stringstream debugFpstext;
    std::stringstream debugUpdttext;
    std::stringstream debugDrawtext;
	
};

#endif
