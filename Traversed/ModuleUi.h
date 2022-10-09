#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include <vector>

class Application;
class AboutUi;
class UiElements;

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

	bool fullscreen = false;
	int screenWidth = 0;
	int screenHeight = 0;

	bool enableAboutUi = false;

	AboutUi* aboutUi = nullptr;

private:
	
	std::vector<UiElements*> menus;
};

#endif