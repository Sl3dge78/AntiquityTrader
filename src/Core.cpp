#include "Core.hpp"

using namespace std;

float Core::deltaTime = 0;
float Core::startUpdateTime = 0;
float Core::drawTime = 0;
float Core::endDrawTime = 0;

///When core is initialized, the app is ready to be started. Call GameLoop() to start it.
Core::Core()
{
    DebugLog("=================================================\n");
    DebugLog("--- Initializing app ---\n");
    

	if (!al_init())
		throw runtime_error("Failed to initialize: Allegro\n");

	display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!display)
		throw runtime_error("Failed to initialize: Display\n");
        
    DebugLog("Init: Display initialized\n");

	if (!al_init_font_addon())
		throw runtime_error("Failed to initialize: Font\n");

    DebugLog("Init: Font add-on initialized\n");
    
    if(!al_init_primitives_addon())
        throw runtime_error("Failed to initialize: Primitives\n");
    
    DebugLog("Init: primitives initialized\n");
    
	eventQueue = al_create_event_queue();
	if (!eventQueue)
		throw runtime_error("Failed to initialize: Event System\n");
    
    DebugLog("Init: Event Queue initialized\n");

	if (!al_install_keyboard())
		throw runtime_error("Failed to initialize: Keyboard\n");
    
	DebugLog("Init: Keyboard initialized\n");

	coreTimer = al_create_timer(1.0 / FRAMERATE);
	if (!coreTimer)
		throw runtime_error("Failed to initialize: Core Timer\n");
    
	DebugLog("Init: Core Timer\n");
    
    m_world = new ECS::World();
    if (!m_world)
        throw runtime_error("Failed to initialize: World\n");
    
    DebugLog("Init: World\n");
    
	keepCoreRunning = true;
    
	DebugLog("--- App Initialized! ---\n");
	DebugLog("=================================================\n\n");

}

///Call destructor to properly kill the app
Core::~Core()
{
	    DebugLog("=================================================\n");
	    DebugLog("-- - Closing app-- - \n\n");

	// Destroy all gameobjects
    delete m_world; //World deletes all entities and systems
    
	al_destroy_font(coreFont);
        DebugLog("Destroyed: Core Font\n");
    
    al_shutdown_primitives_addon();
        DebugLog("Destroyed: Primitives\n");
    
	al_uninstall_keyboard();
	    DebugLog("Destroyed: Keyboard\n");
    
	al_destroy_event_queue(eventQueue);
	    DebugLog("Destroyed: Event Queue\n");

	al_destroy_display(display);
	    DebugLog("Destroyed: Display Queue\n");
    
	    DebugLog("Application closed successfully\n");
}

///Call this once to keep the app running
void Core::GameLoop()
{
	Start();

	while (keepCoreRunning)
	{
        Core::deltaTime = al_get_time() - Core::startUpdateTime;
        Core::startUpdateTime = al_get_time();
    
		Update();
		
		if (redraw && al_is_event_queue_empty(eventQueue))
		{
            Core::drawTime = al_get_time();
			Draw();
            Core::endDrawTime = al_get_time();
            
            //DrawDebug();
            
            al_flip_display();
		}

	}
}

