#include "Globals.h"
#include "Application.h"

#ifndef _BULLET_H_
#define _BULLET_H_

class Bullet
{
public:
	Application* app;

	SDL_Rect rects[3];
	unsigned int source_index, update_counter;
	bool alive;

	Bullet(Application* app);
	~Bullet(){}

	void Update();
	void Print();
	void Spawn(unsigned int x, unsigned int y);

	bool CheckCollisionBricks();
	bool CheckCollisionBalloons();
};




#endif