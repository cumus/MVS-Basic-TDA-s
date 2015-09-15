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

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_ERROR,
	UPDATE_STOP
	
	//CHANGE_TO_...
};

// Configuration -----------
/*
#define ACCELERATED true
#define VSYNC true // false if manually controlled frame rate

#define FPS 60
#define TICKS_PER_FRAME 1000 / FPS
#define SHOWN true
#define FULLSCREEN false
#define RESIZABLE false
#define WINDOW_TITLE "PANG"
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 240
*/

#define FONT "font/PANGTYPO.TTF"


void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
}