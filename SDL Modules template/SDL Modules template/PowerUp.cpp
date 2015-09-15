#include "PowerUp.h"

PowerUp::PowerUp(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y) :
app(app),
position_in_list(position_in_list),
source_index(type),
update_counter(0)
{
	rect = { x, y, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
}


void PowerUp::Update()														
{
	update_counter++;

	if (source_index > 2 && source_index < 10 && update_counter % 5 == 0)
	{
		switch (source_index)
		{
		case 3:
		case 4: source_index++; break;
		case 5: source_index = 3; break;
		case 6:
		case 7:
		case 8: source_index++; break;
		case 9: source_index = 6; break;
		default: break;
		}
	}

	if (rect.y < 184 * app->windowModule->scale)// && !Check_Collision_Bricks())
	{
		rect.y += app->windowModule->scale;
	}

	if (update_counter >= 360
		|| Check_Collision_Player(app->playerModule->player1)
		|| (app->player_2_enabled && Check_Collision_Player(app->playerModule->player2)))
	{
		Kill();
	}
}


void PowerUp::Print()
{
	if (update_counter < 300)
	{
		app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[source_index], &rect);
	}
	if (update_counter < 360)
	{
		if (update_counter % 10 < 5)
		{
			app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[source_index], &rect);
		}
	}
}

void PowerUp::Kill()
{
	for (unsigned int i = position_in_list + 1; i < app->entityManagerModule->powerups.Count(); i++)
	{
		(*app->entityManagerModule->powerups.at(i))->position_in_list--;
	}
	app->entityManagerModule->powerups.Delete_Element_At(position_in_list);
}



bool PowerUp::Check_Collision_Bricks() // cambiar player por bricks ---------> AUSIAS
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks.at(i))->rect;

		if (rect.x < tmp_rect.x + tmp_rect.w 
			&& rect.x + rect.w > tmp_rect.x 
			&& rect.y <  tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h >  tmp_rect.y )
		{
			return true; 
		}
	}
}


bool PowerUp::Check_Collision_Player(Player* player)
{
	if (   (player->harpoon1->alive && Check_Collision_Harpoons(player->harpoon1->head_rect))
		|| (player->harpoon2->alive && Check_Collision_Harpoons(player->harpoon2->head_rect))
		|| (player->rect.x + app->windowModule->scale <= rect.x + rect.w
		&&  player->rect.x + player->rect.w + app->windowModule->scale >= rect.x
		&&  player->rect.y + app->windowModule->scale <= rect.y + rect.h
		&&  player->rect.y + player->rect.h + app->windowModule->scale >= rect.y))
	{
		switch (source_index)
		{
		case 0:
			player->current_weapon = WEAPON_SHOTGUN;
			break;
		case 1:
			player->current_weapon = WEAPON_GRAPPLE;
			break;
		case 2:
			player->current_weapon = WEAPON_DOUBLE_HARPOON;
			break;
		case 3:
		case 4:
		case 5:
			app->entityManagerModule->Dynamite();
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			player->shielded = true;
			break;
		case 10:
			app->entityManagerModule->SlowTime();
			break;
		case 11:
			app->entityManagerModule->StopTime();
			break;
		case 12:
			player->lives++;
			break;
		case 13: break;
		case 14: break;
		case 15:
			app->playerModule->player1->score += 5000;
			break;
			//platano
		case 16:
			app->playerModule->player1->score += 2000;
			break;
			//sandia
		case 17:
			app->playerModule->player1->score += 4000;
			break;
			//berenjena
		case 18:
			app->playerModule->player1->score += 7000;
			break;
			//cereza
		case 19:
			app->playerModule->player1->score += 500;
			break;
			//naranja
		case 20:
			app->playerModule->player1->score += 3000;
			break;
			//limon
		case 21:
			app->playerModule->player1->score += 1000;
			break;
			//uva
		case 22:
			app->playerModule->player1->score += 6000;
			break;
		}

		return true;
	}

	return false;
}

bool PowerUp::Check_Collision_Harpoons(SDL_Rect head_rect)
{
	return (source_index > 15
		&& head_rect.x + head_rect.w >= rect.x
		&& rect.x + rect.w >= head_rect.x
		&& rect.y + rect.h >= head_rect.y
		&& head_rect.y + head_rect.h >= rect.y);
}