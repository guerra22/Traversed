#pragma once
#include "Module.h"
#include "ModuleWindow.h"

#include "External/SDL/include/SDL.h"
#include <vector>

class Application;

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:
	void MainMenu();

	bool fullscreen;
	int screenWidth;
	int screenHeight;

private:
	

};

