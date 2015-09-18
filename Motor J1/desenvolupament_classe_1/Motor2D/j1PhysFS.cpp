#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PhysFS.h"

#include "PhysFS\include\physfs.h"
#pragma comment( lib, "PhysFS/libx86/physfs.lib" )

j1PhysFS::j1PhysFS() : j1Module()
{}

// Destructor
j1PhysFS::~j1PhysFS()
{}

// Called before render is available
bool j1PhysFS::Awake(char* args)
{
	LOG("Loading PhysFS");
	bool ret = true;

	if (!PHYSFS_init(args))
	{
		LOG("PhysFS could not initialize! PHYSFS_getLastError(): %s\n", PHYSFS_getLastError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool j1PhysFS::CleanUp()
{
	LOG("Closing PhysFS");
	bool ret = true;

	//PHYSFS_close(myfile);

	if (!PHYSFS_isInit())
	{
		if (!PHYSFS_deinit())
		{
			LOG("PhysFS could not deinitialize! PHYSFS_getLastError(): %s\n", PHYSFS_getLastError());
			ret = false;
		}
	}
	else
	{
		LOG("PhysFS couldn't be closed because it wasn't initialized");
	}

	return ret;
}
