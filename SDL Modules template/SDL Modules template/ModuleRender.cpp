
#include "ModuleRender.h"

ModuleRender::ModuleRender(Application* app) : Module(app), renderer(NULL) {}

bool ModuleRender::Init()
{
	Uint32 rendererFlags = NULL;
	if (ACCELERATED){ rendererFlags |= SDL_RENDERER_ACCELERATED; }
	if (VSYNC){ rendererFlags |= SDL_RENDERER_PRESENTVSYNC; }

	renderer = SDL_CreateRenderer(app->windowModule->window, -1, rendererFlags);
	if (renderer == NULL){ return false; }

	return true;
}

update_status ModuleRender::PreUpdate()   {   SDL_RenderClear(renderer); return UPDATE_CONTINUE; }
update_status ModuleRender::PostUpdate()  { SDL_RenderPresent(renderer); return UPDATE_CONTINUE; }

bool ModuleRender::CleanUp()
{
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}
	return true;
}


void ModuleRender::Print(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* rect)
{
	SDL_RenderCopy(renderer, texture, source_rect, rect);
}

void ModuleRender::Fade_Screen()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);

	SDL_RenderFillRect(renderer, &app->sceneModule->background_rect);
}


