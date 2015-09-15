#include "Player.h"

Player::Player(Application* app, bool player1) :
app(app),
lives(3),
source_index(17),
score(0),
stair_update_counter(0),
shield_update_counter(0),
shield_source_index(0),
invincibility_counter(0),
shielded(false),
invincible(false),
shoot_key_pressed(false),
state(STILL),
current_weapon(WEAPON_HARPOON),
hit_State(HIT_RIGHT_UP),
current_stair(NULL)
{
	harpoon1 = new Harpoon(app);
	harpoon2 = new Harpoon(app);

	for (unsigned int i = 0; i < 15; i++){ bullets[i] = new Bullet(app); }

	rect = { 0, 0, 32 * app->windowModule->scale, 32 * app->windowModule->scale };

	unsigned int y_coor = (player1? 0 : 32);

	for (unsigned int i = 0; i < 23; i++) { source_rect[i] = { i * 32, y_coor, 32, 32 }; }
	source_rect[23] = { 736, y_coor, 41, 32 };
	source_rect[24] = { 777, y_coor, 41, 32 };
}


Player::~Player()
{
	delete harpoon1;
	delete harpoon2;
}


void Player::LeftTrigger()
{
	if (state == LEFT)
		{
			if (update_counter > 4) // ticks till update
			{
				if (source_index < 9){ source_index++; }
				else { source_index = 5; }
				update_counter = 0;
			}

			if (rect.x > 8 * app->windowModule->scale)
			{
				rect.x -= 2 * app->playerModule->player_speed;

				if(Check_Collision_Player_Brick_Horizontal()) 
				{
					rect.x += 2 * app->playerModule->player_speed;
				}
			}
		}

	else if (state == SHOOT_LEFT || state == SHOOT_RIGHT) // was shooting
	{
		if (update_counter > 4)
		{
			state = LEFT;
			source_index = 5;
			update_counter = 0;
		}
	}
	else if (state == RIGHT || state == STILL)// change of direction
	{
		state = LEFT;
		source_index = 5;
		update_counter = 0;
	}
}

void Player::RightTrigger()
{
	if (state == RIGHT)
	{
		if (update_counter > 4) // ticks till update
		{
			if (source_index < 4){ source_index++; }
			else { source_index = 0; }
			update_counter = 0;
		}

		if (rect.x < (SCREEN_WIDTH - 40) * app->windowModule->scale)
		{
			rect.x += 2 * app->playerModule->player_speed;

			if (Check_Collision_Player_Brick_Horizontal())
			{
				rect.x -= 2 * app->playerModule->player_speed;
			}
		}

	}
	else if (state == SHOOT_LEFT || state == SHOOT_RIGHT) // was shooting
	{
		if (update_counter > 4)
		{
			state = RIGHT;
			source_index = 0;
			update_counter = 0;
		}
	}
	else if (state == LEFT || state == STILL)// change of direction
	{
		state = RIGHT;
		source_index = 0;
		update_counter = 0;
	}
}

void Player::UpTrigger()
{
	if (current_stair == NULL)
	{
		if (stair_update_counter > 5)
		{
			if (Check_Collision_Player_Stair())
			{
				stair_update_counter = 0;
				source_index = 15;
				state = ON_STAIR;
			}
		}
		else{ stair_update_counter++; }
	}
	else
	{
		if (rect.y + rect.h > current_stair->rect.y) // still on stair
		{
			rect.y -= app->playerModule->player_speed;

			if (update_counter > 8) // ticks till update
			{
				if (source_index < 13){ source_index++; }
				else { source_index = 10; }
				update_counter = 0;
			}
		}

		else if (stair_update_counter < 10) // showing bun
		{
			stair_update_counter++;
			source_index = 16;
		}
		else // no longer on stair
		{
			state = STILL;
			source_index = 17;
			rect.y = current_stair->rect.y - rect.h;
			stair_update_counter = 0;
			current_stair = NULL;
		}
	}

}

