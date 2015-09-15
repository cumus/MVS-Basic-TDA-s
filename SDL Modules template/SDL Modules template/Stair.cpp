#include "Stair.h"



Stair::Stair(Application* app, unsigned int x, unsigned int y, unsigned int size) :
		app(app),
		rects(NULL),
		rect({ x * app->windowModule->scale, y * app->windowModule->scale, 22 * app->windowModule->scale, size * 8 * size * app->windowModule->scale })
{
	rects = new DynArray<SDL_Rect>(size);

	for (unsigned int i = 0; i < size; i++)
	{
		rects->push_back({ x * app->windowModule->scale, (y + (i * 8)) * app->windowModule->scale, 22 * app->windowModule->scale, 8 * app->windowModule->scale });
	}
}

Stair::~Stair()
{
	if (rects != NULL){ delete rects; }
}

void Stair::Print()
{
	for (unsigned int i = 0; i < rects->Count(); i++)
	{
		app->renderModule->Print(app->texturesModule->bricks_sprite, &app->entityManagerModule->source_stair_rect, rects->at(i));
	}

}
