#include "ModuleCredits.h"

ModuleCredits::ModuleCredits(Application* app) : Module(app){}
bool ModuleCredits::Init(){ return true; }
update_status ModuleCredits::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleCredits::Update(){ return CHANGE_TO_PLAY; }
update_status ModuleCredits::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleCredits::CleanUp(){ return true; }