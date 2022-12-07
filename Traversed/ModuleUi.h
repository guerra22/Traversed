#ifndef __ModuleUi_H__
#define __ModuleUi_H__

#include "Module.h"

#include <iostream>
#include <vector>

class Application;
class UiPanel;

enum COLORMODE
{
	LightMode = 0,
	DarkMode,
	ClassicMode
};

struct EditorProperties
{
public:
	COLORMODE colorMode = COLORMODE::DarkMode;

	EditorProperties();

	static EditorProperties* Instance();

	static void Delete();

	void SwitchColorMode();

private:
	static EditorProperties* instance;
};

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);

	virtual ~ModuleUI();

	bool Init();
	bool Start();
	bool CleanUp();

	UpdateStatus Update();
	UpdateStatus PostUpdate();

	void DrawEditorGui();

private:
	void BeginRender();
	void EndRender();

	void UpdatePanels();

	void MainMenuBar();

	void FileDialogMenu();

	void SaveSettingsData(pugi::xml_node& save) override;

	void LoadSettingsData(pugi::xml_node& load) override;

private:
	
	std::vector<UiPanel*> panels;
	EditorProperties* eProps = nullptr;
};

#endif // __ModuleEditor_H__