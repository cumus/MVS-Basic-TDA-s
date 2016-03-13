#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiLabel;
class GuiHScrollBar;
struct CVar;
struct Command;

struct ui_label
{
	p2SString text;
	uint x, y;
	bool draggable;
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Called when UI event is raised
	void OnGui(Gui* ui, GuiEvents event);

	bool OnCommand(const Command*, const p2DynArray<p2SString>& arguments, p2SString& return_message);

private:
	SDL_Texture* debug_tex;

	GuiHScrollBar* bar;
	GuiLabel* title;
	p2List<ui_label> labels;

	// EXERCISE 5
	const Command* load = nullptr;
	const Command* save = nullptr;
};

#endif // __j1SCENE_H__