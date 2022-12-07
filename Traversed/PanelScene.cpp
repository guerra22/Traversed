#include "PanelScene.h"
#include "ModuleCamera3D.h"
#include "FrameBuffer.h"

#include "External/MathGeo/include/Math/float2.h"
#include "External/ImGui/imgui_internal.h"

PanelScene::PanelScene(bool enabled) : UiPanel(enabled)
{
	name = "Scene";
	segmentSize = { 0, 0 };

	camInstance = CameraProperties::Instance();
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
	}
	ImGui::End();
}

void PanelScene::RenderSpace()
{
	float aux = (ImGui::GetWindowHeight() + 20 - segmentSize.y) * 0.5f;

	ImGui::SetCursorPosY(aux);
	ImTextureID texID = (ImTextureID)camInstance->editorCamera.renderer->GetFrameBufffer()->GetTextureBuffer();
	ImGui::Image(texID, segmentSize, ImVec2(0, 1), ImVec2(1, 0));
}