#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

class Application;
class Primitive;
class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();

	GameObject* CreateEmptyGameObject(const char* name = nullptr, GameObject* parent = nullptr);
public:
	std::vector<GameObject*> game_objects;
	GameObject* rootObject;
	
private:
	std::vector<Primitive*> primitives;
};
