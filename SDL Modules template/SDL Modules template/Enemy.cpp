#include "Enemy.h"

Enemy::Enemy(Application* app, unsigned int position_in_list, unsigned int x, unsigned int y, unsigned int type) :
app(app),
position_in_list(position_in_list)
{
	rect = { x * app->windowModule->scale, y * app->windowModule->scale, 32 * app->windowModule->scale, 32 * app->windowModule->scale };

	switch (type)
	{
	case 0: source_index =  0; lives = 2; break;
	case 1: source_index = 16; lives = 2; break;
	case 2: source_index = 26; lives = 1; break;
	case 3: source_index = 48; lives = 2; break;
	case 4: source_index = 59; lives = 2; break;
	case 5: source_index = 74; lives = 1; break;
	}
	
}

void Enemy::Update()
{

}


void Enemy::Print()
{
	app->renderModule->Print(app->texturesModule->enemies_sprite, &app->entityManagerModule->source_enemy_rect[source_index], &rect);
}

void Enemy::Hit()
{
	if (--lives == 0)
	{
		for (unsigned int i = position_in_list + 1; i < app->entityManagerModule->balloons.Count(); i++)
		{
			(*app->entityManagerModule->balloons.at(i))->position_in_list--;
		}
		app->entityManagerModule->balloons.Delete_Element_At(position_in_list);
	}
}

