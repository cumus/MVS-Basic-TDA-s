#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Gui.h"
#include "Gui.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Console.h"

// Helper function ---
void strcpy_tolower(char* dst, const char* src)
{
	while(*dst++ = tolower(*src++));
}

j1Console::j1Console() : j1Module(), last_error("No error")
{
	name.create("console");
}

// Destructor
j1Console::~j1Console()
{}

// Called before render is available
bool j1Console::Awake(pugi::xml_node& config)
{
	LOG("Loading Console");
	bool ret = true;

	return ret;
}

// Called when the render is available
bool j1Console::Start()
{
	LOG("Creating Console UI");
	bool ret = true;

	// load font ---
	font = App->font->Load("fonts/ubuntu/UbuntuMono-R.ttf", 14);

	// Setup gui ---
	text = App->gui->CreateLabel(" ", font);
	text->SetVisible(showing);
	text->interactive = true;
	text->drag = {0, 1};
	text->modal = true;
	input = App->gui->CreateInput(">", App->render->camera.w, {0, 0});
	input->interactive = true;
	input->can_focus = true;
	input->SetLocalPos(LEFT_MARGIN, int(App->render->camera.h * CONSOLE_HEIGHT));
	input->SetListener(this);
	input->modal = true;
	input->SetVisible(showing);

	// Create some default commands
	quit = CreateCommand("quit", this);
	list = CreateCommand("list", this);

	return ret;
}

// --
bool j1Console::PreUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == j1KeyState::KEY_DOWN)
	{
		showing = !showing;
		text->SetVisible(showing);
		input->SetVisible(showing);
		if(showing == true)
		{
			App->gui->SetFocus(input);
		}
	}

	return ret;
}

// --
bool j1Console::PostUpdate()
{
	bool ret = true;

	if(output_dirty == true)
	{
		output_dirty = false;
		text->SetText(output.GetString());
		text->SetLocalPos(LEFT_MARGIN, int(App->render->camera.h * CONSOLE_HEIGHT) - text->GetScreenRect().h);
	}

	if(showing == true)
	{
		SDL_Rect c = App->render->camera;
		c.h = int(c.h * CONSOLE_HEIGHT);
		App->render->DrawQuad({0, 0, c.w, c.h}, 0, 0, 0, 250, true, false);
		rectangle r = input->GetLocalRect();
		App->render->DrawQuad({r.x, r.y, r.w, r.h}, 0, 0, 100, 250, true, false);
	}

	return ret;
}

// Called before quitting
bool j1Console::CleanUp()
{
	LOG("Freeing Console");

	return true;
}

const Command* j1Console::FindCommand(const char* name) const
{
	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE)
	{
		char search[COMMAND_NAME_SIZE];
		strcpy_tolower(search, name);

		for(uint i = 0; i < commands.Count(); ++i)
		{
			if(strcmp(commands[i].name, search) == 0)
				return &commands[i];
		}
	}

	return nullptr;
}

const Command* j1Console::CreateCommand(const char* name, j1Module* listener, uchar min_args, uchar max_args)
{
	const Command* ret = nullptr;

	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE && FindCommand(name) == NULL && FindCVar(name) == nullptr)
	{
		Command com;
		strcpy_tolower(com.name, name);
		com.listener = listener;
		com.min_arguments = min_args;
		com.max_arguments = max_args;

		commands.PushBack(com);
		ret = &commands[commands.Count() - 1];
	}

	return ret;
}

const CVar* j1Console::CreateCVar(const char* name, const char* string, j1Module* listener, bool read_only, bool serialize)
{
	CVar* ret = nullptr;

	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE && FindCommand(name) == nullptr && FindCVar(name) == nullptr)
	{
		CVar var;
		strcpy_tolower(var.name, name);
		var.listener = listener;
		var.read_only = read_only;
		var.serialize = serialize;
		var.type = CVar::is_string;

		cvars.PushBack(var);
		ret = &cvars[cvars.Count() - 1];

		int len = strlen(string);
		ret->value.s = new char[len+1];
		strcpy_s(ret->value.s, len + 1, string);
	}

	return ret;
}

