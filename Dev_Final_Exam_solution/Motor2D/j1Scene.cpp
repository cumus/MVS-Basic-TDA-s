#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Console.h"
#include "Gui.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	// EXERCISE 3
	// Add all labels
	for(pugi::xml_node label = config.child("ui_label"); label; label = label.next_sibling("ui_label"))
		labels.add({label.child_value(), label.attribute("x").as_int(0), label.attribute("y").as_int(0), label.attribute("drag").as_bool(false)});

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	load = App->console->CreateCommand("load", this, 1, 1);
	save = App->console->CreateCommand("save", this, 1, 1);

	debug_tex = App->tex->Load("maps/path.png");

	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	// EXERCISE 3
	p2List_item<ui_label>* item = labels.start;
	while(item)
	{
		GuiLabel* l = App->gui->CreateLabel(item->data.text.GetString());
		l->SetLocalPos(item->data.x, item->data.y);
		if(item->data.draggable == true)
		{
			l->interactive = true;
			l->drag.x = l->drag.y = 1.0f;
		}

		item = item->next;
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	/*
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		//App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		//App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += (int) floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= (int) floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += (int) floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= (int)floor(200.0f * dt);

	App->map->Draw();
	
	int x, y;
	App->input->GetMousePosition(x, y);

	// Debug pathfinding ------------------------------
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}
	*/
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

// Called when UI event is raised
void j1Scene::OnGui(Gui* ui, GuiEvents event)
{
}

bool j1Scene::OnCommand(const Command* com, const p2DynArray<p2SString>& arguments, p2SString& return_message)
{
	// EXERCISE 5
	if(com == save)
	{
		App->SaveGame(arguments[1].GetString());
	}
	else if(com == load)
	{
		App->LoadGame(arguments[1].GetString());
	}

	return false;
}