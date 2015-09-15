#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

class ModuleTextures : public Module{
public:
	
	SDL_Texture* background_sprite;
	SDL_Texture* balls_sprite;
	SDL_Texture* powerUp_sprite;
	SDL_Texture* bricks_sprite;
	SDL_Texture* enemies_sprite;
	SDL_Texture* harpoons_sprite;
	SDL_Texture* instructions_sprite;
	SDL_Texture* map_countdown_sprite;
	SDL_Texture* map_sprite;
	SDL_Texture* particles_sprite;
	SDL_Texture* players_sprite;
	SDL_Texture* ready;
	SDL_Texture* scores_sprite;
	SDL_Texture* timer_sprite;
	SDL_Texture* title_sprite;
	SDL_Texture* level_complete;

	ModuleTextures(Application* app);
	bool Init();
	bool CleanUp();
};

#endif