const CVar* j1Console::CreateCVar(const char* name, float value, j1Module* listener, bool read_only, bool serialize)
{
	CVar* ret = nullptr;

	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE && FindCommand(name) == nullptr && FindCVar(name) == nullptr)
	{
		CVar var;
		strcpy_tolower(var.name, name);
		var.listener = listener;
		var.read_only = read_only;
		var.serialize = serialize;

		var.value.f = value;
		var.type = CVar::is_float;

		cvars.PushBack(var);
		ret = &cvars[cvars.Count() - 1];
	}

	return ret;
}

const CVar* j1Console::CreateCVar(const char* name, int value, j1Module* listener, bool read_only, bool serialize)
{
	CVar* ret = nullptr;

	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE && FindCommand(name) == nullptr && FindCVar(name) == nullptr)
	{
		CVar var;
		strcpy_tolower(var.name, name);
		var.listener = listener;
		var.read_only = read_only;
		var.serialize = serialize;

		var.value.i = value;
		var.type = CVar::is_int;

		cvars.PushBack(var);
		ret = &cvars[cvars.Count() - 1];
	}

	return ret;
}

const CVar* j1Console::CreateCVar(const char* name, uint value, j1Module* listener, bool read_only, bool serialize)
{
	CVar* ret = nullptr;

	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE && FindCommand(name) == nullptr && FindCVar(name) == nullptr)
	{
		CVar var;
		strcpy_tolower(var.name, name);
		var.listener = listener;
		var.read_only = read_only;
		var.serialize = serialize;

		var.value.u = value;
		var.type = CVar::is_uint;

		cvars.PushBack(var);
		ret = &cvars[cvars.Count() - 1];
	}

	return ret;
}

const CVar* j1Console::CreateCVar(const char* name, bool value, j1Module* listener, bool read_only, bool serialize)
{
	CVar* ret = nullptr;

	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE && FindCommand(name) == nullptr && FindCVar(name) == nullptr)
	{
		CVar var;
		strcpy_tolower(var.name, name);
		var.listener = listener;
		var.read_only = read_only;
		var.serialize = serialize;

		var.value.b = value;
		var.type = CVar::is_bool;

		cvars.PushBack(var);
		ret = &cvars[cvars.Count() - 1];
	}

	return ret;
}

const CVar* j1Console::FindCVar(const char* name) const
{
	if(name != nullptr && strlen(name) < COMMAND_NAME_SIZE)
	{
		char search[COMMAND_NAME_SIZE];
		strcpy_tolower(search, name);

		for(uint i = 0; i < cvars.Count(); ++i)
		{
			if(strcmp(cvars[i].name, search) == 0)
				return &cvars[i];
		}
	}

	return nullptr;
}

bool j1Console::ProcessString(const char* input)
{
	bool ret = false;

	last_message.Clear();
	if(input != nullptr && strlen(input) > 0 && strlen(input) < MAX_INPUT_LINE_SIZE)
	{
		char line[MAX_INPUT_LINE_SIZE];
		strcpy_s(line, MAX_INPUT_LINE_SIZE, input);

		char* context = nullptr;
		char* token = strtok_s(line, " ", &context);

		arguments.Clear();
		do
		{
			arguments.PushBack(p2SString(token));
		} while(token = strtok_s(NULL, " ", &context));

		uint nargs = arguments.Count() - 1;

		const Command* com = FindCommand(arguments[0].GetString());

		if(com != nullptr && com->listener != nullptr)
		{
			if(nargs >= com->min_arguments && nargs <= com->max_arguments)
			{
				// If we reach this point we are ready to call a listener
				if(ret = com->listener->OnCommand(com, arguments, last_message))
					last_error.create("No error");
				else
				{
					last_error = last_message;
					last_message.Clear();
				}
			}
			else
				last_error.create("Command arguments mismatch");
		}
		else
		{
			const CVar* var = FindCVar(arguments[0].GetString());

			if(var == nullptr)
				last_error.create("Command / CVar not found");
			else
			{
				switch(nargs)
				{
					case 1:
					{
						if(((CVar*)var)->SetFromString(arguments[1].GetString()) == true)
						{
							if(var->listener != nullptr)
								var->listener->OnCVar(var);
						}
					}
					case 0:
					{
						char output[COMMAND_NAME_SIZE + 25];
						sprintf_s(output, COMMAND_NAME_SIZE + 25, "%s: %s", var->name, var->Printable());
						last_message += output;
						ret = true;
					} break;
					default:
					last_error.create("Command arguments mismatch");
					break;
				}
			}
		}
			
	}
	else
		last_error.create("Invalid input line");

	if(ret == true)
		Print(last_message.GetString());
	else
		PrintError(last_error.GetString());

	return ret;
}

