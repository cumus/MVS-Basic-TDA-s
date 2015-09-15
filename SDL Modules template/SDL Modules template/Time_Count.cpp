#include "Time_Count.h"

Time_Count::Time_Count(Application* app)
{
	this->app = app;
	current_time = 100;
	time(&timer);
	
	rect[0] = { 334 * app->windowModule->scale, 9 * app->windowModule->scale, 13 * app->windowModule->scale, 13 * app->windowModule->scale };
	rect[1] = { 348 * app->windowModule->scale, 9 * app->windowModule->scale, 13 * app->windowModule->scale, 13 * app->windowModule->scale };
	rect[2] = { 362 * app->windowModule->scale, 9 * app->windowModule->scale, 13 * app->windowModule->scale, 13 * app->windowModule->scale };
	rect[3] = { 271 * app->windowModule->scale, 9 * app->windowModule->scale, 62 * app->windowModule->scale, 13 * app->windowModule->scale };

	for (int i = 0; i < 10; i ++){ source_rect[i] = {62 + (i * 13), 0, 13, 13}; }
	source_rect[10] = {0, 0, 62, 13};

	Update_Source_Index();
}

void Time_Count::Update()
{
	if (current_time > 0)
	{
		current_time--;
		time(&timer);
		Update_Source_Index();
	}
}

void Time_Count::Update_Source_Index()
{
	source_index[0] = (current_time / 100) % 10;
	source_index[1] = (current_time / 10) % 10;
	source_index[2] = current_time % 10;
}


void Time_Count::Reset(unsigned int seconds)
{
	current_time = seconds;
	time(&timer);
	Update_Source_Index();
}

void Time_Count::Print_Timer()
{
	app->renderModule->Print(app->texturesModule->timer_sprite, &source_rect[10], &rect[3]);
	app->renderModule->Print(app->texturesModule->timer_sprite, &source_rect[source_index[0]], &rect[0]);
	app->renderModule->Print(app->texturesModule->timer_sprite, &source_rect[source_index[1]], &rect[1]);
	app->renderModule->Print(app->texturesModule->timer_sprite, &source_rect[source_index[2]], &rect[2]);
}