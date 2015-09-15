#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleInput_H__
#define __ModuleInput_H__

class ModuleInput : public Module{

public:

	SDL_Event mainEvent;
	const Uint8* key;

	ModuleInput(Application* app);
	ModuleInput(const ModuleInput& input);
	update_status PreUpdate();
};

#endif