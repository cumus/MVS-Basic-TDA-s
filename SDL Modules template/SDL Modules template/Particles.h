#include "Globals.h"
#include "Application.h"

#ifndef __Particles_H__
#define __Particles_H__


class Particles
{
public:
	Application* app;

	SDL_Rect rect;
	int position_in_list;
	unsigned int quantity, update_counter, source_index;

	Particles(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y);
	~Particles(){}

	void Update();
	void Print();

};
#endif