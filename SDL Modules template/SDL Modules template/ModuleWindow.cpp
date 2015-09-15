
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app) : Module(app), window(NULL), scale(1) {}

ModuleWindow::ModuleWindow(const ModuleWindow& window) : Module(window.app), scale(window.scale) {}


bool ModuleWindow::Init()
{
	// Get Display dimensions to define scale
	SDL_DisplayMode mode;

	if (SDL_GetNumDisplayModes(0) < 1) { return false; } // check if there are no displays 
	if (SDL_GetDisplayMode(0, 0, &mode) != 0) { return false; } // get display mode

	// check display has minimum dimensions
	if (mode.w < SCREEN_WIDTH || mode.h < SCREEN_HEIGHT)
	{
		LOG("Display too small");
		return false;
	}
	
	// increase scale with 80px margin on each side
	while (SCREEN_WIDTH * (scale + 1) + 160 < mode.w && SCREEN_HEIGHT * (scale + 1) + 160 < mode.h){ scale++; }
	
	scale = 3;
	scale_f = float(scale);

	// manage window flags
	Uint32 windowFlags = NULL;
	if (SHOWN){ windowFlags |= SDL_WINDOW_SHOWN; }
	if (FULLSCREEN){ windowFlags |= SDL_WINDOW_FULLSCREEN; }
	if (RESIZABLE){ windowFlags |= SDL_WINDOW_RESIZABLE; }

	// create window
	window = SDL_CreateWindow(WINDOW_TITLE, 80, 80, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale, windowFlags);
	if (window == NULL){ return false; }

	return true;
}

bool ModuleWindow::CleanUp()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	return true;
}
