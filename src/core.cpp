#include "core.hpp"

using namespace std;

ALLEGRO_FONT* Core::CORE_FONT;

///When core is initialized, the app is ready to be started. Call GameLoop() to start it.
Core::Core() {
    DebugLog("=================================================\n");
    DebugLog("--- Initializing app ---\n");

	if (!al_init())
		throw runtime_error("Failed to initialize: Allegro\n");

	display_ = al_create_display(constants::kWindowWidth, constants::kWindowHeight);
	if (!display_)
		throw runtime_error("Failed to initialize: Display\n");
    DebugLog("Init: Display initialized\n");

	if (!al_init_font_addon())
        throw runtime_error("Failed to initialize: Font\n");
    DebugLog("Init: Font add-on initialized\n");
    
    if(!al_init_primitives_addon())
        throw runtime_error("Failed to initialize: Primitives\n");
    DebugLog("Init: primitives initialized\n");
    
	event_queue_ = al_create_event_queue();
	if (!event_queue_)
		throw runtime_error("Failed to initialize: Event System\n");
    DebugLog("Init: Event Queue initialized\n");

	if (!al_install_keyboard())
		throw runtime_error("Failed to initialize: Keyboard\n");
	DebugLog("Init: Keyboard initialized\n");

	core_timer_ = al_create_timer(1.0 / constants::kFramerate);
	if (!core_timer_)
		throw runtime_error("Failed to initialize: Core Timer\n");
	DebugLog("Init: Core Timer\n");
    
    world_ = new ECS::World();
    if (!world_)
        throw runtime_error("Failed to initialize: World\n");
    DebugLog("Init: World\n");
    
	keep_core_running_ = true;
    
	DebugLog("--- App Initialized! ---\n");
	DebugLog("=================================================\n\n");
}

///Call destructor to properly kill the app
Core::~Core() {
    DebugLog("=================================================\n");
    DebugLog("-- - Closing app-- - \n\n");

	// Destroy all gameobjects
    delete world_; //World deletes all entities and systems
    
    al_destroy_font(CORE_FONT);
        DebugLog("Destroyed: Core Font\n");
    
    al_shutdown_primitives_addon();
        DebugLog("Destroyed: Primitives\n");
    
	al_uninstall_keyboard();
	    DebugLog("Destroyed: Keyboard\n");
    
	al_destroy_event_queue(event_queue_);
	    DebugLog("Destroyed: Event Queue\n");

	al_destroy_display(display_);
	    DebugLog("Destroyed: Display Queue\n");
    
	    DebugLog("Application closed successfully\n");
}

///Call this once to keep the app running
void Core::GameLoop() {
	Start();

	while (keep_core_running_)
	{
		Update();
		
		if (redraw_ && al_is_event_queue_empty(event_queue_))
		{
			Draw();
		}
	}
}

///Called before the main loop starts. Do gameobject init here.
void Core::Start() {
	// Start recording events
	al_register_event_source(event_queue_, al_get_display_event_source(display_));
	al_register_event_source(event_queue_, al_get_keyboard_event_source());

	//Start main loop timer
	al_start_timer(core_timer_);
	al_register_event_source(event_queue_, al_get_timer_event_source(core_timer_));

    CORE_FONT = al_create_builtin_font();
    
    world_->CreateSystem<systems::ObjectRendererSystem>(CORE_FONT);
    world_->CreateSystem<systems::PlayerSystem>();
    world_->CreateSystem<systems::MapSystem>(CORE_FONT);
    world_->CreateSystem<systems::CameraSystem>();
    //world_->CreateSystem<systems::MapCollisionSystem>();
    world_->Init();
}

/// Update logic
void Core::Update() {
    world_->UpdateSystemsEntities();
    
	//Read events
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue_, &ev);
	switch (ev.type)
	{
    //SYSTEM EVENTS
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		CloseApplication();
		break;
            
	case ALLEGRO_EVENT_TIMER:
		redraw_ = true;
		break;

	default: // We caught an unknown type of event, we delegate its' handling to the input systems
        world_->Input(& ev);
		break;

	}

	//Update logic
    world_->Update();
}

/// Draw all objects
void Core::Draw() {
	al_clear_to_color(al_map_rgb(0,0,0)); // Background color
    world_->Draw();
    al_flip_display();
}

/// Make the game stop
void Core::CloseApplication() {
    keep_core_running_ = false;
}

/*
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
    
    al_draw_text(CoreFont::coreFont, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, debugFpstext.str().c_str());
    al_draw_text(CoreFont::coreFont, al_map_rgb(255, 255, 255), 0, 8, ALLEGRO_ALIGN_LEFT, debugUpdttext.str().c_str());
    al_draw_text(CoreFont::coreFont, al_map_rgb(255, 255, 255), 0, 16, ALLEGRO_ALIGN_LEFT, debugDrawtext.str().c_str());
}
*/
