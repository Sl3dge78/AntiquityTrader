//
//  constants.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 06/01/2019.
//  Copyright © 2019 Sledge. All rights reserved.
//

#include "constants.hpp"

namespace constants {

const float     kFramerate = 30.0;
const int       kWindowWidth = 800;
const int       kWindowHeight = 600;

const int       kFileTileWidth = 8;
const int       kFileTileHeight = 8;
    
const int       kTileWidth = 16;
const int       kTileHeight = 16;

const int       kAmoutOfTilesOnScreenX = kWindowWidth/kTileWidth;
const int       kAmoutOfTilesOnScreenY = kWindowHeight/kTileHeight;

const char*     kMapFile = "resources/map/map.txt";
const char*     kTownFile = "resources/map/towns.txt";
    
}
