//
//  DebugTools.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 19/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "DebugTools.hpp"

std::string GetCurrentTimeString()
{
    //Get time
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    //YYYY-MM-DD - HH:MM:SS = 22chars
    char time[22];
    
    std::strftime(time, 22, "%F - %T", std::localtime(&now));
    
    return std::string(time);
}

void DebugLog(char const * message)
{
    std::string time;
    
    time += GetCurrentTimeString();
    std::cout << GetCurrentTimeString() << " - " << message;
}