const char* j1Console::GetLastError() const
{
	return last_error.GetString();
}

const char* j1Console::GetLastResult() const
{
	return last_message.GetString();
}

void j1Console::Print(const char* string)
{
	output += "\n";
	output += string;
	output_dirty = true;
}

void j1Console::PrintError(const char* string)
{
	output += "\nERROR: ";
	output += string;
	output_dirty = true;
}

void j1Console::OnGui(Gui* ui, GuiEvents event)
{
	if(ui == input && event == GuiEvents::input_submit && strlen(input->GetString()) > 0)
	{
		this->ProcessString(input->GetString());
		input->Clear();
	}
}

bool j1Console::OnCommand(const Command* command, const p2DynArray<p2SString>& arguments, p2SString& return_message)
{
	bool ret = true;

	if(command == quit)
	{
		App->Quit();
		return_message.create("Bye!");
	}
	else if(command == list)
	{
		return_message.create("Commands: ");
		uint size = commands.Count();
		for(uint i = 0; i < size; ++i)
		{
			return_message += commands[i].name;
			if(i < size - 1)
				return_message += ", ";
		}

		return_message += "\nCvars: ";
		size = cvars.Count();
		for(uint i = 0; i < size; ++i)
		{
			return_message += cvars[i].name;
			if(i < size - 1)
				return_message += ", ";
		}
	}
	
	return ret;
}

const char* CVar::Printable() const
{
	static char ret[10];

	strcpy_s(ret, 10, "??");

	switch(type)
	{
		case CVar::is_bool:
		strcpy_s(ret, 10, (value.b) ? "true" : "false");
		break;

		case CVar::is_float:
		sprintf_s(ret, 10, "0.3f", value.f);
		break;

		case CVar::is_int:
		sprintf_s(ret, 10, "%d", value.i);
		break;

		case CVar::is_uint:
		sprintf_s(ret, 10, "%uu", value.u);
		break;

		case CVar::is_string:
		return value.s;
	}

	return ret;
}

bool CVar::SetFromString(const char* new_value)
{
	bool ret = false;

	switch(type)
	{
		case CVar::is_bool:
		{
			bool v = !(_stricmp(new_value, "false") == 0 || strcmp(new_value, "0") == 0);
			if(ret = (v != value.b))
				value.b = v;
		} break;

		case CVar::is_float:
		{
			float v = atof(new_value);
			if(ret = (v != value.f))
				value.f = v;
		} break;

		case CVar::is_int:
		{
			int v = atoi(new_value);
			if(ret = (v != value.i))
				value.i = v;
		} break;

		case CVar::is_uint:
		{
			int v = atoi(new_value);
			if(ret = (v != value.u))
				value.u = v;
		} break;

		case CVar::is_string:
		{
			if(ret = (strcmp(new_value, value.s) != 0))
			{
				int len = strlen(new_value);
				if(len != strlen(value.s))
				{
					RELEASE_ARRAY(value.s);
					value.s = new char[len + 1];
				}
				strcpy_s(value.s, len + 1, new_value);
			}
		} break;
	}

	return ret;
}