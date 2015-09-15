#pragma once

#include "Application.h"

Application::Application() : coins(0), stage(1), city(1), player_2_enabled(false) {}

bool Application::Init()
{
	windowModule = new ModuleWindow(this);
	renderModule = new ModuleRender(this);
	inputModule = new ModuleInput(this);
	texturesModule = new ModuleTextures(this);
	audioModule = new ModuleAudio(this);
	fontManagerModule = new ModuleFontManager(this);

	modules_Queue.push(windowModule);
	modules_Queue.push(renderModule);
	modules_Queue.push(inputModule);
	modules_Queue.push(texturesModule);
	modules_Queue.push(audioModule);
	modules_Queue.push(fontManagerModule);

	playerModule = new ModulePlayer(this);
	entityManagerModule = new ModuleEntityManager(this);
	sceneModule = new ModuleScene(this);
	titleModule = new ModuleTitle(this);
	chooseCityModule = new ModuleChooseCity(this);
	planeModule = new ModulePlane(this);
	stageEndModule = new ModuleStageEnd(this);
	creditsModule = new ModuleCredits(this);
	highscoreModule = new ModuleHighscore(this);

	playerModule_Node = new DoubleNode<Module*>(playerModule);
	entityManagerModule_Node = new DoubleNode<Module*>(entityManagerModule);
	sceneModule_Node = new DoubleNode<Module*>(sceneModule);
	titleModule_Node = new DoubleNode<Module*>(titleModule);
	chooseCityModule_Node = new DoubleNode<Module*>(chooseCityModule);
	planeModule_Node = new DoubleNode<Module*>(planeModule);
	stageEndModule_Node = new DoubleNode<Module*>(stageEndModule);
	creditsModule_Node = new DoubleNode<Module*>(creditsModule);
	highscoreModule_Node = new DoubleNode<Module*>(highscoreModule);

	DoubleNode<Module*>* item = modules_Queue.getStart();
	while (item != NULL)
	{
		if (!item->data->Init()){ return false; }
		item = item->next;
	}

	coins = 0;
	stage = 1;

	city_names[0]  = "MT. FUJI";
	city_names[1]  = "MT. KEIRIN";
	city_names[2]  = "EMERALD TEMPLE"; // 2 lines
	city_names[3]  = "ANGKOR WAT";
	city_names[4]  = "AUSTRALIA";
	city_names[5]  = "TAJ MAHAL";
	city_names[6]  = "LENINGRAD";
	city_names[7]  = "PARIS";
	city_names[8]  = "LONDON";
	city_names[9]  = "BARCELONA";
	city_names[10] = "ATHENS";
	city_names[11] = "EGYPT";
	city_names[12] = "KENYA";
	city_names[13] = "NEW YORK";
	city_names[14] = "MAYA";
	city_names[15] = "ANTARTICA";
	city_names[16] = "EASTER ISLAND"; // 2 lines

	return true;
}

Application::~Application()
{
	modules_Queue.clear();
}

update_status Application::Update()
{
	update_status returnValue;

	DoubleNode<Module*>* item = modules_Queue.getStart(); // ------------PreUpdate------------
	while (item != NULL)
	{
		returnValue = item->data->PreUpdate();
		if (returnValue != UPDATE_CONTINUE){ return returnValue; }
		item = item->next;
	}

	item = modules_Queue.getStart(); // ------------Update------------
	while (item != NULL)
	{
		returnValue = item->data->Update();
		if (returnValue != UPDATE_CONTINUE){ return returnValue; }
		item = item->next;
	}

	item = modules_Queue.getStart(); // ------------PostUpdate------------
	while (item != NULL)
	{
		returnValue = item->data->PostUpdate();
		if (returnValue != UPDATE_CONTINUE){ return returnValue; }
		item = item->next;
	}

	return returnValue;
}

bool Application::CleanUp()
{
	modules_Queue.ReduceTo(6);

	if (!playerModule->CleanUp())        { return false; } delete playerModule_Node; // deleting the containing node deletes its data
	if (!entityManagerModule->CleanUp()) { return false; } delete entityManagerModule_Node;
	if (!sceneModule->CleanUp())         { return false; } delete sceneModule_Node;
	if (!titleModule->CleanUp())         { return false; } delete titleModule_Node;
	if (!chooseCityModule->CleanUp())    { return false; } delete chooseCityModule_Node;
	if (!planeModule->CleanUp())         { return false; } delete planeModule_Node;
	if (!stageEndModule->CleanUp())      { return false; } delete stageEndModule_Node;
	if (!creditsModule->CleanUp())       { return false; } delete creditsModule_Node;
	if (!highscoreModule->CleanUp())     { return false; } delete highscoreModule_Node;

	DoubleNode<Module*>* item = modules_Queue.getLast();
	while (item != NULL)
	{
		if (!item->data->CleanUp()){ return false; }
		item = item->previous;
	}

	modules_Queue.clear();
	return true;
}

bool Application::ChangeTo(update_status new_state)
{
	// Clear Unnecessary Modules
	modules_Queue.ReduceTo(6);

	switch (new_state)
	{
	case CHANGE_TO_TITLE:
		if (titleModule->Init() == false) { return false; }
		modules_Queue.push(titleModule_Node);
		break;

	case CHANGE_TO_CHOOSE_CITY:
		if (chooseCityModule->Init() == false) { return false; }
		modules_Queue.push(chooseCityModule_Node);
		break;

	case CHANGE_TO_PLAY:
		if (playerModule->Init() == false)        { return false; }
		if (entityManagerModule->Init() == false) { return false; }
		if (sceneModule->Init() == false)         { return false; }

		modules_Queue.push(playerModule_Node);
		modules_Queue.push(entityManagerModule_Node);
		modules_Queue.push(sceneModule_Node);

		break;

	case CHANGE_TO_MAP_PLANE:
		if (planeModule->Init() == false) { return false; }
		modules_Queue.push(planeModule_Node);
		break;

	case CHANGE_TO_STAGE_END:
		if (stageEndModule->Init() == false) { return false; }
		modules_Queue.push(stageEndModule_Node);
		break;

	case CHANGE_TO_CREDITS:
		if (creditsModule->Init() == false) { return false; }
		modules_Queue.push(creditsModule_Node);
		break;

	case CHANGE_TO_HIGHSCORE:
		if (highscoreModule->Init() == false) { return false; }
		modules_Queue.push(highscoreModule_Node);
		break;
	}
	
	return true;
}

void Application::Add_Coin()
{
	// add coin + play fx
	if (coins < 9) { coins++; audioModule->PlayFx(COIN); }
}

bool Application::Lose_Coin()
{
	// return false if no coins left
	if (coins > 0) { coins--; return true; }
	return false;
}