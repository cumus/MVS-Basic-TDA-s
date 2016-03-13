#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
	//debug = true;
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	// Are we showing any modal gui ?
	showing_modal = false;
	for(p2List_item<Gui*>* item = elements.start; item; item = item->next)
	{
		if(item->data->visible == true && item->data->modal == true)
		{
			showing_modal = true;
			break;
		}
	}

	const Gui* mouse_hover = FindMouseHover();
	if(mouse_hover && 
	   mouse_hover->can_focus == true && 
	   App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN)
		SetFocus(mouse_hover);

	p2List_item<Gui*>* item;

	// if TAB find the next item and give it the focus
	if(App->input->GetKey(SDL_SCANCODE_TAB) == j1KeyState::KEY_DOWN)
	{
		int pos = elements.find((Gui*) focus);
		Gui* foc = nullptr;

		if(pos > 0)
		{
			item = elements.At(pos);
			
			if(item) item = item->next;

			for(item; item; item = item->next)
			{
				if(CanInteract(item->data) == true && item->data->can_focus == true)
				{
					foc = item->data;
					break;
				}
			}
		}
		if(foc == nullptr)
		{
			for(item = elements.start; item; item = item->next)
				if(CanInteract(item->data) == true && item->data->can_focus == true)
				{
					foc = item->data;
					break;
				}
		}

		SetFocus(foc);
	}

	// Now the iteration for input and update
	for(item = elements.start; item; item = item->next)
		if(CanInteract(item->data) == true)
			item->data->CheckInput(mouse_hover, focus);

	for(item = elements.start; item; item = item->next)
		if(item->data->visible == true)
			item->data->Update(mouse_hover, focus);

	return true;
}

bool j1Gui::CanInteract(const Gui* ui) const
{
	if(showing_modal == true)
		return ui->interactive && ui->visible && ui->modal;
	else
		return ui->interactive && ui->visible;
}

// Called after all Updates
const Gui* j1Gui::FindMouseHover() const
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	for(p2List_item<Gui*>* item = elements.end; item; item = item->prev)
	{
		if(CanInteract(item->data) == true)
		{
			if(item->data->GetScreenRect().Contains(mouse.x, mouse.y))
			   return item->data;
		}
	}

	return nullptr;
}

void j1Gui::SetFocus(const Gui* ui)
{
	if(ui != focus)
	{
		if(ui != nullptr)
		{
			if(ui->can_focus == true && CanInteract(ui) == true)
			{
				if(focus != nullptr)
				{
					if(focus->listener != nullptr)
						focus->listener->OnGui(focus, GuiEvents::lost_focus);
					focus->OnFocus(false);
				}
				focus = (Gui*)ui;
				focus->OnFocus(true);
				if(focus->listener != nullptr)
					focus->listener->OnGui(focus, GuiEvents::gain_focus);
			}
		}
		else
		{
			if(focus != nullptr)
			{
				if(focus->listener != nullptr)
					focus->listener->OnGui(focus, GuiEvents::lost_focus);
				focus->OnFocus(false);
			}
			focus = nullptr;
		}
	}
}

const Gui* j1Gui::GetFocus() const
{
	return focus;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<Gui*>* item;

	if(showing_modal == true)
	{
		// first non-modal
		for(item = elements.start; item; item = item->next)
		{
			if(item->data->visible == true && item->data->modal == false)
			{
				//item->data->Draw();
				//if(debug == true)
					//item->data->DebugDraw();
			}
		}
		// them modals
		for(item = elements.start; item; item = item->next)
		{
			if(item->data->visible == true && item->data->modal == true)
			{
				item->data->Draw();
				if(debug == true)
					item->data->DebugDraw();
			}
		}
	}
	else
	{
		for(item = elements.start; item; item = item->next)
		{
			if(item->data->visible == true)
			{
				item->data->Draw();
				if(debug == true)
					item->data->DebugDraw();
			}
		}
	}


	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<Gui*>* item;

	for(item = elements.start; item; item = item->next)
		RELEASE(item->data);

	elements.clear();

	return true;
}

// Create a simple image
GuiImage* j1Gui::CreateImage(const char* filename)
{
	GuiImage* ret = NULL;
	SDL_Texture* texture = App->tex->Load(filename);

	if(texture != NULL)
	{
		ret = new GuiImage(texture);
		elements.add(ret);
	}

	return ret;
}

// Create a simple image
GuiImage* j1Gui::CreateImage(const rectangle& section)
{
	GuiImage* ret = new GuiImage(section, atlas);
	elements.add(ret);

	return ret;
}

// Create a simple image
GuiImage* j1Gui::CreateImage(int w, int h)
{
	GuiImage* ret = NULL;

	rectangle r;
	r = {0, 0, w, h};
	ret = new GuiImage(r);
	elements.add(ret);

	return ret;
}

// Create a simple image
GuiLabel* j1Gui::CreateLabel(const char* text, _TTF_Font* font, uint wrap_width)
{
	GuiLabel* ret = NULL;

	if(text != NULL)
	{
		ret = new GuiLabel(text, font, wrap_width);
		elements.add(ret);
	}

	return ret;
}

GuiInputText* j1Gui::CreateInput(const rectangle& section, const char* default_text, uint width, const iPoint& offset)
{
	GuiInputText* ret = new GuiInputText(default_text, width, section, atlas, offset);
	elements.add(ret);

	return ret;
}

GuiInputText* j1Gui::CreateInput(const char* default_text, uint width, const iPoint& offset)
{
	GuiInputText* ret = new GuiInputText(default_text, width, offset);
	elements.add(ret);

	return ret;
}

GuiHScrollBar* j1Gui::CreateHScrollBar(const rectangle& bar, const rectangle& thumb, const rectangle& bar_offset, const iPoint& thumb_margins)
{
	GuiHScrollBar* ret = new GuiHScrollBar(bar, bar_offset, thumb, thumb_margins);
	elements.add(ret);

	return ret;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// EXERCISE 4
bool j1Gui::Load(pugi::xml_node& data)
{
	LOG("Loading UI positions");

	for(pugi::xml_node ui = data.child("ui"); ui; ui = ui.next_sibling("ui"))
	{
		p2List_item<Gui*>* item = elements.At(ui.attribute("id").as_uint(-1));

		if(item)
		{
			item->data->SetLocalPos(ui.attribute("x").as_int(0), ui.attribute("y").as_int(0));
		}
	}

	return true;
}

// EXERCISE 4
bool j1Gui::Save(pugi::xml_node& data) const
{
	LOG("Saving UI positions");

	p2List_item<Gui*>* item = elements.start;
	int i = 0;
	while(item)
	{
		pugi::xml_node ui = data.append_child("ui");
		ui.append_attribute("id") = i++;
		ui.append_attribute("x") = item->data->GetLocalPos().x;
		ui.append_attribute("y") = item->data->GetLocalPos().y;

		item = item->next;
	}

	
	return true;
}