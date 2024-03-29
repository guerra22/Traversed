#include "PanelGame.h"
#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "Renderer.h"
#include "FrameBuffer.h"

PanelGame::PanelGame(bool enabled) : UiPanel(enabled)
{
	name = "Game";

	segmentSize = { 0, 0 };

	cameraID = -1;
}

PanelGame::~PanelGame()
{

}

void PanelGame::Start()
{
	camInstance = CameraProperties::Instance();
}

void PanelGame::Update()
{
	if (cameraID != camInstance->mainCameraId) LookForCamera();

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar;
	flags |= ImGuiWindowFlags_NoScrollWithMouse;

	if (ImGui::Begin(name.c_str(), 0, flags))
	{
		if (mainCamera != nullptr)
		{
			ImVec2 pos = ImGui::GetWindowPos();
			ImVec2 size = ImGui::GetWindowSize();
			size.x += pos.x;
			size.y += pos.y;

			ImVec2 aux = ImGui::GetContentRegionAvail();
			aux.y = (aux.x / 16) * 9;


			if (aux.x != segmentSize.x || aux.y != segmentSize.y)
			{
				segmentSize.x = aux.x;
				segmentSize.y = aux.y;

				Resize();
			}
		}
		RenderSpace();
	}
	ImGui::End();
}

void PanelGame::Resize()
{
	if (mainCamera->camera.renderer == nullptr)
	{
		mainCamera->camera.SetRenderer({ segmentSize.x, segmentSize.y });
		//mainCamera->camera.renderer = new Renderer({ segmentSize.x, segmentSize.y });
	}
	else
	{
		mainCamera->camera.renderer->Resize({ segmentSize.x, segmentSize.y });
	}
}

void PanelGame::LookForCamera()
{
	if (camInstance->gameCameras.size() != 0 && camInstance->mainCameraId != -1)
	{
		cameraID = camInstance->mainCameraId;
		mainCamera = camInstance->gameCameras.at(cameraID);
		Resize();
	}
	else
	{
		mainCamera = nullptr;
		cameraID = -1;
		camInstance->mainCameraId = 0;
	}
}

void PanelGame::RenderSpace()
{
	if (mainCamera != nullptr)
	{
		if (mainCamera->isMainCamera == false) mainCamera->isMainCamera = true;

		float aux = (ImGui::GetWindowHeight() + 20 - segmentSize.y) * 0.5f;
		ImGui::SetCursorPosY(aux);
		ImTextureID texID = (ImTextureID)mainCamera->camera.renderer->GetFrameBufffer()->GetTextureBuffer();
		ImGui::Image(texID, segmentSize, ImVec2(0, 1), ImVec2(1, 0));
	}
}