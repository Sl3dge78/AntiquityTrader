//
//  main.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//
#include "main.hpp"

int main(int argc, char **argv)
{
    Core* app;
    try {
        app = new Core();
    }
    catch (const std::runtime_error & e ){
        DebugLog(e.what());
        
        return -1;
    }
    
    //Game init is done, we start the main game loop
    app->GameLoop();
    
    //Game exectuion is completed we call the destructor
    delete app;
    return 0;
}
