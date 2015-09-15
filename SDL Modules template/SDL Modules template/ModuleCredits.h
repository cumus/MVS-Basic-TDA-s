#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleCredits_H__
#define __ModuleCredits_H__

class ModuleCredits : public Module{
public:
	ModuleCredits(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif