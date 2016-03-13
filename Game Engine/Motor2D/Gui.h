#ifndef __GUI_H__
#define __GUI_H__

#include "p2Point.h"

struct _TTF_Font;

#define CURSOR_WIDTH 2

enum GuiEvents
{
	listening_ends,
	mouse_enters,
	mouse_leaves,
	mouse_lclick_down,
	mouse_lclick_up,
	mouse_rclick_down,
	mouse_rclick_up,
	gain_focus,
	lost_focus,
	input_changed,
	input_submit,
	value_changed
};

enum GuiTypes
{
	unknown,
	image,
	label,
	button,
	hscrollbar
};

// ---------------------------------------------------
class Gui
{
	friend class j1Gui;
public:
	Gui();
	virtual ~Gui()
	{}
	virtual void Draw() const
	{}
	virtual void DebugDraw() const;
	virtual void Update(const Gui* mouse_hover, const Gui* focus)
	{}
	virtual void OnFocus(bool focus)
	{}
	void CheckInput(const Gui* mouse_hover, const Gui* focus);
	void SetLocalPos(int x, int y);
	void Center();
	rectangle GetScreenRect() const;
	rectangle GetLocalRect() const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	void SetListener(j1Module* module);
	void SetVisible(bool visible);

protected:
	void SetSize(int w, int h);

public:
	fPoint drag = {0.0f, 0.0f};
	bool interactive = false;
	bool cut_childs = false;
	bool can_focus = false;
	bool modal = false;
	Gui* parent = nullptr;
protected:
	GuiTypes type = GuiTypes::unknown;
	j1Module* listener = nullptr;
	bool visible = true;
private:
	bool mouse_inside = false;
	rectangle rect;
};

// ---------------------------------------------------
class GuiImage : public Gui
{
public:
	GuiImage(const SDL_Texture* texture);
	GuiImage(const rectangle& section, const SDL_Texture* texture = nullptr);
	~GuiImage();

	void SetSection(const rectangle& section);
	void Draw() const;

private:

	rectangle section;
	const SDL_Texture* texture = nullptr;
};

// ---------------------------------------------------
class GuiLabel : public Gui
{
public:
	GuiLabel(const char* text, _TTF_Font* font = nullptr,  uint wrap_width = 0);
	~GuiLabel();

	void SetText(const char* text);
	const SDL_Texture* GetTexture() const;
	void Draw() const;

private:

	uint wrap_width = 0;
	SDL_Texture* texture = nullptr;
	_TTF_Font* font = nullptr;
};

class GuiInputText : public Gui
{
public:
	GuiInputText(const char* default_text, uint width, const rectangle& section, const SDL_Texture* texture, const iPoint& offset = {0, 0});
	GuiInputText(const char* default_text, uint width, const iPoint& offset = {0, 0});
	~GuiInputText();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw() const;
	void OnFocus(bool focus);

	const char* GetString() const;
	void Clear();

private:

	GuiLabel text;
	GuiImage image;
	p2SString input;
	iPoint cursor_coords = {0, 0};
	int last_cursor = 0;
	bool had_focus = false;
};

class GuiHScrollBar : public Gui
{
public:
	GuiHScrollBar(const rectangle& bar, const rectangle& offset, const rectangle& thumb, iPoint margins);
	~GuiHScrollBar();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw() const;
	float GetValue() const;

private:

	GuiImage bar;
	GuiImage thumb;
	iPoint margins;
	int min_x = 0;
	int max_x = 0;
	int thumb_pos = 0;
};

#endif // __GUI_H__
