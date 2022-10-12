#ifndef __PANEL_CONFIGURATION_H_
#define __PANEL_CONFIGURATION_H_

#define IMGUI_YELLOW ImVec4(1.f,1.f,0.f,1.f)
#define IMGUI_PRINT(field, format, ...) \
	ImGui::Text(field); \
	ImGui::SameLine(); \
	ImGui::TextColored(IMGUI_YELLOW, format, __VA_ARGS__)

#include "PanelAbout.h"

class PanelConfiguration : public UiPanel
{
public:
	PanelConfiguration(Application* app);
	virtual ~PanelConfiguration();

	void Draw() override;

	bool fullscreen = false;
	int screenWidth;
	int screenHeight;
	bool Vsync = false;
	float screenBrightness;

};

#endif

