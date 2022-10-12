#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include <vector>

class Application;
class PanelAbout;
class PanelConfiguration;
class UiPanel;

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
	void LogFPS(float fps, float ms);

	bool fullscreen = false;
	int screenWidth;
	int screenHeight;
	bool Vsync = false;
	float screenBrightness;

	bool testCube = true;

	PanelAbout* about = nullptr;
	PanelConfiguration* configuration = nullptr;

private:
	std::vector<UiPanel*> panels;
};

#endif