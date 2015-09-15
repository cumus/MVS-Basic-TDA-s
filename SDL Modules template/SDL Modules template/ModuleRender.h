#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleRender_H__
#define __ModuleRender_H__


class Application;

class ModuleRender : public Module{
public:

	SDL_Renderer* renderer;

	ModuleRender(Application* app);
	ModuleRender(const ModuleRender& render);
	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	void Print(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* rect);
	void Fade_Screen();
};

#endif