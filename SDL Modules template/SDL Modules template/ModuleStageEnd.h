#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL2_ttf-2.0.12/include/SDL_ttf.h"
#pragma comment( lib, "SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib" )



#ifndef __ModuleStageEnd_H__
#define __ModuleStageEnd_H__


class ModuleStageEnd : public Module{
public:

	// image shown
	SDL_Rect image_rect;
	SDL_Rect image_source_rect[4][1];
	unsigned int max_index[4];
	unsigned int source_index_1, source_index_2;
	unsigned int next_extend;
	bool push_button_shown;
	void NextExtend();
	unsigned int ticks;
	int next_extend_counter;

	ModuleStageEnd(Application* app);
	bool Init();
	update_status Update();
	bool CleanUp();
};

#endif