#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"

#include <iostream>
#include <vector>

class Application;
class UiPanel;
class PanelShaderText;

enum COLORMODE
{
	LightMode = 0,
	DarkMode,
	ClassicMode,
	CustomizeMode
};

struct EditorProperties
{
public:
	COLORMODE colorMode = COLORMODE::CustomizeMode;

	EditorProperties();

	static EditorProperties* Instance();

	static void Delete();

	void SwitchColorMode();

	void SetupImGuiStyle();

	void RequestShaderTextSwitch(std::string shaderResourceUuid);
	bool GetShaderTextRequest()
	{
		if (requestShaderTextSwitch)
		{
			requestShaderTextSwitch = false;
			return true;
		}
		return false;
	}

	std::string GetShaderTextRequestUuid()
	{
		std::string aux = requestShaderTextUuid;
		requestShaderTextUuid = "NULL";
		return aux;
	}
private:
	static EditorProperties* instance;

	bool requestShaderTextSwitch = false;
	std::string requestShaderTextUuid;
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

	void RequestSwitchHandler();

	void UpdatePanels();

	void MainMenuBar();

	void FileDialogMenu();

	void SaveSettingsData(pugi::xml_node& save) override;

	void LoadSettingsData(pugi::xml_node& load) override;

private:
	
	std::vector<UiPanel*> panels;
	PanelShaderText* panelShaderText = nullptr;
	int panelViewPoolOff;
	EditorProperties* eProps = nullptr;
};

#endif // __ModuleEditor_H__