#ifndef __j1PHYSFS_H__
#define __j1PHYSFS_H__

#include "j1Module.h"

class j1PhysFS : public j1Module
{
public:

	j1PhysFS();

	// Destructor
	virtual ~j1PhysFS();

	// Called before render is available
	bool Awake(char* args);

	// Called before quitting
	bool CleanUp();

};

#endif // __j1PHYSFS_H__