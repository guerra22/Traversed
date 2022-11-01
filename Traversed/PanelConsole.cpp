#include "PanelConsole.h"
#include "ImGuiUtils.h"

PanelConsole::PanelConsole(Application* app) : UiPanel(app)
{
	active = true;

}

PanelConsole::~PanelConsole()
{

}

void PanelConsole::Draw()
{
	ImGui::Begin("console", &active);
	{

	}
	ImGui::End();

}