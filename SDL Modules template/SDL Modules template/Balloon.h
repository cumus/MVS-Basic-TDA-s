#include "Globals.h"
#include "Application.h"
#include "Particles.h"
#include "Module.h"

#ifndef __Balloon_H__
#define __Balloon_H__


enum BALL_TYPE
{
	RED_1,
	BLUE_1,
	GREEN_1,

	RED_2,
	BLUE_2,
	GREEN_2,

	RED_3,
	BLUE_3,
	GREEN_3,

	RED_4,
	BLUE_4,
	GREEN_4
};

enum BALLOON_STATE_VERTICAL
{
	BALLOON_UP,
	BALLOON_DOWN
};

enum BALLOON_STATE_HORIZONTAL
{
	BALLOON_LEFT,
	BALLOON_RIGHT
};

class Balloon
{
public:

	Application* app;

	int position_in_list;

	float gravity;
	float position_X, position_Y;

	unsigned int ticks;

	BALL_TYPE type;
	BALLOON_STATE_VERTICAL state_balloon_V;
	BALLOON_STATE_HORIZONTAL state_balloon_H;
	SDL_Rect rect;
	
	Balloon(Application* app, unsigned int position_in_list, int x, int y, int type, int direction);
	~Balloon(){}

	void Update();
	void Print();
	void Hit();
	void Reduce_Balloon_Size();
	void Restart_Movement_Balloons_hit();

	void Size1_Check_Collision_Balloon_Players();
	void Size4_Check_Collision_Balloon_Players();

	void Check_Collision_Balloon_Bricks();

};
#endif