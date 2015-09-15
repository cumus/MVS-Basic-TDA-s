#include "Module.h"
#include "Globals.h"
#include "Application.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

enum fx_sound
{
	BALLOON_POP,
	COIN
};

class ModuleAudio : public Module
{
private:

	Mix_Music* music;
	Mix_Chunk fx[2];

public:

	char* music_paths[19];

	ModuleAudio(Application* app);
	ModuleAudio(const ModuleAudio& audio);
	bool Init();
	bool CleanUp();

	bool PlayMusic(const unsigned int position); // Play indicated music
	void PlayFx(fx_sound fx); // Play a previously loaded WAV
	
	void ResumeMusic(); // Resume music
	void PauseMusic(); // Pause (free) music
	void StopMusic(); // Stop music
};

#endif