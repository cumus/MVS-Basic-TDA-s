#pragma once

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

#include "DynArray.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_ERROR,
	UPDATE_STOP,
	
	CHANGE_TO_TITLE,
	CHANGE_TO_CHOOSE_CITY,
	CHANGE_TO_PLAY,
	CHANGE_TO_MAP_PLANE,
	CHANGE_TO_STAGE_END,
	CHANGE_TO_CREDITS,
	CHANGE_TO_HIGHSCORE
};

enum power_Up
{
	POWERUP_TIME_STOP,
	POWERUP_TIME_SLOW,
	POWERUP_FOOD,
	POWERUP_SHIELD,
	POWERUP_LIFE,
	POWERUP_DYNAMITE,
	POWERUP_DOUBLE_HARPOON,
	POWERUP_GRAPPLE,
	POWERUP_SHOTGUN
};

// Configuration -----------

#define ACCELERATED true
#define VSYNC true // false if manually controlled frame rate

/*
#define FPS 60
#define TICKS_PER_FRAME 1000 / FPS
*/


#define SHOWN true
#define FULLSCREEN false
#define RESIZABLE false
#define WINDOW_TITLE "PANG"
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 240
