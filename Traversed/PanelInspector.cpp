#include "PanelInspector.h"
#include "ImGuiUtils.h"

PanelInspector::PanelInspector(Application* app) : UiPanel(app)
{
	active = true;

}

PanelInspector::~PanelInspector()
{

}

void PanelInspector::Draw()
{
	ImGui::Begin("properties inspector", &active);
	{

	}
	ImGui::End();

}