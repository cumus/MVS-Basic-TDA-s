#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleTitle_H__
#define __ModuleTitle_H__

class ModuleTitle : public Module{
public:

	// Ball Animation Resources
	SDL_Rect balloon_source_rect[5];
	SDL_Rect balloon_rects[4];
	int gravity[4];
	int horizontal_limits[4];
	unsigned int source_rect_index[4];
	unsigned int update_counter[4];
	bool falling[4];

	// Non-Animated Title Resources
	SDL_Rect rect;
	SDL_Rect source_rect[5];
	SDL_Rect insert_coin_rect;

	bool insert_coin_pressed;
	unsigned int ticks;

	ModuleTitle(Application* app);
	bool Init();
	update_status Update();

	void Update_Balloons();
};

#endif