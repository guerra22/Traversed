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
	Timer	fps_timer;
	Uint32	frames;
	int		fps_counter;
	int		last_frame_ms;
	int		last_fps;
	int		capped_ms;

	std::list<Module*> list_modules;

	bool saveRequest;
	bool loadRequest;

	std::string app_name;
	std::string organization_name;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	const char* GetAppName() const;
	void SetAppName(const char* name);
	const char* GetOrganizationName() const;
	void SetOrganizationName(const char* name);
	uint GetFramerateLimit() const;
	void SetFramerateLimit(uint max_framerate);
	void RequestBrowser(const char* url) const;
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	void SaveConfig();
	void LoadConfig();
};