#include "PanelHierarchy.h"
#include "ImGuiUtils.h"

PanelHierarchy::PanelHierarchy(Application* app) : UiPanel(app)
{
	active = true;

}

PanelHierarchy::~PanelHierarchy()
{

}

void PanelHierarchy::Draw()
{
	ImGui::Begin("Game Object", &active);
	{

	}
	ImGui::End();

}