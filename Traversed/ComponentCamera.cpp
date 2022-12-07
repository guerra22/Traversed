#include "ComponentCamera.h"

#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "Renderer.h"
#include "MeshRenderer.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_impl_sdl.h"
#include "External/ImGui/imgui_impl_opengl3.h"

ComponentCamera::ComponentCamera(GameObject* owner, std::string uuid) : Component(owner, uuid)
{
	this->type = CAMERA;

	camInstance = CameraProperties::Instance();

	if (camInstance->gameCameras.size() == 0)
	{
		isMainCamera = true;
		camInstance->mainCameraId = 0;
	}
	else isMainCamera = false;

	//Includes camera to the list of game cameras.
	camInstance->gameCameras.emplace_back(this);

	numOfMeshes = 0;
	SetFustrumBox();
}

ComponentCamera::~ComponentCamera()
{
	RELEASE(frustumMesh->mesh);
	RELEASE(frustumMesh);
}

void ComponentCamera::Init()
{

}

void ComponentCamera::Update()
{
	ComponentTransform* transform = owner->GetComponent<ComponentTransform>(TRANSFORM);

	if (transform != nullptr)
	{
		float4x4 aux = camera.frustum.WorldMatrix();
		aux.SetRotatePart(transform->GetRotationAsQuat());
		camera.frustum.SetWorldMatrix(aux.Float3x4Part());
		camera.Position = transform->position;
		camera.Reference = transform->position;
		camera.frustum.pos = transform->position;

		//Frustum Mesh Debug
		if (frustumMesh == nullptr) return;
		frustumMesh->model = transform->GetWorldMatrix();
		camInstance->editorCamera.renderer->QueueDebug(frustumMesh);
	}

	if (camera.renderer != nullptr) numOfMeshes = camera.renderer->numOfMeshes;
}

void ComponentCamera::UpdateGUI()
{
	if (isMainCamera) ImGui::Text("Im the main 'Game' camera!");

	ImGui::NewLine();

	std::string aux = "Num. of meshes in frustum: ";
	aux += std::to_string(numOfMeshes);
	ImGui::Text(aux.c_str());
}

void ComponentCamera::SetFustrumBox()
{
	Meshe mesh;
	float3 cornersArr[8];
	camera.frustum.farPlaneDistance = 10;
	camera.frustum.front = -camera.Z;

	camera.frustum.GetCornerPoints(cornersArr);
	camera.frustum.farPlaneDistance = 500.0f;
	camera.frustum.front = camera.Z;

	for (int i = 0; i < 8; ++i)
	{
		Vertex v;
		v.position = cornersArr[i];
		mesh.vertices.emplace_back(v);
	}
	mesh.indices.reserve(16);

	mesh.indices = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5,
		2, 6, 3, 7,
		3, 1, 0, 2,
		6, 4, 7, 5
	};
	frustumMesh = new DebugMesh(new MeshRenderer(mesh, false), float4x4::identity);
}

#pragma region Save/Load
nlohmann::ordered_json ComponentCamera::SaveUnique(nlohmann::JsonData data)
{
	data.SetBool("Main_camera", isMainCamera);

	return data.data;
}

void ComponentCamera::LoadUnique(nlohmann::JsonData data)
{
	this->isMainCamera = data.GetBool("Main_camera");
	camInstance->gameCameras.at(camInstance->mainCameraId)->isMainCamera = false;

	camInstance->mainCameraId = camInstance->gameCameras.size() - 1;
}

#pragma endregion Save & Load