/*

#ifndef __j1PHYSFS_H__
#define __j1PHYSFS_H__

#include "j1Module.h"
#include "SDL\include\SDL.h"



class j1PhysFS : public j1Module
{
private:

	SDL_RWops* io;

public:

	j1PhysFS();

	// Destructor
	virtual ~j1PhysFS();

	// Called before render is available
	bool Awake(char* args);

	// Called before quitting
	bool CleanUp();

private:

	//SDL_RWops* SDL_RWFromConstMem(const void* mem, int size)

	//PHYSFS_File * PHYSFS_openRead(const char * 	filename)
	//PHYSFS_sint64 PHYSFS_fileLength(PHYSFS_File * 	handle)
	//PHYSFS_sint64 PHYSFS_read	(	PHYSFS_File * 	handle, void * 	buffer, PHYSFS_uint32 	objSize, PHYSFS_uint32 	objCount)
	//int PHYSFS_close	(	PHYSFS_File * 	handle	 )

	//SDL_Surface *IMG_Load_RW(SDL_RWops *src, int freesrc)
	//Mix_Chunk *Mix_LoadWAV_RW(SDL_RWops *src, int freesrc)

	//int SDL_RWclose(struct SDL_RWops* context)


	// Private Utensils

	bool OpenFile(const char * filename, PHYSFS_File *physFS_file);

	bool GetFileLength(PHYSFS_File * handle, PHYSFS_sint64 size);

	int ReadPhysFS(PHYSFS_File * handle, void * buffer, PHYSFS_uint32 objSize, PHYSFS_uint32 objCount);

	bool ClosePhysFS(PHYSFS_File * 	handle);

	bool LoadSLD_RWops(const void* mem, int size);





	/*
	1 - Primer obriu el fitxer amb PhysFS : PHYSFS_OpenRead
	2 - Calculeu el tamany : PHYSFS_fileLength
	3 - Reserveu la memòria necessaria i llegiu tot el fitxer : PHYSFS_read
	4 - Ja el podeu tancar : PHYSFS_close
	5 - Crear un RWOps des de memoria : SDL_RWFromConstMem
	Ja hem de poder carregar imatges i audio amb les funcions alternatives de les llibreries de imatge i so : IMG_Load_RW i Mix_LoadWAV_RW
	Bonus : a veure si trobeu com fer que la memòria del buffer s'alliberi correctament ;)
	* /

};

#endif // __j1PHYSFS_H__


*/