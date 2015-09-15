#include "ModuleHighscore.h"

ModuleHighscore::ModuleHighscore(Application* app) : Module(app){}
bool ModuleHighscore::Init(){ return true; }
update_status ModuleHighscore::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleHighscore::Update(){ return CHANGE_TO_PLAY; }
update_status ModuleHighscore::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleHighscore::CleanUp(){ return true; }