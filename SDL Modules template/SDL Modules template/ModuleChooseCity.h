#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleChooseCity_H__
#define __ModuleChooseCity_H__

class ModuleChooseCity : public Module{
public:

	// background
	SDL_Rect background_rect;
	SDL_Rect background_source_rect;

	// number countdown
	SDL_Rect countdown_rect;
	SDL_Rect countdown_source_rect[10];
	unsigned int current_number;

	// selection squares
	SDL_Rect selection_rect[17];
	SDL_Rect selection_source_rect[2];
	unsigned int selection_index, selection_source_index;

	// forward return controls
	SDL_Rect controls_rect;
	SDL_Rect controls_source_rect;

	// izquierda+arriba y derecha
	bool a_pressed, d_pressed;

	unsigned int ticks, update_counter;

	ModuleChooseCity(Application* app);
	bool Init();
	update_status Update();
};

#endif