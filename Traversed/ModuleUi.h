#pragma once
#include "Module.h"
#include "Globals.h"
#include "lib/Imgui/imgui.h"
#include "lib/Imgui/backends/imgui_impl_sdl.h"
#include "lib/SDL/include/SDL.h"
#include <vector>

class UI_Item;

class ModuleUI : public Module
{
public:
	ModuleUI(bool start_updated);
	~ModuleUI();

	bool Init();

	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void RenderImGui();

	bool MainMenu();

	bool CheckDataWindows();

private:
	

};

