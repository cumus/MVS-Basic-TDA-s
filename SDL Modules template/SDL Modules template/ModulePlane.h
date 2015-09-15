#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModulePlane_H__
#define __ModulePlane_H__

class ModulePlane : public Module{
public:

	// background
	SDL_Rect background_rect;
	SDL_Rect background_source_rect;

	// city rects
	SDL_Rect city_rect[17];
	SDL_Rect city_source_rect[2];

	// plane rects
	SDL_Rect plane_rect;
	SDL_Rect plane_source_rect[6];
	unsigned int plance_source_index;

	unsigned int travel_index;

	unsigned int ticks;

	ModulePlane(Application* app);
	bool Init();
	update_status Update();

	void UpdatePlane();
};

#endif