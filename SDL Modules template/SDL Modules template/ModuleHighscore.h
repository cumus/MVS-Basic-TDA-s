#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleHighscore_H__
#define __ModuleHighscore_H__

class ModuleHighscore : public Module{
public:
	ModuleHighscore(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif