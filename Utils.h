#pragma once

#include <SDL2/SDL.h>               // SDL OpenGL Framework
#include <SDL2/SDL_image.h>         // An SDL2 extension that enables different image formats
#include <SDL2/SDL_mixer.h>         // An SDL2 Extension that enables different Audio Formats
#include <SDL2/SDL_net.h>           // An SDL2 extension that enables easier network programming
#include <SDL2/SDL_ttf.h>           // An SDL2 extension that enables fonts
#include <iostream>                 // cout, cin, etc
#include <ostream>                  // control what output stream to print to, an actual LOG file , STDOUT, etc
#include <string>                   // Enable string data types
#include <vector>                   // Enable Vectors
#include <fstream>                  // Enable file write/write have to pass in flag ios::in | ios::out
#include <boost/lexical_cast.hpp>   // std::string to int
#include <hash_map>                 // Hashes nuff said

// Map Loader
#include "TmxParser/Tmx.h"

// Callback functions for menu items
#include <boost/function.hpp>   // Allow function references to be accepted as arguments
#include <boost/bind.hpp>       // Allow function references to be passed as arguments
#include <boost/ptr_container/ptr_vector.hpp> // Allow a vector of pointers that automatically calls delete

// Safely delete pointers, arrays of points, and release memory and such from the heap (dynamic memory)
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=nullptr; } }
#endif

// Constants
#define DEFAULT_FONT_SIZE 24
#define GAME_NAME "Last Bastion"
#define SPRITE_FOLDER "Assets/sprites/"
#define IMAGE_FOLDER "Assets/images/"
#define MAP_FOLDER "Assets/maps/"
#define FONT_FOLDER "Assets/fonts/"
#define MUSIC_FOLDER "Assets/music/"
#define SOUND_FOLDER "Assets/sounds/"
#define MAPS_FOLDER "Assets/maps/"
#define SAVE_FOLDER "Assets/saves"
#define DEFAULT_FONT "SourceSansPro-Regular.ttf"
#define LOG_FILE std::cout
#define LOG_LEVEL 5
const SDL_Color ColorWhite = {255, 255, 255, 255};
const SDL_Color ColorBlack = {0, 0, 0, 255};

enum ElementType
{
    None,
    Fire,
    Earth,
    Air,
    Water,
    Metal
};

#include "GameLog.h"
