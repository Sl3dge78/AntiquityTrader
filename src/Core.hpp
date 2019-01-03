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
#include "Macros.hpp"


#include "ECS/ECS.hpp"
#include "Systems/RenderingSystems.hpp"
#include "Systems/PlayerSystem.hpp"
#include "Systems/MapSystem.hpp"
#include "Systems/Systems.hpp"

#include "Components/Components.hpp"
#include "Components/Component_Map.hpp"
#include "Components/UI.hpp"


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
    MapSystem * m_mapSystem = nullptr;
    PlayerSystem * m_playerSyst = nullptr;
    CameraSystem * m_cameraSyst = nullptr;
    UISystem * m_uiRendererSyst = nullptr;
    MapCollisionSystem * mapColl = nullptr;
    
    Rect m_cameraClipRect {0,0,0,0};
    
    // DEBUG
    void DrawDebug();
    int debugFrames = 0;
    std::stringstream debugFpstext;
    std::stringstream debugUpdttext;
    std::stringstream debugDrawtext;
	
};

#endif