void Player::DownTrigger()
{
	if (current_stair == NULL)
	{
		if (stair_update_counter > 5)
		{
			if (rect.y < 168 && Check_Collision_Player_Stair())
			{
				stair_update_counter = 0;
				source_index = 16;
				state = ON_STAIR;
			}
		}
		else{ stair_update_counter++; }
	}
	else
	{
		if (rect.y + rect.h > current_stair->rect.y + current_stair->rect.h) // still on stair
		{
			rect.y += app->playerModule->player_speed;

			if (update_counter > 8) // ticks till update
			{
				if (source_index > 10){ source_index--; }
				else { source_index = 13; }
				update_counter = 0;
			}
		}
		else // no longer on stair
		{
			state = STILL;
			source_index = 17;
			rect.y = current_stair->rect.y - rect.h;
			stair_update_counter = 0;
			current_stair = NULL;
		}
	}
}


void Player::Shoot()
{
	if (shoot_key_pressed || state == HIT) { return; }
	shoot_key_pressed = true;

	switch (current_weapon)
	{
	case WEAPON_DOUBLE_HARPOON:
		if (!harpoon2->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon2->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon2->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon2->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
			}
		}

		else if (!harpoon1->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon1->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon1->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon1->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
			}
		}
		break;

	case WEAPON_HARPOON:
		if (!harpoon1->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon1->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon1->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon1->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
			}
		}
		break;

	case WEAPON_GRAPPLE:
		if (!harpoon1->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon1->Shoot_Grapple(rect.y, rect.x + (14 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon1->Shoot_Grapple(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon1->Shoot_Grapple(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
			}
		}
		break;

	case WEAPON_SHOTGUN:
		shoot_update_counter = 0;

		for (unsigned int i = 0; i < 15; i++)
		{
			if (!bullets[i]->alive)
			{
				if (state == RIGHT || source_index == 17) // leaning left
				{
					source_index = 18;
					update_counter = 0;
					bullets[i]->Spawn(rect.x + (16 * app->windowModule->scale), rect.y - (9 * app->windowModule->scale));
					app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
					state = SHOOT_RIGHT;
				}
				else if (state == LEFT || source_index == 19) // leaning right
				{
					source_index = 20;
					update_counter = 0;
					bullets[i]->Spawn(rect.x + (12 * app->windowModule->scale), rect.y - (9 * app->windowModule->scale));
					app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
					state = SHOOT_LEFT;
				}
				else // on stairs
				{
					bullets[i]->Spawn(rect.x + (14 * app->windowModule->scale), rect.y - (9 * app->windowModule->scale));
					app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				}
				break;
			}
		}
		break;
	}
}


void Player::Still()
{
	if (update_counter > 4)
	{
		switch (state)
		{
		case LEFT:
		case SHOOT_LEFT:
			state = STILL;
			source_index = 19;
			break;

		case RIGHT:
		case SHOOT_RIGHT:
			state = STILL;
			source_index = 17;
			break;
		case ON_STAIR:
			source_index = 15;
			break;
		default:
			break;
		}
	}
}

void Player::Hit(const SDL_Rect* killer)
{
	if (shielded) // kill shield if shielded
	{
		shielded = false;
		MakeInvincible();
		return;
	}
	else if (invincible) return;

	if (rect.x + (rect.w / 2) <= killer->x + (killer->w / 2))
	{
		source_index = 21;
		hit_State = HIT_LEFT_UP;

	}
	else
	{
		source_index = 22;
		hit_State = HIT_RIGHT_UP;
	}

	alive = false;
	ticks = 0;
	player_gravity = 13;
	height = rect.y;
	update_counter = 0;
	shoot_update_counter = 0;
	state = HIT;
	app->sceneModule->game_state = PLAYER_KILLED;
	app->sceneModule->update_counter = 0;
}


void Player::ActivateShield()
{
	shielded = true;
	invincible = false;
}


void Player::Update()
{
	// PLAYER NORMAL___________________________________________________________________________________________________________________
	if (app->sceneModule->game_state == PLAYING)
	{
		// if no floor: make fall
		if (rect.y < 168 * app->windowModule->scale && state != ON_STAIR) // not on ground nor on stairs
		{
			if (!Check_Collision_Player_Verticals()) { rect.y += 4 * app->windowModule->scale; } // no bricks nor stairs bellow -> fall
		}

		update_counter++;
		
		if (shoot_update_counter < 10){ shoot_update_counter++; }
		else if (current_weapon != WEAPON_SHOTGUN) { shoot_key_pressed = false; shoot_update_counter = 0; }
		
		// update shield
		if(shielded)
		{
			if(shield_update_counter > 5)
			{
				shield_update_counter = 0;
				shield_source_index = (shield_source_index == 0? 1 : 0);
			}
			else
			{
				shield_update_counter++;
			}
		}

		if (harpoon2->alive){ harpoon2->Update(); }
		if (harpoon1->alive){ harpoon1->Update(); }

		for (unsigned int i = 0; i < 15; i++)
		{
			if (bullets[i]->alive){ bullets[i]->Update(); }
		}
	}



	// PLAYER HIT___________________________________________________________________________________________________________________
	if (state == HIT)
	{
		if (shoot_update_counter > 30)				//4rth bounce -> player killed(this)
		{
			switch (hit_State)
			{
			case HIT_LEFT_UP:
				//rect.x -= app->windowModule->scale;
				if ((rect.y > 8 * app->windowModule->scale) && player_gravity != 0) // && no collision with bricks
				{
					rect.x -= 2;
					rect.y = rect.y - player_gravity;
					ticks--;
					if (ticks % 3 == 0) player_gravity--;
					if (rect.x < 8 * app->windowModule->scale)hit_State = HIT_RIGHT_UP;
					/*
					height = rect.y;
					update_counter = 0;
					hit_State = HIT_LEFT_DOWN;*/
				}
				else
				{
					hit_State = HIT_LEFT_DOWN;
					source_index = 23;
					player_gravity = 0;
					ticks = 1;
					//rect.y = height - ((6 * app->windowModule->scale) + ((update_counter * update_counter) / 9));
				}
				break;

			case HIT_LEFT_DOWN:
				//rect.x -= app->windowModule->scale;

				if (rect.y + rect.h < 199 * app->windowModule->scale) // && no collision with bricks
				{
					rect.x -= 2;
					rect.y = rect.y + player_gravity;
					ticks--;
					if (ticks % 3 == 0) player_gravity++;
					if (rect.x < 8 * app->windowModule->scale)hit_State = HIT_RIGHT_DOWN;
					/*height = rect.y;
					update_counter = 0;
					hit_State = HIT_LEFT_UP;*/
				}
				else
				{
					hit_State = HIT_LEFT_UP;
					ticks = 1;
					source_index = 23;
					player_gravity=player_gravity-3;
					//rect.y = height + ((6 * app->windowModule->scale) -  ((update_counter * update_counter) / 9));
				}
				break;

			case HIT_RIGHT_UP:
				//rect.x += app->windowModule->scale;
				if ((rect.y > 8 * app->windowModule->scale) && player_gravity != 0) // && no collision with bricks
				{
					rect.x += 2;
					rect.y = rect.y - player_gravity;
					ticks--;
					if (ticks % 3 == 0) player_gravity--;
					if (rect.x - rect.w > 376 * app->windowModule->scale)hit_State = HIT_LEFT_UP;
					//hit_State = HIT_LEFT_UP;
				}
				else
				{
					hit_State = HIT_RIGHT_DOWN;
					source_index = 24;
					player_gravity = 0;
					ticks = 1;
					
					//rect.y = height - ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;

			case HIT_RIGHT_DOWN:
				//rect.x += app->windowModule->scale;

				if (rect.y + rect.h < 199 * app->windowModule->scale)
				{

					rect.x += 2;
					rect.y = rect.y + player_gravity;
					ticks--;
					if (ticks % 3 == 0) player_gravity++;
					if (rect.x + rect.w > 376 * app->windowModule->scale)hit_State = HIT_LEFT_DOWN;
					//height = rect.y;
					//hit_State = HIT_LEFT_UP;
				}
				// else if() no collision with bricks
				// { height = rect.y
				else
				{
					hit_State = HIT_RIGHT_UP;
					ticks = 1;
					source_index = 24;
					player_gravity = player_gravity - 3;;
					//rect.y = height + ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;
			}
		}

		else
		{
			shoot_update_counter++;

			if (shoot_update_counter == 30)
			{
				rect.x -= 5 * app->windowModule->scale;
				rect.w = 41 * app->windowModule->scale;
				source_index += 2;
			}
		}

		return;
	}

}


void Player::Print()
{
	if(shielded)
	{
		SDL_Rect shield_rect;
		switch (state)
		{
		case        LEFT: shield_rect = { rect.x + (4 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		case       RIGHT: shield_rect = { rect.x - (4 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		case    ON_STAIR: shield_rect = { rect.x, rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		case       STILL: shield_rect = { rect.x - app->windowModule->scale, rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		case  SHOOT_LEFT: shield_rect = { rect.x - (2 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		case SHOOT_RIGHT: shield_rect = { rect.x + (2 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		case         HIT: shield_rect = { rect.x - app->windowModule->scale, rect.y - (4 * app->windowModule->scale), 32 * app->windowModule->scale, 39 * app->windowModule->scale }; break;
		}
		
		app->renderModule->Print(app->texturesModule->particles_sprite, &app->entityManagerModule->shield_source_rect[shield_source_index], &shield_rect);	
	}

	if (invincible && invincibility_counter < 180)
	{
		invincibility_counter++;
		if (invincibility_counter % 10 < 5 )
		{
			app->renderModule->Print(app->texturesModule->players_sprite, &source_rect[source_index], &rect);
		}
		
	}
	else {
			app->renderModule->Print(app->texturesModule->players_sprite, &source_rect[source_index], &rect);
			invincible = false;
			invincibility_counter = 0;
		 }
}

void Player::PrintBullets()
{
	for (unsigned int i = 0; i < 15; i++)
	{
		if (bullets[i]->alive){ bullets[i]->Print(); }
	}
}


void Player::Reset(const unsigned int x, const unsigned int y)
{
	rect.x = x * app->windowModule->scale;
	rect.y = y * app->windowModule->scale;
	rect.w = 32 * app->windowModule->scale;

	harpoon1->alive = false;
	harpoon2->alive = false;

	for (unsigned int i = 0; i < 15; i++){ bullets[i]->alive = false; }

	source_index = 17;
	stair_update_counter = 0;
	shield_source_index = 0;
	shield_update_counter = 0;
	invincibility_counter = 0;
	shielded = false;
	invincible = false;
	shoot_key_pressed = false;
	state = STILL;
	current_weapon = WEAPON_HARPOON;
	hit_State = HIT_RIGHT_UP;
	current_stair = NULL;
}



bool Player::Check_Collision_Player_Brick_Horizontal()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks.at(i))->rect;

		if (rect.x  -1<= tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w -1 >= tmp_rect.x
			&& rect.y-1 <= tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h -1 >= tmp_rect.y)
		{
			return true;
		}
	}
	return false;
}

bool Player::Check_Collision_Player_Verticals()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks.at(i))->rect;

		if (rect.x + app->windowModule->scale <= tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w + app->windowModule->scale >= tmp_rect.x
			&& rect.y + app->windowModule->scale <= tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h + app->windowModule->scale >= tmp_rect.y)
		{
			return true;
		}
	}

	for (unsigned int i = 0; i < app->entityManagerModule->stairs.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->stairs.at(i))->rect;

		if (rect.x + app->windowModule->scale <= tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w + app->windowModule->scale >= tmp_rect.x
			&& rect.y + app->windowModule->scale <= tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h + app->windowModule->scale >= tmp_rect.y)
		{
			return true;
		}
	}
	return false;
}

bool Player::Check_Collision_Player_Stair()
{
	SDL_Rect stair_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->stairs.Count(); i++)
	{
		// get stair rect
		stair_rect = (*app->entityManagerModule->stairs.at(i))->rect;

		if (rect.x >stair_rect.x) // player to the right
		{
			if (rect.x - stair_rect.x <= 4 * app->windowModule->scale) // player horizontaly close enough to stairs
			{
				if (rect.y + (rect.h / 2) >= stair_rect.y && rect.y + (rect.h / 2) <= stair_rect.y + stair_rect.h) // player close enough to stairs
				{
					current_stair = *app->entityManagerModule->stairs.at(i);
					rect.x = current_stair->rect.x - (2 * app->windowModule->scale);
					stair_update_counter = 0;
					update_counter = 0;
					return true;
				}
			}
		}
		else // player to the left
		{
			if (stair_rect.x - rect.x <= 4 * app->windowModule->scale) // player horizontaly close enough to stairs
			{
				if (rect.y + (rect.h / 2) >= stair_rect.y && rect.y + (rect.h / 2) <= stair_rect.y + stair_rect.h) // player close enough to stairs
				{
					current_stair = *app->entityManagerModule->stairs.at(i);
					rect.x = current_stair->rect.x - (2 * app->windowModule->scale);
					stair_update_counter = 0;
					update_counter = 0;
					return true;
				}
			}
		}
	}
	return false;
}

void Player::MakeInvincible()
{
	invincible = true;



}