#include "ComponentMesh.h"
#include "ModuleCamera3D.h"
#include "Renderer.h"
#include "Shader.h"
#include "GameObject.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_impl_sdl.h"
#include "External/ImGui/imgui_impl_opengl3.h"

ComponentMesh::ComponentMesh(GameObject* owner) : Component(owner)
{
	this->type = CO_TYPE::MESH;

	camInstance = CameraProperties::Instance();
}

ComponentMesh::~ComponentMesh()
{
	if (mesh != nullptr)
	{
		RELEASE(mesh);
	}
}

void ComponentMesh::Update()
{
	if (mesh == nullptr) return;

	camInstance->editorCamera.renderer->QueueMesh(this);
}

void ComponentMesh::UpdateGUI()
{
	if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_Leaf))
	{
		ImGui::Checkbox("Active##MeshRenderer", &this->active);

		ImGui::SameLine();
		ImGui::Checkbox("Display Normals", &displayNormals);

		if (displayNormals)
		{
			ImGui::Checkbox("Face Normals ", &faceNormals);
			if (ImGui::SliderFloat("Line Magnitude", &normalsMagnitude, 0.1f, 1.0f, "%.2f"))
			{
				mesh->CleanNormals();
				mesh->CreateNormals(normalsMagnitude);
			}
		}

		//Vertex
		std::string txt = "Vertices: ";
		txt += std::to_string(mesh->mesh.vertices.size());
		ImGui::Text(txt.c_str());
		//Indices
		txt = "Indices: ";
		txt += std::to_string(mesh->mesh.indices.size());
		ImGui::Text(txt.c_str());
		//Faces
		txt = "Faces: ";
		txt += std::to_string(mesh->mesh.numFaces);
		ImGui::Text(txt.c_str());
	}
}

void ComponentMesh::Render(Shader* shader, Shader* debugShader)
{
	if (!active) return;
	mesh->Draw(shader,
		owner->GetComponent<ComponentMaterial>(MATERIAL)->GetTexture(),
		owner->GetComponent<ComponentTransform>(TRANSFORM)->GetWorldMatrix());
	if (displayNormals)
		mesh->DrawNormals(
			debugShader,
			owner->GetComponent<ComponentTransform>(TRANSFORM)->GetWorldMatrix(),
			faceNormals);
}

MeshRenderer* ComponentMesh::GetMesh()
{
	return this->mesh;
}

void ComponentMesh::SetMesh(MeshRenderer* mesh)
{
	this->mesh = mesh;
}