#include "Core.hpp"

using namespace std;

float Core::deltaTime = 0;
float Core::previousTime = 0;

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
    
    world = new ECS::World();
    if (!world)
        throw runtime_error("Failed to initialize: World\n");
    
    DebugLog("Init: World\n");
    
    rendererSystem = new RendererSystem();
    if(!rendererSystem)
        throw runtime_error("Failed to initialize: Renderer System\n");
    
    DebugLog("Init: Systems\n");
    
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
    delete world; //World deletes all entities and systems
    
	al_destroy_font(coreFont);
        DebugLog("Destroyed: Core Font\n");
    
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
		// Register inputs

		//TODO : Update delta time
		Update();
		
		if (redraw && al_is_event_queue_empty(eventQueue))
		{
			Draw();
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
    
    
    /*
     *   ENTITIES
     */
    player = world->AddEntity();
    
    player->AddComponent<FontRenderer>(coreFont, '@', al_map_rgb(150, 0, 0));
    player->AddComponent<Transform>();
    
    /*
     *   SYSTEMS
     */
    rendererSystem->AddEntity(player);
}

/// Update logic
void Core::Update()
{
	//Update delta time
	Core::deltaTime = al_get_time() - Core::previousTime;
	Core::previousTime = al_get_time();

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
	
	default:
		//GAME EVENTS
		
		break;

	}

	//Update logic

}

/// Draw all objects
void Core::Draw()
{
	al_clear_to_color(BACKGROUND_COLOR);
    
    rendererSystem->Draw();
    
	al_flip_display();
}

/// Make the game stop
void Core::CloseApplication()
{
	keepCoreRunning = false;
}
