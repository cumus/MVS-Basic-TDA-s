
#include "ModuleTextures.h"

ModuleTextures::ModuleTextures(Application* app) : Module(app)
{
	background_sprite = NULL;
	balls_sprite = NULL;
	bricks_sprite = NULL;
	enemies_sprite = NULL;
	harpoons_sprite = NULL;
	instructions_sprite = NULL;
	map_countdown_sprite = NULL;
	map_sprite = NULL;
	particles_sprite = NULL;
	players_sprite = NULL;
	powerUp_sprite = NULL;
	ready = NULL;
	scores_sprite = NULL;
	timer_sprite = NULL;
	title_sprite = NULL;

}

bool ModuleTextures::Init()
{
	background_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Backgrounds.png");
	if (background_sprite == NULL){ return false; }

	balls_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Balls.png");
	if (balls_sprite == NULL){ return false; }

	bricks_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Bricks.png");
	if (bricks_sprite == NULL){ return false; }

	enemies_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Enemies.png");
	if (enemies_sprite == NULL){ return false; }

	harpoons_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Harpoons.png");
	if (harpoons_sprite == NULL){ return false; }

	map_countdown_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Map Countdown.png");
	if (map_countdown_sprite == NULL){ return false; }

	map_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Map.png");
	if (map_sprite == NULL){ return false; }

	particles_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Particles.png");
	if (particles_sprite == NULL){ return false; }

	players_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Players.png");
	if (players_sprite == NULL){ return false; }

	powerUp_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Power_ups.png");
	if (powerUp_sprite == NULL){ return false; }

	ready = IMG_LoadTexture(app->renderModule->renderer, "images/Ready.png");
	if (ready == NULL){ return false; }

	scores_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Score.png");
	if (scores_sprite == NULL){ return false; }

	timer_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Timer.png");
	if (timer_sprite == NULL){ return false; }

	title_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Title.png");
	if (title_sprite == NULL){ return false; }

	level_complete = IMG_LoadTexture(app->renderModule->renderer, "images/SpriteEndStage/AllFinalStagesOK.png");
	if (level_complete == NULL){ return false; }
	

	return true;
}

bool ModuleTextures::CleanUp()
{

	SDL_DestroyTexture(background_sprite);
	SDL_DestroyTexture(balls_sprite);
	SDL_DestroyTexture(bricks_sprite);
	SDL_DestroyTexture(enemies_sprite);
	SDL_DestroyTexture(harpoons_sprite);
	SDL_DestroyTexture(instructions_sprite);
	SDL_DestroyTexture(map_countdown_sprite);
	SDL_DestroyTexture(map_sprite);
	SDL_DestroyTexture(particles_sprite);
	SDL_DestroyTexture(players_sprite);
	SDL_DestroyTexture(powerUp_sprite);
	SDL_DestroyTexture(ready);
	SDL_DestroyTexture(scores_sprite);
	SDL_DestroyTexture(timer_sprite);
	SDL_DestroyTexture(title_sprite);
	SDL_DestroyTexture(level_complete);

	return true;
}
