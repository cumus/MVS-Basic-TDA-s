#include "Globals.h"
#include"Application.h"


#ifndef __Harpoon_H__
#define __Harpoon_H__

class Harpoon
{
public:
	Application* app;

	SDL_Rect head_rect, body_rect;
	int source_index;

	int update_counter, length;
	bool alive;

	Harpoon(Application* app);
	~Harpoon(){}

	void Shoot_Harpoon(unsigned int y, unsigned int x);
	void Shoot_Grapple(unsigned int y, unsigned int x);

	void Update();
	void Print();

	bool Check_Collision_Harpoon_Balloon();
	bool Check_Collision_Harpoon_Brick();

};
#endif