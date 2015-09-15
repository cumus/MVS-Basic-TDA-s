# include "Particles.h"

/*
0 - 11 balloon
12 enemy hit
13 shoot
14 - 29 brick
*/


Particles::Particles(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y) :
		app(app),
		position_in_list(position_in_list),
		update_counter(0)
{
	if (type < 12){ app->audioModule->PlayFx(BALLOON_POP); }

	quantity = 3;

	switch (type)
	{
	case 0:
		source_index = 0;
		rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 1:
		source_index = 4;
		rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 2:
		source_index = 8;
		rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 3:
		source_index = 12;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 29 * app->windowModule->scale };
		break;
	case 4:
		source_index = 16;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 29 * app->windowModule->scale };
		break;
	case 5:
		source_index = 20;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 29 * app->windowModule->scale };
		break;
	case 6:
		source_index = 24;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
	case 7:
		source_index = 28;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
	case 8:
		source_index = 32;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
	case 9:
		source_index = 36;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 10:
		source_index = 40;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 11:
		source_index = 44;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 12:
		source_index = 48;
		rect = { x, y - app->windowModule->scale, 28 * app->windowModule->scale, 26 * app->windowModule->scale };
		quantity = 4;
		break;
	case 13:
		source_index = 53;
		rect = { x, y - app->windowModule->scale, 15 * app->windowModule->scale, 15 * app->windowModule->scale };
		break;
		// horizontal bricks
		//yellow1
	case 14:
		source_index = 57;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//pink1
	case 15:
		source_index = 61;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//blue1
	case 16:
		source_index = 61;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//yellow2
	case 17:
		source_index = 69;
		rect = { x, y - app->windowModule->scale, 24 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//pink2
	case 18:
		source_index = 73;
		rect = { x, y - app->windowModule->scale, 24 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//blue2
	case 19:
		source_index = 77;
		rect = { x, y - app->windowModule->scale, 24 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//yellow3
	case 20:
		source_index = 81;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//pink3
	case 21:
		source_index = 85;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//blue3
	case 22:
		source_index = 89;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//yelllow4
	case 23:
		source_index = 93;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//pink4
	case 24:
		source_index = 97;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		//blue4
	case 25:
		source_index = 101;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
		break;
		// vertical bricks
		//Yellow
	case 26:
		source_index = 105;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 32 * app->windowModule->scale };
		break;
		//Blue1
	case 27:
		source_index = 109;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 32 * app->windowModule->scale };
		break;
		//Blue2
	case 28:
		source_index = 113;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
		//Blue3
	case 29:
		source_index = 117;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 24 * app->windowModule->scale };
		break;
	case 30:
		source_index = 121;
		rect = { x, y - app->windowModule->scale, 14 * app->windowModule->scale, 5 * app->windowModule->scale };
		quantity = 1;
		break;
	}
}

void Particles::Update()
{
	if (update_counter >2)
	{
		if (quantity > 0)
		{
			source_index++;
			update_counter = 0;
			quantity--;
		}
		else
		{
			for (unsigned int i = position_in_list + 1; i < app->entityManagerModule->particles.Count(); i++)
			{
				(*app->entityManagerModule->particles.at(i))->position_in_list--;
			}
			app->entityManagerModule->particles.Delete_Element_At(position_in_list);
		}
	}
	else{ update_counter++; }
}

void Particles::Print()
{
	if (source_index < 57)
	{
		app->renderModule->Print(app->texturesModule->particles_sprite, &app->entityManagerModule->particles_source_rect[source_index], &rect);
	}
	else
	{
		app->renderModule->Print(app->texturesModule->bricks_sprite, &app->entityManagerModule->particles_source_rect[source_index], &rect);
	}
}
