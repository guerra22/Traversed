#include "PanelHierarchy.h"
#include "ImGuiUtils.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"

PanelHierarchy::PanelHierarchy(Application* app) : UiPanel(app)
{
	active = true;
}

PanelHierarchy::~PanelHierarchy()
{

}

void PanelHierarchy::Draw()
{
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin("Game Object");
	{
		GameObjectList();
	}
	ImGui::End();
}

void PanelHierarchy::GameObjectList()
{
	if (!App->sceneintro->game_objects.empty())
	{
		for (uint i = 0; i < App->sceneintro->game_objects.size(); i++)
		{
			ImGui::MenuItem(App->sceneintro->game_objects[i]->GetName().c_str());
			{
				if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
				{
					App->sceneintro->game_objects[i]->SelectItem();
				}
			}
		}
	}
}