#include "PanelInspector.h"
#include "ModuleSceneintro.h"
#include "GameObject.h"

PanelInspector::PanelInspector(bool enabled) : UiPanel(enabled)
{
	name = "Inspector";
}

PanelInspector::~PanelInspector()
{

}

void PanelInspector::Start()
{
	sceneInstance = SceneProperties::Instance();
}

void PanelInspector::Update()
{
	if (ImGui::Begin(name.c_str()))
	{

		//Each Component manages its own ImGui
		GameObject* go = IterateGameObject(sceneInstance->root);

		if (go != nullptr)
		{
			for (auto const& comp : go->components)
			{
				comp.second->UpdateGUI();
			}
		}

	}
	ImGui::End();
}

GameObject* PanelInspector::IterateGameObject(GameObject* go)
{
	GameObject* toReturn = go;

	if (go->selected) return go;
	else
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			toReturn = IterateGameObject(go->children[i]);

			if (toReturn != nullptr && toReturn->selected) return toReturn;

			if (go->children[i]->selected)
			{
				return go->children[i];
			}
		}
	}

	return nullptr;
}