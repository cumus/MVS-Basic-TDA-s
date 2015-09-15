#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

class Application;

class ModuleWindow : public Module{
public:

	SDL_Window* window;
	int scale;
	float scale_f;

	ModuleWindow(Application* app);
	ModuleWindow(const ModuleWindow& window);
	bool Init();
	bool CleanUp();
};

#endif