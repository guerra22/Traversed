#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleWindow.h"

#include "lib/Imgui/imgui.h"
#include "lib/SDL/include/SDL.h"
#include <vector>

class UI_Item;
class Application;

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Init();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void RenderImGui();

	bool MainMenu();

private:
	

};

