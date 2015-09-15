#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app),
time_count(NULL),
pause_pressed(false),
stage_cleared(false)
{}

bool ModuleScene::Init()
{
	if (time_count == NULL){ time_count = new Time_Count(app); }

	stage_cleared = false;
	game_state = READY;
	update_counter = 0;
	half_time = false;
	countdown_num = 10;
	
	ready_rect = { 165 * app->windowModule->scale, 104 * app->windowModule->scale, 54 * app->windowModule->scale, 16 * app->windowModule->scale };
	ready_source_rect = { 0, 0, 54, 16 };

	game_over_rect = { 120 * app->windowModule->scale, 104 * app->windowModule->scale, 142 * app->windowModule->scale, 16 * app->windowModule->scale };
	game_over_source_rect = { 196, 0, 142, 16 };

	time_over_rect = { 120 * app->windowModule->scale, 104 * app->windowModule->scale, 142 * app->windowModule->scale, 16 * app->windowModule->scale };
	time_over_source_rect = { 54, 0, 142, 16 };

	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };

	for (int i = 0; i < 5; i++)
	{
		livesrect_player1[i] = { (8 + 16 * i)* app->windowModule->scale, 224 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		livesrect_player2[i] = { (272 + 16 * i)* app->windowModule->scale, 224 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	}

	power_up_rect = { 96 * app->windowModule->scale, 224 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	power_up_rect2 = { 360 * app->windowModule->scale, 224 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	app->stageEndModule->next_extend = 10000;
	app->stageEndModule->next_extend_counter = 0;


	
	if (!load_stage()){ return false; }

	return true;
}

update_status ModuleScene::PreUpdate()
{
	// ADD Coin
	if (app->inputModule->key[SDL_SCANCODE_5] == 1)
	{
		if (!insert_coin_pressed){ app->Add_Coin(); insert_coin_pressed = true; }
	}
	else { insert_coin_pressed = false; }
	// STAGE CHEAT - 9: RESET STAGE
	if (app->inputModule->key[SDL_SCANCODE_9] == 1){ reset_stage(); }
	// STAGE CHEAT - 9: RESET STAGE
	if (app->inputModule->key[SDL_SCANCODE_8] == 1){ app->entityManagerModule->powerups.push_back(new PowerUp(app, app->entityManagerModule->powerups.Count(), rand() % 13, 150, 40)); }
	if (app->inputModule->key[SDL_SCANCODE_7] == 1){ stage_cleared=true; }
	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update()
{
	// PRINT ALL OBJECTS ON SCREEN
	Print_All_Objects();

	app->stageEndModule->NextExtend();

	switch (game_state)
	{
	case PLAYING:
		// PAUSE MANAGED
		if (app->inputModule->key[SDL_SCANCODE_P] == 1)
		{
			if (!pause_pressed){ Pause_Scene(); }
		}
		else{ pause_pressed = false; }

		if (!app->player_2_enabled)
		{
			if (app->inputModule->key[SDL_SCANCODE_Y] == 1 && app->coins > 1)
			{
				app->coins--;
				app->player_2_enabled = true;
				app->playerModule->player2->MakeInvincible();
			}
		}

		// STAGE CLEARED MANAGED
		if (stage_cleared)
		{
			if (update_counter > 180)
			{
				app->stage++;
				if (app->stage % 3 == 1)
				{
					app->city++;
				}
				stage_cleared = false;
				return CHANGE_TO_STAGE_END;
			}
			update_counter++;
		}
		else
		{
			//TIMER MANAGED
			if (difftime(time(NULL), time_count->timer) >= 1 && game_state == PLAYING) { time_count->Update(); }

			//CHECK HALF TIME
			if (!half_time)
			{
				if (time_count->current_time <= stage_arrangement.time_limit / 2)
				{
					app->audioModule->PlayMusic(10);
					half_time = true;
				}
			}
			
			//CHECK TIME OUT
			if (time_count->current_time == 0)
			{
				if (app->playerModule->player1->lives > 0)
				{
					app->playerModule->player1->lives--;
				}
				
				if (app->player_2_enabled)
				{ 
					if (app->playerModule->player2->lives > 0)
					{
						app->playerModule->player2->lives--;
					}
					else
					{
						app->player_2_enabled = false;
					}
				}

				update_counter = 0;
				game_state = TIME_OUT;
				app->audioModule->StopMusic();
			}

			// CHECK IF STAGE CLEARED
			else if (app->entityManagerModule->balloons.empty())
			{
				stage_cleared = true;
				update_counter = 0;
			}
		}
		break;

	case PLAYER_KILLED:
		if (update_counter > 300)
		{
			update_counter = 0;
			
			//PLAYER 1 HIT
			if (app->playerModule->player1->state == HIT)
			{
				if (app->playerModule->player1->lives > 0)
				{
					app->playerModule->player1->lives--;
					reset_stage();
				}
				else if (app->coins > 0)
				{
					app->coins--;
					app->playerModule->player1->lives = 3;
					reset_stage();
				}
				else
				{
					app->audioModule->StopMusic();
					game_state = COUNTDOWN;
					app->coins--;
				}
			}

			//PLAYER 2 HIT
			else if (app->playerModule->player2->lives > 0)
			{
				app->playerModule->player2->lives--;
				reset_stage();
			}
			else if (app->coins > 0)
			{
				app->coins--;
				app->playerModule->player2->lives = 3;
				app->player_2_enabled = false;
				reset_stage();
			}
			else
			{
				app->audioModule->StopMusic();
				game_state = COUNTDOWN;
				app->coins--;
			}
		}

		else { update_counter++; }

		break;

	case READY:
		if (update_counter < 30){ app->renderModule->Print(app->texturesModule->ready, &ready_source_rect, &ready_rect); }
		else if (update_counter % 30 > 15){ app->renderModule->Print(app->texturesModule->ready, &ready_source_rect, &ready_rect); }

		if (update_counter > 120){ game_state = PLAYING; update_counter = 0; }
		else { update_counter++; }

		break;

	case COUNTDOWN:
		if (update_counter++ % 60 == 0){ countdown_num--; }
		if (countdown_num == -1){ game_state = GAME_OVER; update_counter = 0; }

		if (app->coins > 0)
		{
			game_state = PLAYING;
			update_counter = 0;
			app->playerModule->player1->lives = 3;
			reset_stage();
		}

		app->fontManagerModule->Write_On_Screen(countdown_num, 88 * app->windowModule->scale, 226 * app->windowModule->scale, 8 * app->windowModule->scale, RED);
		break;

	case GAME_OVER:
		app->renderModule->Print(app->texturesModule->ready, &game_over_source_rect, &game_over_rect);

		if (update_counter > 240){ return CHANGE_TO_TITLE; }
		else { update_counter++; }

		break;

	case PAUSED:
		app->renderModule->Print(app->texturesModule->ready, &game_over_source_rect, &game_over_rect);

		// darken screen
		app->renderModule->Fade_Screen();

		if (app->inputModule->key[SDL_SCANCODE_P] == 1)
		{
			if (!pause_pressed)
			{
				if (!Resume_Scene()){ return UPDATE_ERROR; }
			}
		}
		else{ pause_pressed = false; }

		break;
	case TIME_OUT:
		app->renderModule->Print(app->texturesModule->ready, &time_over_source_rect, &time_over_rect);

		if (update_counter > 240)
		{
			if (app->playerModule->player1->lives > 0)
			{
				reset_stage();
			}
			else 
			{ 
				if (app->coins > 0)
				{
					app->coins--;
					app->playerModule->player1->lives = 3;
					reset_stage();
				}
				else
				{ 
					app->audioModule->StopMusic(); 
					game_state = COUNTDOWN;
					update_counter = 0;
				}
			}
		
		}
		else { update_counter++; }

		break;
	}

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	delete time_count;

	return true;
}

void ModuleScene::Pause_Scene()
{
	app->audioModule->PauseMusic();

	game_state = PAUSED;
	pause_pressed = true;
}

bool ModuleScene::Resume_Scene()
{
	app->audioModule->ResumeMusic();

	game_state = PLAYING;
	pause_pressed = true;

	return true;
}


void ModuleScene::Print_All_Objects()
{
	// PRINT TEXT & SCORES & LIVES
	app->fontManagerModule->Write_On_Screen("Player-1",                        17 * app->windowModule->scale, 208 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("Player-2",                       270 * app->windowModule->scale, 208 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen_backwards(app->playerModule->player1->score, 111 * app->windowModule->scale, 216 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(app->city_names[app->city - 1], (192 - ((strlen(app->city_names[app->city - 1])/2)*8)) * app->windowModule->scale, 208 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("-",                              167 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(app->stage,                       176 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("HI:",                            160 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(10000,                            185 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	//app->fontManagerModule->Write_On_Screen(app->coins,                       360 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	//print player 1 lives sprites
	int vidas_tmp = app->playerModule->player1->lives;
	if (vidas_tmp > 5){ vidas_tmp = 5; }
	for (int i = 0; i < vidas_tmp; i++){ app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[13], &livesrect_player1[i]); }
	if (app->playerModule->player1->lives>5){ app->fontManagerModule->Write_On_Screen(app->playerModule->player1->lives, 88 * app->windowModule->scale, 226 * app->windowModule->scale, 10 * app->windowModule->scale, WHITE); }
	//print name of the city
	if (app->city > 9) { app->fontManagerModule->Write_On_Screen(app->city, 152 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
	else { app->fontManagerModule->Write_On_Screen(app->city, 160 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
	if (app->stage > 9) { app->fontManagerModule->Write_On_Screen("stage", 195 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
	else { app->fontManagerModule->Write_On_Screen("stage", 187 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
	//print player 2 score and lives sprites
	if (app->player_2_enabled){
		
		for (unsigned int i = 0; i < app->playerModule->player2->lives; i++){ app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[14], &livesrect_player2[i]); }
		if (app->playerModule->player2->lives>5){ app->fontManagerModule->Write_On_Screen(app->playerModule->player2->lives, 352 * app->windowModule->scale, 226 * app->windowModule->scale, 10 * app->windowModule->scale, WHITE); }
		app->fontManagerModule->Write_On_Screen_backwards(app->playerModule->player2->score, 360 * app->windowModule->scale, 214 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
		
	}
	else{
		if (time_count->current_time % 2 == 0) { app->fontManagerModule->Write_On_Screen("PUSH BUTTON", 270 * app->windowModule->scale, 224 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
	}
	//CURRENT POWER UP
	//Player1
	switch (app->playerModule->player1->current_weapon)
	{
	
		case WEAPON_HARPOON:break;
		case WEAPON_DOUBLE_HARPOON: app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[2], &power_up_rect);
			break;
		case WEAPON_GRAPPLE:app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[1], &power_up_rect);
			break;
		case WEAPON_SHOTGUN:app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[0], &power_up_rect);
			break;
	}

	//Player 2
	switch (app->playerModule->player2->current_weapon)
	{

	case WEAPON_HARPOON:break;
	case WEAPON_DOUBLE_HARPOON: app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[2], &power_up_rect2);
		break;
	case WEAPON_GRAPPLE:app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[1], &power_up_rect2);
		break;
	case WEAPON_SHOTGUN:app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[0], &power_up_rect2);
		break;
	}

	// PRINT BACKGROUND
	app->renderModule->Print(app->texturesModule->background_sprite, &background_source_rect, &background_rect);

	// PRINT TIMER
	time_count->Print_Timer();

	// PRINT STAIRS
	for (unsigned int i = 0; i < app->entityManagerModule->stairs.Count(); i++) { (*app->entityManagerModule->stairs.at(i))->Print(); }

	// PRINT BRICKS
	for (unsigned int i = 0; i < app->entityManagerModule->bricks.Count(); i++) { (*app->entityManagerModule->bricks.at(i))->Print(); }

	// PRINT HARPOONS
	if (app->playerModule->player1->harpoon1->alive) { app->playerModule->player1->harpoon1->Print(); }
	if (app->playerModule->player1->harpoon2->alive) { app->playerModule->player1->harpoon2->Print(); }

	if (app->player_2_enabled)
	{
		if (app->playerModule->player2->harpoon1->alive) { app->playerModule->player2->harpoon1->Print(); }
		if (app->playerModule->player2->harpoon2->alive) { app->playerModule->player2->harpoon2->Print(); }
	}

	// PRINT BULLETS
	app->playerModule->player1->PrintBullets();
	if (app->player_2_enabled) { app->playerModule->player2->PrintBullets(); }

	// PRINT PLAYERS
	app->playerModule->player1->Print();
	if (app->player_2_enabled){ app->playerModule->player2->Print(); }
	
	// PRINT BALLS
	for (unsigned int i = 0; i < app->entityManagerModule->balloons.Count(); i++) { (*app->entityManagerModule->balloons.at(i))->Print(); }

	// PRINT POWER UPS
	for (unsigned int i = 0; i < app->entityManagerModule->powerups.Count(); i++) { (*app->entityManagerModule->powerups.at(i))->Print(); }

	// PRINT PARTICLES
	for (unsigned int i = 0; i < app->entityManagerModule->particles.Count(); i++) { (*app->entityManagerModule->particles.at(i))->Print(); }
}


void ModuleScene::reset_stage()
{
	unsigned int i;

	game_state = READY;

	half_time = false;
	countdown_num = 10;
	update_counter = 0;

	app->entityManagerModule->particles.clear();

	// SOUNDTRACK
	if (app->city < 10){ app->audioModule->PlayMusic(app->city - 1); }
	else if (app->city < 14){ app->audioModule->PlayMusic(app->city - 8); }
	else
	{
		switch (app->city)
		{
		case 14: app->audioModule->PlayMusic(2); break;
		case 15: app->audioModule->PlayMusic(8); break;
		case 16: app->audioModule->PlayMusic(6); break;
		case 17: app->audioModule->PlayMusic(9); break;
		}
	}

	// TIME COUNT
	time_count->Reset(stage_arrangement.time_limit);

	// PLAYER POS
	app->playerModule->player1->Reset(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]);
	app->playerModule->player2->Reset(stage_arrangement.player_pos[2], stage_arrangement.player_pos[3]);

	// POWER UPS_________________________________________________________________________________________________________________________

	app->entityManagerModule->powerups.ClearAll();


	// BRICKS____________________________________________________________________________________________________________________________

	app->entityManagerModule->bricks.ClearAll();
	
	for (i = 0; i < stage_arrangement.bricks.Count(); i++)
	{
		app->entityManagerModule->bricks.push_back(new Brick(
			app, i,
			stage_arrangement.bricks.at(i)->x,
			stage_arrangement.bricks.at(i)->y,
			stage_arrangement.bricks.at(i)->type, 
			stage_arrangement.bricks.at(i)->aux1));
	}


	// STAIRS____________________________________________________________________________________________________________________________

	app->entityManagerModule->stairs.ClearAll();
	for (i = 0; i < stage_arrangement.stairs.Count(); i++)
	{
		app->entityManagerModule->stairs.push_back(new Stair(
			app,
			stage_arrangement.stairs.at(i)->x,
			stage_arrangement.stairs.at(i)->y,
			stage_arrangement.stairs.at(i)->type));
	}


	// BALLOONS____________________________________________________________________________________________________________________________

	app->entityManagerModule->balloons.ClearAll();
	for (i = 0; i < stage_arrangement.balloons.Count(); i++)
	{
		app->entityManagerModule->balloons.push_back(new Balloon(
			app, i,
			(*stage_arrangement.balloons.at(i)).x,
			(*stage_arrangement.balloons.at(i)).y,
			(*stage_arrangement.balloons.at(i)).type,
			(*stage_arrangement.balloons.at(i)).aux1));
	}

	
	// ENEMIES____________________________________________________________________________________________________________________________
	/*
	app->entityManagerModule->enemies.ClearAll();
	for (i = 0; i < stage_arrangement.enemies.Count(); i++)
	{
		app->entityManagerModule->enemies->push_back(new Enemy(
			app, i,
			(*stage_arrangement.enemies.at(i)).x,
			(*stage_arrangement.enemies.at(i)).y,
			(*stage_arrangement.enemies.at(i)).type
			(*stage_arrangement.enemies.at(i)).aux1,
			(*stage_arrangement.enemies.at(i)).aux2,
			(*stage_arrangement.enemies.at(i)).aux3));
	}*/
}



bool ModuleScene::load_stage()
{
	if (fopen_s(&level_file, "txt files/LevelArrangment.txt", "r") != 0){ return false; }

	char line[400];
	for (int i = 0; i < app->stage; i++)
	{
		fgets(line, 300, level_file);
		if (line == NULL){ return false; }
	}

	parser(line);
	fclose(level_file);

	background_source_rect = { ((app->stage - 1) % 3) * 384, ((app->city - 1)) * 208, 384, 208 };

	reset_stage();

	return true;

}


void ModuleScene::parser(char *line)
{
	char *main_token = NULL;
	char *tmp_string = NULL;
	int max;
	Hexa_Struct tmp_struct;
	tmp_struct.Reset();

	// time limit
	stage_arrangement.time_limit = atoi(strtok_s(line, "%", &main_token));
	
	// player's initial position
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.player_pos[0] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[1] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[2] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[3] = atoi(tmp_string);
	
	// bricks
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.bricks.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.aux1 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.bricks.push_back(tmp_struct);
		}
	}

	// stairs
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.stairs.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.stairs.push_back(tmp_struct);
			}
	}

	// balloons
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.balloons.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.aux1 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.balloons.push_back(tmp_struct);
		}
	}

	// enemies
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.enemies.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.aux1 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.enemies.push_back(tmp_struct);
		}
	}
}
