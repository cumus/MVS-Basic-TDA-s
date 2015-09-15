#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef __Stair_H__
#define __Stair_H__

class Stair
{
public:
	Application* app;

	DynArray<SDL_Rect>* rects;
	SDL_Rect rect;

	Stair(Application* app, unsigned int x, unsigned int y, unsigned int size);
	~Stair();

	void Print();
};
#endif