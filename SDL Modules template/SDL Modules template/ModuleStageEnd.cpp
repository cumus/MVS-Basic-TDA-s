
#include "ModuleStageEnd.h"

ModuleStageEnd::ModuleStageEnd(Application* app) : Module(app)
{
	for (unsigned int i = 0; i < 1; i++){ image_source_rect[0][i] = { i * 141,   0, 141, 94 }; }
	for (unsigned int i = 0; i < 1; i++){ image_source_rect[1][i] = { i * 141, 141, 141, 94 }; }
	for (unsigned int i = 0; i < 1; i++){ image_source_rect[2][i] = { i * 141, 282, 141, 94 }; }
	for (unsigned int i = 0; i < 1; i++){ image_source_rect[3][i] = { i * 141, 463, 141, 94 }; }

	max_index[0] = 0;
	max_index[1] = 0;
	max_index[2] = 0;
	max_index[3] = 0;

	ticks = 0;
	source_index_1 = source_index_2 = 0;
	push_button_shown = true;
}


bool ModuleStageEnd::Init()
{
	app->audioModule->PlayMusic(17);

	image_rect = { 118 * app->windowModule->scale, 32 * app->windowModule->scale, 141 * app->windowModule->scale, 94 * app->windowModule->scale };

	ticks = 0;
	
	// handle source_index_1 algorithm
	source_index_1 = 0;

	source_index_2 = 0;

	push_button_shown = true;
	app->playerModule->player1->score += (app->sceneModule->time_count->current_time)*100;





	return true;
}
void ModuleStageEnd::NextExtend(){


	if (app->playerModule->player1->score >= next_extend){

		app->playerModule->player1->lives++;
		if ((next_extend_counter % 2) == 0){
			next_extend = next_extend * 2;
			next_extend_counter++;
		}
		else{
			next_extend = (next_extend / 2) * 10;
			next_extend_counter++;
		}
	}



}
update_status ModuleStageEnd::Update()
{
	app->audioModule->StopMusic();

	// -------------------------------------------------------------------------------------------------------------------------------------------

	if (ticks > 180)
	{
		return CHANGE_TO_PLAY;
		/*
		if (app->stage > 1 && (app->stage - 1) % 3 == 0) { return CHANGE_TO_PLAY; } // planne module if travelng to new city
		return CHANGE_TO_MAP_PLANE;*/
	}

	// Update push_button_shown state
	if (ticks % 30 == 0)
	{
		if (push_button_shown) { push_button_shown = false; }
		else{ push_button_shown = true; }
	}

	// Update source_index_2
	if (ticks % 10 == 0)
	{
		if (source_index_2 < max_index[source_index_1]){ source_index_2++; }
		else{ source_index_2 = 0; }
	}



	// Print All

	app->renderModule->Print(app->texturesModule->level_complete, &image_source_rect[source_index_1][source_index_2], &image_rect); // print map

	if ((app->stage - 1) / 10 != 0)
	{
		// print: (app->stage - 1) / 10
	}
	// print: (app->stage - 1) % 10
	app->fontManagerModule->Write_On_Screen("stage", 176 * app->windowModule->scale, 144 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen_backwards(app->stage, 172 * app->windowModule->scale, 144 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("TIME BONUS :", 104* app->windowModule->scale, 168 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen_backwards((app->sceneModule->time_count->current_time) * 100, 300 * app->windowModule->scale, 168 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("PTS", 300 * app->windowModule->scale, 168 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	if (ticks > 90)
	{
		app->fontManagerModule->Write_On_Screen("NEXT EXTEND :", 104 * app->windowModule->scale, 184 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
		app->fontManagerModule->Write_On_Screen_backwards(next_extend, 300 * app->windowModule->scale, 184 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
		app->fontManagerModule->Write_On_Screen("PTS", 300 * app->windowModule->scale, 184 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	}

	if (push_button_shown)
	{
		if (ticks % 60 < 30) { app->fontManagerModule->Write_On_Screen("PUSH BUTTON", 270 * app->windowModule->scale, 224 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE); }
	}

	ticks++;

	return UPDATE_CONTINUE;
}

bool ModuleStageEnd::CleanUp(){ return true; }