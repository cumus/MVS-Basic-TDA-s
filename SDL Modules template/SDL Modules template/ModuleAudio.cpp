
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(Application* app) : Module(app), music(NULL) {}

ModuleAudio::ModuleAudio(const ModuleAudio& audio) : Module(audio.app), music(NULL) {}

bool ModuleAudio::Init()
{
	music = NULL;

	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);

	if (initted != flags){ return false; }

	if (Mix_OpenAudio(44100, AUDIO_U8 /*MIX_DEFAULT_FORMAT*/, 2, 2048) == -1){ return false; } // Initialize SDL_mixer

	// set music paths:
	//music_paths[0]  = "music/01a - Mt. Fuji (Arcade).wav";
	//...
	
	// set chunk paths:
	//Mix_Chunk* chunk = NULL;
	//chunk = Mix_LoadWAV("music/bolapeta.wav"); if (chunk == NULL) { return false; }   fx[0] = *chunk; // BALLOON_POP
	//chunk = Mix_LoadWAV("music/coin.wav");     if (chunk == NULL) { return false; }   fx[1] = *chunk; // COIN
	//...

	return true;
}

bool ModuleAudio::CleanUp()
{
	if (music != NULL){ Mix_FreeMusic(music); } // free music

	//for (unsigned int i = 0; i < "max chunk num"; i++){ Mix_FreeChunk(&fx[i]); } // free chuncks

	Mix_CloseAudio(); // close audio subsystem

	//while (Mix_Init(0)){ Mix_Quit(); } //each call to Mix_Init may set different flags
	Mix_Quit();

	return true;
}

bool ModuleAudio::PlayMusic(const unsigned int position)
{
	if (music != NULL){ Mix_FreeMusic(music); } // free previous music

	music = Mix_LoadMUS(music_paths[position]); // load new music
	if (music == NULL){ return false; }

	if (Mix_PlayMusic(music, -1) < 0){ return false; } // check if music is played

	return true;
}

void ModuleAudio::PlayFx(fx_sound id)
{
	Mix_PlayChannel(-1, &fx[int(id)], 0);
}

void ModuleAudio::ResumeMusic()
{
	Mix_ResumeMusic();
}

void ModuleAudio::PauseMusic()
{
	Mix_PauseMusic();
}

void ModuleAudio::StopMusic()
{
	if (music != NULL) // free previous music
	{
		Mix_FreeMusic(music);
		music = NULL;
	} 
}