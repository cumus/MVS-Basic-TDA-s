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

bool j1PhysFS::OpenFile(const char * filename, PHYSFS_File *physFS_file)
{
	physFS_file = PHYSFS_openRead(filename);
	return (physFS_file != NULL);
}

bool j1PhysFS::GetFileLength(PHYSFS_File * handle, PHYSFS_sint64 size)
{
	bool retValue = true;

	if (retValue = (handle != NULL))
	{
		size = PHYSFS_fileLength(handle);
	}

	return retValue;
}

int j1PhysFS::ReadPhysFS(
	PHYSFS_File * handle,
	void * buffer,
	PHYSFS_uint32 objSize,
	PHYSFS_uint32 objCount
	)
{
	return PHYSFS_read(handle, buffer, objSize, objCount);



}

bool j1PhysFS::ClosePhysFS(PHYSFS_File * 	handle)
{
	bool retValue = true;

	if (retValue = (handle != NULL))
	{
		retValue = (PHYSFS_close(handle) != 0);
	}

	return retValue;


}

bool j1PhysFS::LoadSLD_RWops(const void* mem, int size)
{
	io = SDL_RWFromConstMem(mem, size);
	return (io != NULL);
}



