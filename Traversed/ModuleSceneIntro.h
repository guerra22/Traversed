#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

class Application;
class Primitive;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();

	//TODO 9: Create an "OnCollision" method specific for this module

private:
	std::vector<Primitive*> primitives;
};
