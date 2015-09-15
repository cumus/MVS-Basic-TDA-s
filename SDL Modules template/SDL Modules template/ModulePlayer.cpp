#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(Application* app) : Module(app), player1(NULL), player2(NULL) {}

bool ModulePlayer::Init()
{
	if (player1 == NULL) { player1 = new Player(app, true); }
	if (player2 == NULL) { player2 = new Player(app, false); }
	player_speed = app->windowModule->scale;
	return true;
}

update_status ModulePlayer::Update()
{
	//----------------  PLAYING  ----------------
	if (app->sceneModule->game_state == PLAYING)
	{
		// PLAYER 2
		if (app->player_2_enabled)
		{
			player2->Update();

			// Movement
			if ( app->inputModule->key[SDL_SCANCODE_LEFT] == 1){ player2->LeftTrigger(); }
			if (app->inputModule->key[SDL_SCANCODE_RIGHT] == 1){ player2->RightTrigger(); }
			if (   app->inputModule->key[SDL_SCANCODE_UP] == 1){ player2->UpTrigger(); }
			if ( app->inputModule->key[SDL_SCANCODE_DOWN] == 1){ player2->DownTrigger(); }

			// Shoot
			if (app->inputModule->key[SDL_SCANCODE_RCTRL] == 1){ player2->Shoot(); }
			else { player2->shoot_key_pressed = false; }

			// Still
			
			if (((app->inputModule->key[SDL_SCANCODE_LEFT] == 0 && app->inputModule->key[SDL_SCANCODE_RIGHT] == 0)
				|| (app->inputModule->key[SDL_SCANCODE_UP] == 0 && app->inputModule->key[SDL_SCANCODE_DOWN] == 0))
				&& (player2->state != HIT))
			{
				player2->Still();
			}
		}

		// PLAYER 1
		player1->Update();

		// Movement
		if (app->inputModule->key[SDL_SCANCODE_A] == 1){ player1->LeftTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_D] == 1){ player1->RightTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_W] == 1){ player1->UpTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_S] == 1){ player1->DownTrigger(); }

		// Still
		if (((app->inputModule->key[SDL_SCANCODE_A] == 0 && app->inputModule->key[SDL_SCANCODE_D] == 0)
			|| (app->inputModule->key[SDL_SCANCODE_W] == 0 && app->inputModule->key[SDL_SCANCODE_S] == 0))
			&& (player1->state != HIT))
		{
			player1->Still();
		}

		// Shoot
		if (app->inputModule->key[SDL_SCANCODE_SPACE] == 1){ player1->Shoot(); }
		else { player1->shoot_key_pressed = false; }
	}

	//----------------  PLAYER_KILLED  ----------------
	else if (app->sceneModule->game_state == PLAYER_KILLED)
	{
		// PLAYER 2
		if (app->player_2_enabled) { if (!player2->alive){ player2->Update(); } }

		// PLAYER 1
		if (!player1->alive){ player1->Update(); }
	}

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	if (player1 != NULL) { delete player1; }
	if (player2 != NULL) { delete player2; }

	return true;
}

void ModulePlayer::SpawnPlayer2()
{
	//----------------
	//----------------
	//----------------
	//----------------
	//----------------
	//----------------
}

