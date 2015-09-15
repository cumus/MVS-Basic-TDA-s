#include "Globals.h"
#include "Application.h"
#include "Harpoon.h"
#include "Stair.h"
#include "Bullet.h"


#ifndef __Player_H__
#define __Player_H__

enum PlayerState
{
	LEFT,
	RIGHT,
	ON_STAIR,
	STILL,
	SHOOT_LEFT,
	SHOOT_RIGHT,
	HIT
};

enum Hit_State
{
	HIT_LEFT_UP,
	HIT_LEFT_DOWN,
	HIT_RIGHT_UP,
	HIT_RIGHT_DOWN
};

enum Weapon
{
	WEAPON_DOUBLE_HARPOON,
	WEAPON_HARPOON,
	WEAPON_GRAPPLE,
	WEAPON_SHOTGUN
};

class Player
{
public:
	Application* app;

	// Rectangles
	SDL_Rect rect;
	SDL_Rect source_rect[25];
	unsigned int source_index, update_counter;
	
	// Shield
	unsigned int shield_source_index, shield_update_counter,invincibility_counter;
	bool shielded, invincible;

	// Weapons
	Harpoon* harpoon1;
	Harpoon* harpoon2;
	Bullet* bullets[15];
	Weapon current_weapon;
	unsigned int shoot_update_counter;
	bool shoot_key_pressed;

	// Player state
	PlayerState state;
	unsigned int score, lives;
	bool alive;

	// Hit resources
	Hit_State hit_State;
	unsigned int player_gravity, ticks, height;
	
	// Current Stair
	Stair* current_stair;
	unsigned int stair_update_counter;

	Player(Application* app, bool player1);
	~Player();

	void LeftTrigger();
	void RightTrigger();
	void UpTrigger();
	void DownTrigger();
	void Shoot();
	void Still();
	void Hit(const SDL_Rect* killer);
	
	void ActivateShield();
	void MakeInvincible();


	void Update();
	void Print();
	void PrintBullets();
	void Reset(const unsigned int x, const unsigned int y);

	bool Check_Collision_Player_Brick_Horizontal();
	bool Check_Collision_Player_Verticals();
	bool Check_Collision_Player_Stair();

};
#endif
