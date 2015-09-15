#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef __Enemy_H__
#define __Enemy_H__

class Enemy
{
public:
	Application* app;

	SDL_Rect rect;
	unsigned int source_index;

	unsigned int position_in_list;

	unsigned int lives;

	Enemy(Application* app, unsigned int position_in_list, unsigned int x, unsigned int y, unsigned int type);
	~Enemy();

	void Update();
	void Print();
	void Hit();
};
#endif