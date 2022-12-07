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

#include "MeshImporter.h"

ComponentMesh::ComponentMesh(GameObject* owner, std::string uuid) : Component(owner, uuid)
{
	this->type = CO_TYPE::MESH;

	camInstance = CameraProperties::Instance();

	displayNormals = false;
	normalsMagnitude = 0.25f;
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

	if (camInstance->gameCameras.size() != 0)
	{
		if (camInstance->gameCameras.at(camInstance->mainCameraId)->camera.renderer != nullptr)
			camInstance->gameCameras.at(camInstance->mainCameraId)->camera.renderer->QueueMesh(this);
	}
}

void ComponentMesh::UpdateGUI()
{
	ImGui::NewLine();
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

	ImGui::NewLine();

	if (mesh == nullptr)
	{
		ImGui::Text("No mesh loaded!");
	}
	else
	{
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

void ComponentMesh::Render(Shader* shader, Shader* debugShader, Camera* camera)
{
	if (!active) return;

	if (owner->GetComponent<ComponentMaterial>(MATERIAL) != nullptr && owner->GetComponent<ComponentTransform>(TRANSFORM) != nullptr)
	{
		mesh->Draw(shader,
			camera,
			owner->GetComponent<ComponentMaterial>(MATERIAL)->GetTexture(),
			owner->GetComponent<ComponentTransform>(TRANSFORM)->GetWorldMatrix());
		if (displayNormals)
			mesh->DrawNormals(
				debugShader,
				camera,
				owner->GetComponent<ComponentTransform>(TRANSFORM)->GetWorldMatrix(),
				faceNormals);
	}
}

MeshRenderer* ComponentMesh::GetMesh()
{
	return this->mesh;
}

void ComponentMesh::SetMesh(MeshRenderer* mesh)
{
	this->mesh = mesh;
}

#pragma region Save/Load
nlohmann::ordered_json ComponentMesh::SaveUnique(nlohmann::JsonData data)
{
	if (mesh != nullptr)
	{
		data.SetString("Path", mesh->mesh.path);
	}
	data.SetBool("Normals", displayNormals);
	data.SetBool("Face_Normals", faceNormals);
	data.SetFloat("Normals_Magnitude", normalsMagnitude);

	return data.data;
}

void ComponentMesh::LoadUnique(nlohmann::JsonData data)
{
	std::string meshToLoad(data.GetString("Path"));
	mesh = new MeshRenderer(MeshImporter::LoadMesh(meshToLoad));

	displayNormals = data.GetBool("Normals");
	faceNormals = data.GetBool("Face_Normals");
	normalsMagnitude = data.GetFloat("Normals_Magnitude");
}

#pragma endregion Save & Load