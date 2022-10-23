#ifndef __PANEL_CONFIGURATION_H_
#define __PANEL_CONFIGURATION_H_

#define FPS_LOG_SIZE 100
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

	void AddFPS(float fps, float ms);

	bool fullscreen = false;
	bool resizable = false;
	bool fulldesktop = false;
	int screenWidth;
	int screenHeight;
	bool Vsync = false;
	float screenBrightness;

private:
	std::vector<float> fps_log;
	std::vector<float> ms_log;
};

#endif

