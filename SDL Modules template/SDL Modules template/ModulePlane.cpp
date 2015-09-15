#include "ModulePlane.h"

ModulePlane::ModulePlane(Application* app) : Module(app)
{
	// background
	background_source_rect = { 0, 0, SCREEN_WIDTH, 208 };

	// city rects
	city_rect[0] =  { 344 * app->windowModule->scale,  72 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[1] =  { 304 * app->windowModule->scale,  72 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[2] =  { 288 * app->windowModule->scale, 104 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[3] =  { 304 * app->windowModule->scale, 104 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[4] =  { 332 * app->windowModule->scale, 164 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[5] =  { 268 * app->windowModule->scale, 100 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[6] =  { 208 * app->windowModule->scale,  40 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[7] =  { 176 * app->windowModule->scale,  48 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[8] =  { 152 * app->windowModule->scale,  40 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[9] =  { 132 * app->windowModule->scale,  68 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[10] = { 180 * app->windowModule->scale,  68 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[11] = { 204 * app->windowModule->scale,  84 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[12] = { 204 * app->windowModule->scale, 124 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[13] = {  80 * app->windowModule->scale,  64 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[14] = {  44 * app->windowModule->scale, 100 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[15] = {  88 * app->windowModule->scale, 192 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[16] = {  12 * app->windowModule->scale, 156 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	
	city_source_rect[0] = { 216, 208, 8, 8 };
	city_source_rect[1] = { 216, 216, 8, 8 };

	for (unsigned int i = 0; i < 6; i++)
	{
		plane_source_rect[i] = { 224 + (i * 16), 208, 16, 16 };
	}

}

bool ModulePlane::Init()
{
	// background
	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, 208 * app->windowModule->scale };

	travel_index = (app->stage / 3) - 1;
	
	plane_rect = app->chooseCityModule->selection_rect[travel_index];

	switch (travel_index)
	{
	case 0:  plance_source_index = 4; break;
	case 1:  plance_source_index = 0; break;
	case 2:  plance_source_index = 3; break;
	case 3:  plance_source_index = 1; break;
	case 4:  plance_source_index = 2; break;
	case 5:  plance_source_index = 2; break;
	case 6:  plance_source_index = 0; break;
	case 7:  plance_source_index = 2; break;
	case 8:  plance_source_index = 0; break;
	case 9:  plance_source_index = 3; break;
	case 10: plance_source_index = 1; break;
	case 11: plance_source_index = 5; break;
	case 12: plance_source_index = 2; break;
	case 13: plance_source_index = 0; break;
	case 14: plance_source_index = 1; break;
	case 15: plance_source_index = 2; break;
	}

	ticks = 0;
	return true;
}

update_status ModulePlane::Update()
{
	if (ticks > 180){ return CHANGE_TO_PLAY; }

	if (ticks == 130){ app->audioModule->StopMusic(); }

	//if (ticks < 150){ UpdatePlane(); }

	// print map
	app->renderModule->Print(app->texturesModule->map_sprite, &background_source_rect, &background_rect);

	// print visited cities
	for (unsigned int i = 0; i <= travel_index; i++)
	{
		app->renderModule->Print(app->texturesModule->map_sprite, &city_source_rect[1], &city_rect[i]);
	}

	// intermitent print destination city
	if (ticks % 40 < 20)
	{
		app->renderModule->Print(app->texturesModule->map_sprite, &city_source_rect[0], &city_rect[travel_index + 1]);
	}

	// print plane
	app->renderModule->Print(app->texturesModule->map_sprite, &plane_source_rect[plance_source_index], &plane_rect);

	ticks++;

	return UPDATE_CONTINUE;
}

void ModulePlane::UpdatePlane()
{
	switch (travel_index)
	{
	case 0:
		plance_source_index = 4;
		break;
	case 1:
		plance_source_index = 0;
		break;
	case 2:
		plance_source_index = 3;
		break;
	case 3:
		plance_source_index = 1;
		break;
	case 4:
		plance_source_index = 2;
		break;
	case 5:
		plance_source_index = 2;
		break;
	case 6:
		plance_source_index = 0;
		break;
	case 7:
		plance_source_index = 2;
		break;
	case 8:
		plance_source_index = 0;
		break;
	case 9:
		plance_source_index = 3;
		break;
	case 10:
		plance_source_index = 1;
		break;
	case 11:
		plance_source_index = 5;
		break;
	case 12:
		plance_source_index = 2;
		break;
	case 13:
		plance_source_index = 0;
		break;
	case 14:
		plance_source_index = 1;
		break;
	case 15:
		plance_source_index = 2;
		break;
	}
}



