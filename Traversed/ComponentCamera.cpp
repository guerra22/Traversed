#include "ComponentCamera.h"

#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "ComponentTransform.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_impl_sdl.h"
#include "External/ImGui/imgui_impl_opengl3.h"

ComponentCamera::ComponentCamera(GameObject* owner) : Component(owner)
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
}

ComponentCamera::~ComponentCamera()
{

}

void ComponentCamera::Init()
{

}

void ComponentCamera::Update()
{
	/*CompTransform* transform = owner->GetComponent<CompTransform>(TRANSFORM);
	Quat lookingDir = Quat::identity;

	float4x4 aux = camera.frustum.WorldMatrix();
	aux.SetRotatePart(lookingDir);
	camera.frustum.SetWorldMatrix(aux.Float3x4Part());
	camera.Position += transform->position;
	camera.Reference += transform->position;
	camera.frustum.pos += transform->position;*/
}

void ComponentCamera::UpdateGUI()
{
	if (isMainCamera) ImGui::Text("Im the main camera!");
}