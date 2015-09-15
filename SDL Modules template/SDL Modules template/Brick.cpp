#include "Brick.h"



Brick::Brick(Application* app, int position_in_list, unsigned int x, unsigned int y, unsigned int type, unsigned int power_up_alive)
{
	this->app = app;
	this->position_in_list = position_in_list;
	this->type = type;
	if (power_up_alive == 1)
	{
		this->power_up_alive = true;
	}

	if (type < 12)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			(4 - (type/3)) * 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	}
	else if (type < 14)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			8 * app->windowModule->scale, 32 * app->windowModule->scale };
	}
	else
	{
		switch (type)
		{
		case 14:
			rect = { x * app->windowModule->scale, y * app->windowModule->scale,
				8 * app->windowModule->scale, 16 * app->windowModule->scale };
			break;
		case 15:
			rect = { x * app->windowModule->scale, y * app->windowModule->scale,
				8 * app->windowModule->scale, 24 * app->windowModule->scale };
			break;
		}
	}
	//unbreakeables bricks
	if (type > 15 && type < 25)
	{		
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			16 * app->windowModule->scale, 8 * app->windowModule->scale };
	}
	else if (type > 24 && type < 34)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			8 * app->windowModule->scale, 16 * app->windowModule->scale };
	}
	else if (type > 33 && type < 39)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			8 * app->windowModule->scale, 8 * app->windowModule->scale };
	}
	else if (type == 40)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			8 * app->windowModule->scale, 32 * app->windowModule->scale };

	}

}

void Brick::Print()
{
	app->renderModule->Print(app->texturesModule->bricks_sprite, &app->entityManagerModule->source_brick_rect[type], &rect);
}

void Brick::Hit()
{
	if (power_up_alive == true)
	{
		app->entityManagerModule->powerups.push_back(new PowerUp(app, app->entityManagerModule->powerups.Count(), rand() % 13, rect.x, rect.y));
	}
	
	if (type < 16)
	{
		app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), type + 14, rect.x, rect.y));

		for (unsigned int i = position_in_list + 1; i < app->entityManagerModule->bricks.Count(); i++)
		{
			(*app->entityManagerModule->bricks.at(i))->position_in_list--;
		}
		app->entityManagerModule->bricks.Delete_Element_At(position_in_list);

	}
}

