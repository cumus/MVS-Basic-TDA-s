#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Balloon.h"
#include "Enemy.h"
#include "Stair.h"
#include "Brick.h"
#include "Particles.h"
#include "PowerUp.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__


class ModuleEntityManager : public Module{
public:

	SDL_Rect harpoon_source_rect[25];
	SDL_Rect shotgun_source_rect[5];
	SDL_Rect shield_source_rect[2];

	DynArray<Brick*> bricks;
	SDL_Rect source_brick_rect[41];

	DynArray<Stair*> stairs;
	SDL_Rect source_stair_rect;

	DynArray<Balloon*> balloons;
	SDL_Rect source_balloon_rect[12];
	float balloon_speed;

	DynArray<Enemy*> enemies;
	SDL_Rect source_enemy_rect[74];

	DynArray<Particles*> particles;
	SDL_Rect particles_source_rect[150];

	DynArray<PowerUp*> powerups;
	SDL_Rect powerup_source_rect[23];

	bool stop_time, slow_time, dynamite;
	unsigned int stop_time_counter, slow_time_counter, dynamite_counter;

	ModuleEntityManager(Application* app);
	bool Init();
	update_status Update();
	bool CleanUp();

	void StopTime();
	void SlowTime();
	void Dynamite();
	bool DynamiteUpdate();
};

#endif
