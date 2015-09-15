#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef _BRICK_H_
#define _BRICK_H_

class Brick
{
	public:
		Application* app;

		SDL_Rect rect;
		unsigned int type;
		int position_in_list;
		bool power_up_alive;

		Brick(Application* app, int position_in_list, unsigned int x, unsigned int y, unsigned int type, unsigned int power_up_alive);
		~Brick(){}

		void Print();
		void Hit();
};





#endif _BRICK_H_