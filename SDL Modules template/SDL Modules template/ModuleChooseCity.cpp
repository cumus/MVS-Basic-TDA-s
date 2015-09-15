#include "ModuleChooseCity.h"

ModuleChooseCity::ModuleChooseCity(Application* app) : Module(app),
selection_index(0),
selection_source_index(0),
update_counter(0),
current_number(9),
ticks(0),
a_pressed(false),
d_pressed(false)
{
	// background
	background_source_rect = { 0, 0, SCREEN_WIDTH, 208 };

	// number countdown
	for (unsigned int i = 0; i < 10; i++) { countdown_source_rect[i] = { (i * 24), 0, 24, 31 }; }

	// selection squares
	selection_source_rect[0] = { 184, 208, 16, 16 };
	selection_source_rect[1] = { 200, 208, 16, 16 };

	// forward return controls
	controls_source_rect = { 0, 208, 184, 45 };
}

bool ModuleChooseCity::Init()
{
	app->audioModule->PlayMusic(10);

	// background
	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, 208 * app->windowModule->scale };

	// number countdown
	countdown_rect = { 255 * app->windowModule->scale, 20 * app->windowModule->scale, 24 * app->windowModule->scale, 31 * app->windowModule->scale };

	// selection squares
	selection_rect[0] =  { 340 * app->windowModule->scale,  68 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[1] =  { 300 * app->windowModule->scale,  68 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[2] =  { 284 * app->windowModule->scale, 100 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[3] =  { 300 * app->windowModule->scale, 100 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[4] =  { 328 * app->windowModule->scale, 160 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[5] =  { 264 * app->windowModule->scale,  96 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[6] =  { 204 * app->windowModule->scale,  36 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[7] =  { 172 * app->windowModule->scale,  44 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[8] =  { 148 * app->windowModule->scale,  36 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[9] =  { 128 * app->windowModule->scale,  64 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[10] = { 176 * app->windowModule->scale,  64 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[11] = { 200 * app->windowModule->scale,  80 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[12] = { 200 * app->windowModule->scale, 120 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[13] = {  76 * app->windowModule->scale,  60 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[14] = {  40 * app->windowModule->scale,  96 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[15] = {  84 * app->windowModule->scale, 188 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[16] = {   8 * app->windowModule->scale, 152 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };

	// forward return controls
	controls_rect = { 100 * app->windowModule->scale, 163 * app->windowModule->scale, 184 * app->windowModule->scale, 45 * app->windowModule->scale };

	selection_index = 0;
	selection_source_index = 0;
	update_counter = 0;
	current_number = 10;
	ticks = 1;
	a_pressed = d_pressed = false;

	return true;
}




update_status ModuleChooseCity::Update()
{
	// handle countdown numbers
	if (ticks % 60 == 0)
	{
		if (current_number > 0){ current_number--; }
		else{ return CHANGE_TO_PLAY;}
	}

	if (ticks < 600)
	{
		// SPACE TRIGGER
		if (app->inputModule->key[SDL_SCANCODE_SPACE] == 1)
		{
			app->city = selection_index + 1;
			app->stage = (selection_index * 3) + 1;
			return CHANGE_TO_PLAY;
		}

		// LEFT TRIGGER
		if (app->inputModule->key[SDL_SCANCODE_A] == 1)
		{
			if (!a_pressed)
			{
				if (selection_index < 16)
				{
					selection_index++;
				}

				a_pressed = true;
			}
		}
		else { a_pressed = false; }

		// RIGHT TRIGGER
		if (app->inputModule->key[SDL_SCANCODE_D] == 1)
		{
			if (!d_pressed)
			{
				if (selection_index != 0)
				{
					selection_index--;
				}

				d_pressed = true;
			}
		}
		else { d_pressed = false; }
	}
	else
	{
		if (ticks % 14 > 7) selection_source_index = 1;
		else selection_source_index = 0;
	}

	app->fontManagerModule->Write_On_Screen("choose a city to start.",          9 * app->windowModule->scale, 214 * app->windowModule->scale, 7 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("use arrows to choose.",            9 * app->windowModule->scale, 222 * app->windowModule->scale, 7 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("press button to finalize choice.", 9 * app->windowModule->scale, 230 * app->windowModule->scale, 7 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("stage name",                     295 * app->windowModule->scale, 207 * app->windowModule->scale, 7 * app->windowModule->scale, YELLOW);
	app->fontManagerModule->Write_On_Screen("stage",                          280 * app->windowModule->scale, 230 * app->windowModule->scale, 7 * app->windowModule->scale, YELLOW);
	app->fontManagerModule->Write_On_Screen(app->stage,                       344 * app->windowModule->scale, 230 * app->windowModule->scale, 7 * app->windowModule->scale, YELLOW);
	app->fontManagerModule->Write_On_Screen("~",                              352 * app->windowModule->scale, 230 * app->windowModule->scale, 7 * app->windowModule->scale, YELLOW);
	app->fontManagerModule->Write_On_Screen(app->stage,                       358 * app->windowModule->scale, 230 * app->windowModule->scale, 7 * app->windowModule->scale, YELLOW);


	app->renderModule->Print(app->texturesModule->map_sprite, &background_source_rect, &background_rect); // print map
	app->renderModule->Print(app->texturesModule->map_sprite, &controls_source_rect, &controls_rect); // print controls
	app->renderModule->Print(app->texturesModule->map_sprite, &selection_source_rect[selection_source_index], &selection_rect[selection_index]); // print selection square
	if (current_number > 1) app->renderModule->Print(app->texturesModule->map_countdown_sprite, &countdown_source_rect[current_number - 1], &countdown_rect); // print countdown numbers
	
	ticks++;

	return UPDATE_CONTINUE;
}

