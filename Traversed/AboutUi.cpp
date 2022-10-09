#include "AboutUi.h"

#include "External/Imgui/imgui.h"

AboutUi::AboutUi()
{
	active = false;
}

AboutUi::~AboutUi()
{

}

void AboutUi::Draw()
{
	ImGui::Begin("hello");
	{
		ImGui::Text("testing");
	}
	ImGui::End();

}