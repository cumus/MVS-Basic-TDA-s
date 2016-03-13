#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2Point.h"

class Gui;
class GuiImage;
class GuiLabel; 
class GuiInputText;
class GuiHScrollBar;

struct SDL_Texture;
struct _TTF_Font;

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	GuiImage* CreateImage(const char* filename);
	GuiImage* CreateImage(const rectangle& atlas_section);
	GuiImage* CreateImage(int w, int h);
	GuiLabel* CreateLabel(const char* text, _TTF_Font* font = nullptr, uint wrap_width = 0);
	GuiInputText* CreateInput(const rectangle& section, const char* default_text, uint width, const iPoint& offset = {0, 0});
	GuiInputText* CreateInput(const char* default_text, uint width, const iPoint& offset = {0, 0});
	GuiHScrollBar* CreateHScrollBar(const rectangle& bar, const rectangle& thumb, const rectangle& bar_offset = {0,0,0,0}, const iPoint& thumb_margins = {0, 0});

	const Gui* FindMouseHover() const;
	const SDL_Texture* GetAtlas() const;
	void SetFocus(const Gui* ui);
	const Gui* GetFocus() const;
	bool CanInteract(const Gui* ui) const;

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

private:

	bool debug = false;
	bool showing_modal = false;
	p2List<Gui*> elements;
	Gui* focus = nullptr;
	SDL_Texture* atlas = nullptr;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__