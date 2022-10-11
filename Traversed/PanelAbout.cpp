#include "PanelAbout.h"

#include "External/Imgui/imgui.h"

PanelAbout::PanelAbout()
{
	active = false;
}

PanelAbout::~PanelAbout()
{

}

void PanelAbout::Draw()
{
	ImGui::Begin("hello");
	{
		ImGui::Text("testing");
	}
	ImGui::End();

}