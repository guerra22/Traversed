#pragma once

#include <list>
#include "Globals.h"
#include "Timer.h"
#include "JsonParser.h"


class Module;
class ModuleHardware;
class ModuleCamera3D;
class ModuleWindow;
class ModuleInput;
class ModuleUI;
class ModuleSceneIntro;
class ModuleRenderer3D;

class Application
{
public:
	ModuleWindow* window = nullptr;
	ModuleHardware* hardware = nullptr;
	ModuleInput* input = nullptr;
	ModuleRenderer3D* renderer3D = nullptr;
	ModuleCamera3D* camera = nullptr;
	ModuleUI* ui = nullptr;
	ModuleSceneIntro* sceneintro = nullptr;

	JsonParser jsonFile;
private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> list_modules;

	bool saveRequest;
	bool loadRequest;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	void SaveConfig();
	void LoadConfig();
};