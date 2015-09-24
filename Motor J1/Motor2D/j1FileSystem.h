#ifndef __j1FILESYSTEM_H__
#define __j1FILESYSTEM_H__

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "PhysFS/include/physfs.h"

struct Mix_Chunk;

int close_sdl_rwops(SDL_RWops *rw);

class j1FileSystem : public j1Module
{
public:

	j1App* app;

	j1FileSystem(const char* game_path, j1App* app);

	// Destructor
	virtual ~j1FileSystem();

	// Called before render is available
	bool Awake(pugi::xml_node node);

	// Called before quitting
	bool CleanUp();

	// Utility functions
	bool AddPath(const char* path_or_zip);
	bool Exists(const char* file) const;
	bool IsDirectory(const char* file) const;

	// Open for Read/Write
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;

	// SDL_RWops Utility
	void CreateRWops(const char*);

	//File Loading
	SDL_Texture* LoadIMG(const char*);
	void LoadAUDIO(char*, Mix_Chunk&);

	// Save buffer
	unsigned int Save(const char* file, const char* buffer, unsigned int size) const;


private:
	SDL_RWops* files;
};

#endif // __j1FILESYSTEM_H__