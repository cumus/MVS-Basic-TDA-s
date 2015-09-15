
#include "ModuleInput.h"

ModuleInput::ModuleInput(Application* app) : Module(app), key(NULL) {}

update_status ModuleInput::PreUpdate()
{
	SDL_PollEvent(&mainEvent);
	if (mainEvent.type == SDL_QUIT){ return UPDATE_STOP; }

	key = SDL_GetKeyboardState(NULL);
	if (key[SDL_SCANCODE_ESCAPE] == 1){ return UPDATE_STOP; }

	return UPDATE_CONTINUE;
}
