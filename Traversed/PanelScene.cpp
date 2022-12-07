#include "PanelScene.h"
#include "ModuleCamera3D.h"
#include "ModuleSceneintro.h"
#include "FrameBuffer.h"

#include "Camera.h"
#include "GameObject.h"
#include "ComponentTransform.h"

#include "External/MathGeo/include/Math/float2.h"
#include "External/ImGui/imgui_internal.h"
#include "External/ImGuizmo/ImGuizmo.h"

PanelScene::PanelScene(bool enabled) : UiPanel(enabled)
{
	name = "Scene";
	segmentSize = { 0, 0 };

	camInstance = CameraProperties::Instance();
	sceneInstance = SceneProperties::Instance();
}

PanelScene::~PanelScene()
{
	//renderer->CleanUp();
	//RELEASE(renderer);
}

void PanelScene::Start()
{
	//renInstance->render = new Renderer({ segmentSize.x, segmentSize.y });
	//camInstance->editorCamera.renderer = new Renderer({ segmentSize.x, segmentSize.y });
	camInstance->editorCamera.SetRenderer({ segmentSize.x, segmentSize.y });
}

void PanelScene::Update()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar;
	flags |= ImGuiWindowFlags_NoScrollWithMouse;

	if (ImGui::Begin(name.c_str(), 0, flags))
	{
		ImVec2 pos = ImGui::GetWindowPos();
		ImVec2 size = ImGui::GetWindowSize();
		size.x += pos.x;
		size.y += pos.y;

		if (ImGui::IsMouseHoveringRect(pos, size)) camInstance->isMouseOnScene = true;
		else camInstance->isMouseOnScene = false;

		ImVec2 aux = ImGui::GetContentRegionAvail();
		aux.y = (aux.x / 16) * 9;

		if (aux.x != segmentSize.x || aux.y != segmentSize.y)
		{
			segmentSize.x = aux.x;
			segmentSize.y = aux.y;
			
			if (camInstance->editorCamera.renderer == nullptr)
			{
				camInstance->editorCamera.SetRenderer({ segmentSize.x, segmentSize.y });
				//camInstance->editorCamera.renderer = new Renderer({ segmentSize.x, segmentSize.y });
			}
			else camInstance->editorCamera.renderer->Resize({ segmentSize.x, segmentSize.y });
		}

		RenderSpace();
		Guizmo(camInstance->editorCamera, sceneInstance->GetSelectedGO());
	}
	ImGui::End();
}

void PanelScene::RenderSpace()
{
	float aux = (ImGui::GetWindowHeight() + 20 - segmentSize.y) * 0.5f;

	//Render Framebuffer
	ImGui::SetCursorPosY(aux);
	ImTextureID texID = (ImTextureID)camInstance->editorCamera.renderer->GetFrameBufffer()->GetTextureBuffer();
	ImGui::Image(texID, segmentSize, ImVec2(0, 1), ImVec2(1, 0));
}

void PanelScene::Guizmo(Camera& cam, GameObject* go)
{
	if (go == nullptr) return;
	ComponentTransform* transform = go->GetComponent<ComponentTransform>(TRANSFORM);
	if (transform == nullptr) return;

	//ImGuizmo::Enable(true);

	ImGuizmo::SetDrawlist();

	float x = ImGui::GetWindowPos().x;
	float y = ImGui::GetWindowPos().y;
	float w = segmentSize.x;
	float h = segmentSize.y;
	//Guizmo

	float4x4 aux = transform->GetWorldMatrix();

	ImGuizmo::SetRect(x, y, w, h);
	if (ImGuizmo::Manipulate(cam.GetViewMatrix(), cam.GetProjectionMatrix(), (ImGuizmo::OPERATION)sceneInstance->GetGuizmoOperation(), ImGuizmo::WORLD, &aux.v[0][0]))
	{
		aux.Transpose();
		transform->SetWorldMatrix(aux);
	}

	if (ImGuizmo::IsOver())
	{

	}

}