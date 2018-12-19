//
//  DebugTools.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 19/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef DebugTools_hpp
#define DebugTools_hpp

#include <stdio.h>
#include <string>
#include <time.h>
#include <chrono>
#include <iostream>

std::string GetCurrentTimeString();
void DebugLog(char const * message);

#endif /* DebugTools_hpp */
