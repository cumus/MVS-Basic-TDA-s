#include "Application.h"
#include "Globals.h"

#ifndef __Time_Count_H__
#define __Time_Count_H__

class Time_Count
{
public:

	Application* app;

	SDL_Rect rect[4];
	SDL_Rect source_rect[11];
	int source_index[3];

	int current_time;
	time_t	timer;

	Time_Count(Application* app);
	~Time_Count(){}

	void Update();
	void Update_Source_Index();
	void Reset(unsigned int time);
	void Print_Timer();

};

#endif