///Called before the main loop starts. Do gameobject init here.
void Core::Start()
{
	// Start recording events
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	//Start main loop timer
	al_start_timer(coreTimer);
	al_register_event_source(eventQueue, al_get_timer_event_source(coreTimer));

	coreFont = al_create_builtin_font();
    
    m_objctRenderer = m_world->AddSystem<ObjectRendererSystem>();
    
    //PLAYER
    ECS::Entity * m_player = m_world->AddEntity();
    m_player->AddComponent<Component_FontRenderer>(coreFont, '@', al_map_rgb(255, 255, 255));
    m_player->AddComponent<Component_Transform>(225,45);
    m_player->AddComponent<Component_Collider>();
    m_playerSyst = m_world->AddSystem<PlayerSystem>(m_player);
    m_objctRenderer->AddEntity(m_player);
    
    //MAP
    //ECS::Entity * m_mainMap = m_world->AddEntity();
    //m_mainMap->AddComponent<Component_Map>();
    //m_mainMap->AddComponent<Component_Transform>(0,0);
    //m_mapRenderer->AddEntity(m_mainMap);
    m_mapSystem = m_world->AddSystem<MapSystem>(coreFont,"resources/map/map.txt","resources/map/towns.txt",m_world);
    mapColl = m_world->AddSystem<MapCollisionSystem>(m_mapSystem->mapEntity);
    mapColl->AddEntity(m_player);
    
    // CAMERA
    ECS::Entity * m_mainCamera = m_world->AddEntity();
    m_mainCamera->AddComponent<Component_Transform>();
    Rect camBounds = Rect{.x = TILE_AMT_X/2,
                          .y = TILE_AMT_Y/2,
                          m_mapSystem->mapEntity->GetComponent<Component_Map>()->width - TILE_AMT_X/2,
                          m_mapSystem->mapEntity->GetComponent<Component_Map>()->height - TILE_AMT_Y/2
    };
    
    m_mainCamera->AddComponent<Component_Follow>(m_player, camBounds);
    m_cameraSyst = m_world->AddSystem<CameraSystem>();
    m_cameraSyst->AddEntity(m_mainCamera);
    
    //TESTUIPANEL
    /*
    ECS::Entity * TownUI = m_world->AddEntity();
    TownUI->isActive = false;
    UIPanel * panel = TownUI->AddComponent<UIPanel>();
    panel->color = al_map_rgba(0,0,0,200);
    panel->rect = (Rect){.x = WINDOW_WIDTH - 200, .y = 0, .height = WINDOW_HEIGHT, .width = 200};
    UIText * txt = TownUI->AddComponent<UIText>();
    txt->text = "TEST\nTEST\n   TEST";
    txt->rect = (Rect){.x = WINDOW_WIDTH - 200, .y = 0, .height = WINDOW_HEIGHT, .width = 200};
    m_uiRendererSyst = m_world->AddSystem<UISystem>(coreFont);
    m_uiRendererSyst->AddEntity(TownUI);
     */
    
}

/// Update logic
void Core::Update()
{
	//Read events
	ALLEGRO_EVENT ev;
	al_wait_for_event(eventQueue, &ev);
	switch (ev.type)
	{
		//SYSTEM EVENTS
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		CloseApplication();
		break;
            
	case ALLEGRO_EVENT_TIMER:
		redraw = true;
		break;
            
        case ALLEGRO_EVENT_KEY_UP:
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_CHAR:
        m_playerSyst->Update(&ev);
        break;
            
	default:
        
		break;

	}

	//Update logic
    m_cameraSyst->Update(&m_cameraClipRect);
    mapColl->Update();
}

/// Draw all objects
void Core::Draw()
{
	al_clear_to_color(BACKGROUND_COLOR);
    
    m_mapSystem->Draw(m_cameraClipRect);
    m_objctRenderer->Draw(m_cameraClipRect);
    
    //m_uiRendererSyst->Draw();
    
}

void Core::DrawDebug()
{
    debugFrames++;
    
    if(debugFrames >= 10)
    {
        debugFrames = 0;
        
        debugFpstext.str("");
        debugUpdttext.str("");
        debugDrawtext.str("");
        
        debugFpstext <<  "FPS :   " << 1/Core::deltaTime << "";
        debugUpdttext << "Update: " << (Core::drawTime - Core::startUpdateTime)*1000 << "ms.";
        debugDrawtext << "Draw:   " << (Core::endDrawTime - Core::drawTime)*1000 << "ms.";
    }
    
    al_draw_text(coreFont, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, debugFpstext.str().c_str());
    al_draw_text(coreFont, al_map_rgb(255, 255, 255), 0, 8, ALLEGRO_ALIGN_LEFT, debugUpdttext.str().c_str());
    al_draw_text(coreFont, al_map_rgb(255, 255, 255), 0, 16, ALLEGRO_ALIGN_LEFT, debugDrawtext.str().c_str());
}

/// Make the game stop
void Core::CloseApplication()
{
	keepCoreRunning = false;
}
