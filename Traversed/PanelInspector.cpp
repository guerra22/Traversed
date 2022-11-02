#include "PanelInspector.h"
#include "ImGuiUtils.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"

PanelInspector::PanelInspector(Application* app) : UiPanel(app)
{
	active = true;

}

PanelInspector::~PanelInspector()
{

}

void PanelInspector::Draw()
{
	selectedGameObject = GetSelectedGameObject();

	ImGui::Begin("properties inspector");
	{
		if (selectedGameObject != nullptr)
		{
			DrawInfoOfGameObject(selectedGameObject);
			DrawTransformComponent();
			DrawMeshComponent();
			DrawMaterialComponent();
		}
	}
	ImGui::End();

}

GameObject* PanelInspector::GetSelectedGameObject()
{
	GameObject* selectedGameObject;
	for (int i = 0; i < App->sceneintro->game_objects.size(); i++)
	{
		if (App->sceneintro->game_objects[i]->IsSelected())
		{
			selectedGameObject = App->sceneintro->game_objects[i];
			return selectedGameObject;
		}
	}

	return nullptr;
}
void PanelInspector::DrawInfoOfGameObject(GameObject* game_object)
{
	ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.43f);
	static char buffer[64];
	strcpy(buffer, game_object->GetName().c_str());
	if (ImGui::InputText("ObjectName", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		game_object->SetName(buffer);
	}
}

void PanelInspector::DrawGameObjectComponents()
{
	for (uint i = 0; i < selectedGameObject->components.size(); i++)
	{
		Component* components = selectedGameObject->components[i];

		if (components != nullptr)
		{
			switch (components->type)
			{
			case COMPONENT_TYPES::TRANSFORM:
			{
				DrawTransformComponent();
				break;
			}
			case COMPONENT_TYPES::MESH:
			{
				DrawMeshComponent();
				break;
			}
			case COMPONENT_TYPES::MATERIAL:
			{
				DrawMaterialComponent();
				break;
			}
			}

			if (components->type == COMPONENT_TYPES::NONE || components->type == COMPONENT_TYPES::UNKNOWN)
			{
				LOGGING("[WARNING] Components invalid");
			}
		}
	}
}

void PanelInspector::DrawTransformComponent()
{
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ComponentTransform* transform = (ComponentTransform*)selectedGameObject->GetComponent(COMPONENT_TYPES::TRANSFORM);

		if (transform != nullptr)
		{
			ImGui::Text("Position");

			ImGui::SameLine(80.0f);

			float3 position = transform->GetPosition();
			float pos[3] = { position.x, position.y, position.z };
			if (ImGui::DragFloat3("Position", pos, 1.0f, 0.0f, 0.0f, "%.3f", NULL))
			{
				transform->SetPosition(float3(pos[0], pos[1], pos[2]));
			}

			ImGui::Text("Rotation");

			ImGui::SameLine(80.0f);

			float3 rotation = transform->GetRotation();
			float rot[3] = { rotation.x, rotation.y, rotation.z };
			if (ImGui::DragFloat3("Rotation", rot, 1.0f, 0.0f, 0.0f, "%.3f", NULL))
			{
				transform->SetRotation(float3(rot[0], rot[1], rot[2]));
			}

			ImGui::Text("Scale");

			ImGui::SameLine(80.0f);

			float3 scale = transform->GetScale();
			float scl[3] = { scale.x, scale.y, scale.z };
			if (ImGui::DragFloat3("Scale", scl, 1.0f, 0.0f, 0.0f, "%.3f", NULL))
			{
				transform->SetScale(float3(scl[0], scl[1], scl[2]));
			}
		}
	}
}

void PanelInspector::DrawMeshComponent()
{
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ComponentMesh* mesh = (ComponentMesh*)selectedGameObject->GetComponent(COMPONENT_TYPES::MESH);

		if (mesh != nullptr)
		{
			ImGui::Text("File path:");

			ImGui::SameLine();

			ImGui::Text("WIP");
			ImGui::Separator();

			ImGui::Text("Mesh Info:");

			ImGui::Text("Vertices:");	ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "  %u", mesh->mesh.num_vertex);
			ImGui::Text("Indices:");	ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "   %u", mesh->mesh.num_index);
			ImGui::Text("UVS:");	ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "   %u", mesh->mesh.num_uvs);
		}
	}
}

void PanelInspector::DrawMaterialComponent()
{
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ComponentMaterial* material = (ComponentMaterial*)selectedGameObject->GetComponent(COMPONENT_TYPES::MATERIAL);

		if (material->materialUsed != nullptr)
		{
			if (material->materialUsed != nullptr)
			{
				bool active = material->IsActive();
				if (ImGui::Checkbox("Apply Texture", &active))
				{
					material->SetIsActive(active);
				}

				if (ImGui::Checkbox("show UVs", &App->renderer3D->checkerTextureApplied))
				{
					App->renderer3D->LoadCheckerTexture();
				}

				ImGui::Text("File:");
				ImGui::SameLine();
				ImGui::Text("WIP");
				ImGui::Text("Texture Data:");
				ImGui::Text("Width:");	ImGui::SameLine(); ImGui::Text(" %u", material->materialUsed->width);
				ImGui::Text("Height:");	ImGui::SameLine(); ImGui::Text("%u", material->materialUsed->height);
			}
		}
	}
}