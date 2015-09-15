#include "ModuleTitle.h"

ModuleTitle::ModuleTitle(Application* app) : Module(app), insert_coin_pressed(false), ticks(0)
{
	for (int i = 0; i < 4; i++)
	{
		source_rect_index[i] = 0;
		update_counter[i] = 0;
		falling[i] = true;
	}
	balloon_source_rect[0] = { 1536,  16, 78, 88 }; // P
	balloon_source_rect[1] = { 1614,  27, 55, 66 }; // A
	balloon_source_rect[2] = { 1536, 104, 66, 64 }; // N
	balloon_source_rect[3] = { 1614, 104, 57, 51 }; // G
	balloon_source_rect[4] = { 0, 0, 48, 40 };

	for (int i = 0; i < 4; i++){ source_rect[i] = { i * 384, 0, 384, 240 }; }
	source_rect[4] = { 1536, 0, 176, 15 };
}

bool ModuleTitle::Init()
{
	rect = { 0, 0, 384 * app->windowModule->scale, 240 * app->windowModule->scale };
	insert_coin_rect = { 100 * app->windowModule->scale, 200 * app->windowModule->scale, 177 * app->windowModule->scale, 15 * app->windowModule->scale };

	gravity[0] = 1 * app->windowModule->scale;
	gravity[1] = 3 * app->windowModule->scale;
	gravity[2] = 1 * app->windowModule->scale;
	gravity[3] = 2 * app->windowModule->scale;

	balloon_rects[0] = { 384 * app->windowModule->scale, 0 * app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_rects[1] = { -200 * app->windowModule->scale, -200 * app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_rects[2] = { 544 * app->windowModule->scale, -200 * app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_rects[3] = { -200 * app->windowModule->scale, -500 * app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };

	horizontal_limits[0] =  88 * app->windowModule->scale; //53
	horizontal_limits[1] = 130 * app->windowModule->scale; //69
	horizontal_limits[2] = 192 * app->windowModule->scale; //50
	horizontal_limits[3] = 230 * app->windowModule->scale; //50

	for (int i = 0; i < 4; i++){ source_rect_index[i] = 0; update_counter[i] = 0; falling[i] = true; }

	insert_coin_pressed = false;
	ticks = 0;

	app->audioModule->PlayMusic(18);

	return true;
}

update_status ModuleTitle::Update()
{	
	// Inital screens
	if (ticks < 30)       { app->renderModule->Print(app->texturesModule->title_sprite, &source_rect[0], &rect); }
	else if (ticks < 60)  { app->renderModule->Print(app->texturesModule->title_sprite, &source_rect[1], &rect); }
	else if (ticks < 180) { app->renderModule->Print(app->texturesModule->title_sprite, &source_rect[2], &rect); }

	// Begginning animation:
	else if (ticks < 300) { Update_Balloons(); }

	// Title
	else if(ticks < 360) { app->renderModule->Print(app->texturesModule->title_sprite, &source_rect[3], &rect); }
	
	else
	{
		if (ticks == 740) { app->audioModule->StopMusic(); }

		// Check for Coins
		if (app->inputModule->key[SDL_SCANCODE_5] == 1)
		{
			if (!insert_coin_pressed)
			{
				app->Add_Coin();
				app->audioModule->StopMusic();
				insert_coin_pressed = true;
			}
		}
		else { insert_coin_pressed = false; }

		// Title
		if (app->coins == 0)
		{
			if (ticks > 7200) { return CHANGE_TO_TITLE; }
			else
			{
				app->renderModule->Print(app->texturesModule->title_sprite, &source_rect[3], &rect);
				if (ticks % 60 < 30) { app->renderModule->Print(app->texturesModule->title_sprite, &source_rect[4], &insert_coin_rect); }
			}
		}

		// Ask 1 or 2 Players
		else
		{
			app->fontManagerModule->Write_On_Screen("Push start button", 140 * app->windowModule->scale, 100 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
			app->fontManagerModule->Write_On_Screen(         "Credits:", 250 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
			app->fontManagerModule->Write_On_Screen(         app->coins, 320 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);

			if (app->coins == 1){ app->fontManagerModule->Write_On_Screen("1 player", 160 * app->windowModule->scale, 120 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
			else
			{
				app->fontManagerModule->Write_On_Screen("1 or 2 players", 150 * app->windowModule->scale, 120 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);

				if (app->inputModule->key[SDL_SCANCODE_2] == 1)
				{
					app->coins -= 2;
					app->player_2_enabled = true;
					return CHANGE_TO_CHOOSE_CITY;
				}
			}
			//app->fontManagerModule->Write_On_Screen(   "1 player", 150 * app->windowModule->scale, 120 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);

			if (app->inputModule->key[SDL_SCANCODE_1] == 1)
			{
				app->coins--;
				return CHANGE_TO_CHOOSE_CITY;
			}
		}
	}

	ticks++;

	return UPDATE_CONTINUE;
}

void ModuleTitle::Update_Balloons()
{
	for (unsigned int i = 0; i < 4; i++)
	{
		if (source_rect_index[i] == 0)
		{
			// HORIZONTAL
			if (i % 2 == 0) // P, N
			{
				if (balloon_rects[i].x >= horizontal_limits[i]) { balloon_rects[i].x -= 5 * app->windowModule->scale; }
				else { source_rect_index[i]++; update_counter[i] = 0; app->audioModule->PlayFx(BALLOON_POP); }
			}
			else // A, G
			{
				if (balloon_rects[i].x <= horizontal_limits[i]) { balloon_rects[i].x += 5 * app->windowModule->scale; }
				else { source_rect_index[i]++; update_counter[i] = 0; app->audioModule->PlayFx(BALLOON_POP); }
			}

			// VERTICAL
			if (falling[i])
			{
				// UPDATE gravity
				if (update_counter[i] > 1)
				{ 
					update_counter[i] = 0;
					gravity[i] += app->windowModule->scale;
				}
				else { update_counter[i]++; }

				// UPDATE POSITION
				if (balloon_rects[i].y < 200 * app->windowModule->scale) { balloon_rects[i].y += gravity[i]; }
				else
				{
					falling[i] = false;
					gravity[i] = 10 * app->windowModule->scale;
					update_counter[i] = 0;
				}
			}
			else
			{
				// UPDATE gravity
				if (update_counter[i] > 1)
				{
					update_counter[i] = 0;
					gravity[i] -= app->windowModule->scale;
				}
				else { update_counter[i]++; }

				// UPDATE POSITION
				balloon_rects[i].y -= gravity[i];
			}

			// PRINT BALLOON
			app->renderModule->Print(app->texturesModule->balls_sprite, &balloon_source_rect[4], &balloon_rects[i]);
		}
		
		else if (source_rect_index[i] < 6)
		{
			// PRINT PARTICLES
			app->renderModule->Print(app->texturesModule->particles_sprite, &app->entityManagerModule->particles_source_rect[source_rect_index[i] - 2], &balloon_rects[i]);

			// UPDATE update_counter
			if (update_counter[i] > 3)
			{
				update_counter[i] = 0;
				source_rect_index[i]++;

				if (source_rect_index[i] == 6)
				{
					// UPDATE LETTER RECTANGLES
					switch (i)
					{
					case 0: balloon_rects[i] = {  72 * app->windowModule->scale, 38 * app->windowModule->scale, 78 * app->windowModule->scale, 88 * app->windowModule->scale }; break;
					case 1: balloon_rects[i] = { 130 * app->windowModule->scale, 52 * app->windowModule->scale, 55 * app->windowModule->scale, 66 * app->windowModule->scale }; break;
					case 2: balloon_rects[i] = { 192 * app->windowModule->scale, 29 * app->windowModule->scale, 66 * app->windowModule->scale, 64 * app->windowModule->scale }; break;
					case 3: balloon_rects[i] = { 230 * app->windowModule->scale, 50 * app->windowModule->scale, 57 * app->windowModule->scale, 51 * app->windowModule->scale }; break;
					}
				}
			}
			else{ update_counter[i]++; }
		}

		else
		{
			// PRINT LETTERS
			app->renderModule->Print(app->texturesModule->title_sprite, &balloon_source_rect[i], &balloon_rects[i]);
		}
	}
}
