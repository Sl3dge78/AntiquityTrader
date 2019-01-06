#pragma once
#ifndef constants_hpp
#define constants_hpp

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

namespace constants {

extern const float     kFramerate;
extern const int       kWindowWidth;
extern const int       kWindowHeight;

extern const int       kFileTileWidth;
extern const int       kFileTileHeight;

extern const int       kTileWidth;
extern const int       kTileHeight;

extern const int       kAmoutOfTilesOnScreenX;
extern const int       kAmoutOfTilesOnScreenY;

extern const char*     kMapFile;
extern const char*     kTownFile;
    
}


/*
#define FRAMERATE 30.0

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#define TILE_AMT_X WINDOW_WIDTH/TILE_WIDTH
#define TILE_AMT_Y WINDOW_HEIGHT/TILE_HEIGHT

#define BACKGROUND_COLOR al_map_rgb(25, 25, 25)

#define MAP_FILE "resources/map/map.txt"
#define TOWNS_FILE "resources/map/towns.txt"
*/
#endif
