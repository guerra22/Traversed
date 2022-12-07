#include "PanelHierarchy.h"
#include "GameObject.h"
#include "ModuleSceneintro.h"
#include "MeshImporter.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

PanelHierarchy::PanelHierarchy(bool enabled) : UiPanel(enabled)
{
	name = "Hierarchy";
	winHover = true;
}

PanelHierarchy::~PanelHierarchy()
{

}

void PanelHierarchy::Start()
{
	sceneInstance = SceneProperties::Instance();
}

void PanelHierarchy::Update()
{
	if (ImGui::Begin(name.c_str()))
	{
		if (sceneInstance->root != nullptr)
		{
			DisplayGameObject(sceneInstance->root);
			RightClickMenuContextWindow();
		}
	}
	ImGui::End();
}

GameObject* PanelHierarchy::DisplayGameObject(GameObject* go)
{
	GameObject* toReturn = nullptr;

	ImGuiTreeNodeFlags nodeFlags = ImGuiDockNodeFlags_None;
	nodeFlags += ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (go->selected) nodeFlags += ImGuiTreeNodeFlags_Selected;

	if (!go->HasChildren()) nodeFlags |= ImGuiTreeNodeFlags_Leaf;

	//Recursive Display
	const bool nodeOpen = ImGui::TreeNodeEx(go->GetUUName().c_str(), nodeFlags, go->name.c_str());
	if (nodeOpen)
	{
		if (ImGui::IsItemClicked()) { GetSelectedNode(go); }
		if (ImGui::IsItemHovered()) { toReturn = go; }

		RightClickMenuContextItem(go);

#pragma region Drag n Drop
		//Drag
		if (sceneInstance->root != go)
		{
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("Nodes", go, sizeof(GameObject));
				ImGui::Text(go->name.c_str());
				dropGO = go;
				ImGui::EndDragDropSource();
			}
		}
		//Drop
		if (ImGui::BeginDragDropTarget())
		{
			if (ImGui::AcceptDragDropPayload("Nodes"))
			{
				if (dropGO != nullptr) dropGO->SetParent(go);

				dropGO = nullptr;
			}
			ImGui::EndDragDropTarget();
		}
#pragma endregion Drag n Drop

		for (int i = 0; i < go->children.size(); ++i)
		{
			GameObject* aux = DisplayGameObject(go->children[i]);
			if (aux != nullptr) toReturn = aux;
		}

		ImGui::TreePop();
	}
	return toReturn;
}

void PanelHierarchy::RightClickMenuContextItem(GameObject* go)
{
	if (ImGui::IsPopupOpen("Nodes##Window")) return;
	if (hoverGO != nullptr && hoverGO != go) return;
	bool pop = ImGui::BeginPopupContextItem("Nodes##Item", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonDefault_);

	if (pop)
	{
		if (hoverGO == nullptr) hoverGO = go;
		RightClickMenuContent(go);

		ImGui::EndPopup();
	}

	if (!ImGui::IsPopupOpen("Nodes##Item")) hoverGO = nullptr;
}

void PanelHierarchy::RightClickMenuContextWindow()
{
	if (ImGui::IsPopupOpen("Nodes##Item")) return;

	bool pop = ImGui::BeginPopupContextWindow("Nodes##Window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonDefault_);
	if (pop)
	{
		RightClickMenuContent(nullptr);

		ImGui::EndPopup();
	}

}

void PanelHierarchy::RightClickMenuContent(GameObject* go)
{
	GameObject* auxGO = nullptr;
	if (go == nullptr) auxGO = sceneInstance->root;
	else auxGO = go;

	if (ImGui::BeginMenu("Nodes"))
	{
		GameObject* newGO = nullptr;

		if (ImGui::MenuItem("Empty Node"))  auxGO->AddChildren(new GameObject("Empty Node", false));
		if (ImGui::MenuItem("Spatial Node")) auxGO->AddChildren(new GameObject("Spatial Node"));

		if (ImGui::MenuItem("Mesh Node"))
		{
			newGO = new GameObject("Mesh Node");
			newGO->CreateComponent(MESH);
			newGO->CreateComponent(MATERIAL);
			auxGO->AddChildren(newGO);
		}

		if (ImGui::MenuItem("Camera Node"))
		{
			newGO = new GameObject("Camera Node");
			newGO->CreateComponent(CAMERA);
			auxGO->AddChildren(newGO);
		}

		/*if (ImGui::BeginMenu("Primitive Node"))
		{
			if (ImGui::MenuItem("Cube")) MeshImporter::ImportMesh("Assets/Primitives/cube.fbx", auxGO);
			if (ImGui::MenuItem("Sphere")) MeshImporter::ImportMesh("Assets/Primitives/sphere.fbx", auxGO);
			if (ImGui::MenuItem("Plane")) MeshImporter::ImportMesh("Assets/Primitives/plane.fbx", auxGO);
			if (ImGui::MenuItem("Pyramid")) MeshImporter::ImportMesh("Assets/Primitives/pyramid.fbx", auxGO);
			if (ImGui::MenuItem("Cylinder")) MeshImporter::ImportMesh("Assets/Primitives/cylinder.fbx", auxGO);
			if (ImGui::MenuItem("Capsule")) MeshImporter::ImportMesh("Assets/Primitives/capsule.fbx", auxGO);
			ImGui::EndMenu();
		}*/

		ImGui::EndMenu();
	}

	if (ImGui::MenuItem("DELETE", 0, false, go == nullptr ? false : true))
	{
		//auxGO->DeleteGameObject();
		LOG(LOG_TYPE::ATTENTION, "DELETE GAMEOBJECT NOT YET IMPLEMENTED", go->name.c_str());
	}
}

void PanelHierarchy::GetSelectedNode(GameObject* go)
{
	cleanSelected = true;

	cleanSelected = CleanSelected(sceneInstance->root);
	go->selected = true;
}

bool PanelHierarchy::CleanSelected(GameObject* go)
{
	if (!cleanSelected) return false;

	go->selected = false;
	if (go->HasChildren())
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			CleanSelected(go->children[i]);
		}
	}
	return false;
}