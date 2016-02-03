#ifndef __j1CONSOLE_H__
#define __j1CONSOLE_H__

#include "j1Module.h"
#include "p2DynArray.h"

#define LEFT_MARGIN 3
#define COMMAND_NAME_SIZE 25
#define MAX_INPUT_LINE_SIZE 250
#define CONSOLE_HEIGHT 0.4f // percentage of full screen height

class GuiLabel;
class GuiInputText;
struct _TTF_Font;

struct Command
{
	char name[COMMAND_NAME_SIZE];
	uchar min_arguments = 0;
	uchar max_arguments = 0;
	j1Module* listener = nullptr;
};

struct CVar
{
	~CVar()
	{
		if(type == CVar::is_string)
			RELEASE_ARRAY(value.s);
	}

	union
	{
		char* s;
		float f;
		int i = 0;
		uint u;
		bool b;
	} value;

	enum
	{
		is_string,
		is_float,
		is_int,
		is_uint,
		is_bool
	} type;

	char name[COMMAND_NAME_SIZE];
	bool read_only = false;
	bool serialize = false;
	j1Module* listener = nullptr;

	const char* Printable() const;
	bool SetFromString(const char* new_value);
};

class j1Console : public j1Module
{
public:

	j1Console();

	// Destructor
	virtual ~j1Console();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called when therender is available
	bool Start();

	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Add new command
	const Command* CreateCommand(const char* name, j1Module* listener = nullptr, uchar min_args = 0, uchar max_args = 0);

	// Finds a command
	const Command* FindCommand(const char* name) const;

	// Add new cvar
	const CVar* CreateCVar(const char* name, const char* string, j1Module* listener = nullptr, bool read_only = false, bool serialize = false);
	const CVar* CreateCVar(const char* name, float value, j1Module* listener = nullptr, bool read_only = false, bool serialize = false);
	const CVar* CreateCVar(const char* name, int value, j1Module* listener = nullptr, bool read_only = false, bool serialize = false);
	const CVar* CreateCVar(const char* name, uint value, j1Module* listener = nullptr, bool read_only = false, bool serialize = false);
	const CVar* CreateCVar(const char* name, bool value, j1Module* listener = nullptr, bool read_only = false, bool serialize = false);

	// Finds a cvar
	const CVar* FindCVar(const char* name) const;

	// Process a string input by user
	bool ProcessString(const char* input);

	const char* GetLastError() const;
	const char* GetLastResult() const;

	// Liste to gui events
	void OnGui(Gui* ui, GuiEvents event);

	bool OnCommand(const Command*, const p2DynArray<p2SString>& arguments, p2SString& return_message);
	void Print(const char* string);
	void PrintError(const char* string);

private:

	p2DynArray<CVar> cvars;
	p2DynArray<Command> commands;
	p2SString last_error;
	p2SString last_message;
	p2SString output;
	bool output_dirty = false;
	p2DynArray<p2SString> arguments;
	_TTF_Font* font;

	GuiLabel* text;
	GuiInputText* input;
	bool showing = false;

	const Command* quit = nullptr;
	const Command* list = nullptr;
};

#endif // __j1CONSOLE_H__