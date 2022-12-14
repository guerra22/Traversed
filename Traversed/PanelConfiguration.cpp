#include "PanelConfiguration.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleUI.h"
#include "ModuleResources.h"
#include "ResourceModel.h"
#include "ResourceTexture.h"

#include "ComponentCamera.h"
#include "GameObject.h"

#include "External/Glew/include/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "External/SDL/include/SDL.h"
#include "External/GPUDetect/DeviceId.h"

PanelConfiguration::PanelConfiguration(bool enabled) : UiPanel(enabled)
{
	name = "Configuration";

	wProps = WindowProperties::Instance();
	rProps = RenderProperties::Instance();
	eProps = EditorProperties::Instance();
	cProps = CameraProperties::Instance();
	resProps = ResourceProperties::Instance();
	time = Time::Instance();

	//GetCaps();
	vsync = rProps->vsync;

	//framerate queue
	for (int i = 0; i < 99; i++)
	{
		framerateQueue.emplace_back(0);
	}
	//miliseconds queue
	for (int i = 0; i < 99; i++)
	{
		milisecondsQueue.emplace_back(0);
	}

	GetCaps();

	VRamBudget = 0;
	VRamCurrentUsage = 0;
	VRamAvailable = 0;
	VRamReserve = 0;

	ram = SDL_GetSystemRAM();

	cpuCount = SDL_GetCPUCount();

	cache = SDL_GetCPUCacheLineSize();

	getGraphicsDeviceInfo(0, 0, 0, &VRamBudget, &VRamCurrentUsage, &VRamAvailable, &VRamReserve);
}

PanelConfiguration::~PanelConfiguration()
{

}

void PanelConfiguration::Update()
{
	io = ImGui::GetIO(); (void)io;
	if (ImGui::Begin("Configuration"))
	{
		if (ImGui::CollapsingHeader("Application")) ApplicationHeader();
		if (ImGui::CollapsingHeader("Window")) WindowHeader();
		if (ImGui::CollapsingHeader("Input")) InputHeader();
		if (ImGui::CollapsingHeader("Rendering")) RenderingHeader();
		if (ImGui::CollapsingHeader("Active Resource")) ActiveResourceHeader();
		if (ImGui::CollapsingHeader("Game")) GameHeader();
		//if (ImGui::CollapsingHeader("Editor")) EditorHeader();
		if (ImGui::CollapsingHeader("Hardware")) HardwareHeader();
	}
	ImGui::End();
}

#pragma region Configurations
void PanelConfiguration::ApplicationHeader()
{
	//Framerate
	framerateQueue.erase(framerateQueue.begin());
	framerateQueue.emplace_back(io.Framerate);
	std::string auxTxt = "Framerate: " + std::to_string((int)framerateQueue.back());
	ImGui::PlotHistogram("", &framerateQueue[0], framerateQueue.size(), 0, auxTxt.c_str(), 0, 180, ImVec2(0, 160.0f));

	//Miliseconds
	milisecondsQueue.erase(milisecondsQueue.begin());
	milisecondsQueue.emplace_back(io.DeltaTime * 1000);
	auxTxt = "Miliseconds: " + std::to_string((int)milisecondsQueue.back());
	ImGui::PlotHistogram("", &milisecondsQueue[0], milisecondsQueue.size(), 0, auxTxt.c_str(), 0, 100, ImVec2(0, 160.0f));

	//Cap Fps
	ImGui::SliderInt("Cap FPS", &time->frameCap, 1, 180);
	if (ImGui::IsItemDeactivatedAfterEdit()) LOG(LOG_TYPE::ENGINE, "Fps capped to '%i'", time->frameCap);

}

void PanelConfiguration::WindowHeader()
{
	if (ImGui::SliderFloat("Brightness", &wProps->brightness, 0.f, 1.0f))
	{
		SDL_SetWindowBrightness(wProps->window, wProps->brightness);
	}
	if (ImGui::IsItemDeactivatedAfterEdit()) LOG(LOG_TYPE::ENGINE, "Brightness set to '%.2f'", wProps->brightness);

	SDL_GetWindowSize(wProps->window, &wProps->w, &wProps->h);
	ImGui::Text("Window Size -> ( %i, %i )", wProps->w, wProps->h);

	if (ImGui::Checkbox("Fullscreen", &wProps->fullscreen))
	{
		wProps->ToggleFullscreen();
		LOG(LOG_TYPE::ENGINE, "Fullscreen '%s'", wProps->fullscreen ? "ON" : "OFF");
	}
	if (ImGui::Checkbox("Fullscreen Desktop", &wProps->fullScreenDesktop))
	{
		wProps->ToggleFullscreenDesktop();
		LOG(LOG_TYPE::ENGINE, "Fullscreen Desktop '%s'", wProps->fullScreenDesktop ? "ON" : "OFF");
	}
	if (ImGui::Checkbox("Borderless", &wProps->borderless))
	{
		wProps->ToggleBorderless();
		LOG(LOG_TYPE::ENGINE, "Borderless '%s'", wProps->borderless ? "ON" : "OFF");
	}
	if (ImGui::Checkbox("Resizable", &wProps->resizable))
	{
		wProps->ToggleResizable();
		LOG(LOG_TYPE::ENGINE, "Resizable '%s'", wProps->resizable ? "ON" : "OFF");
	}
}

void PanelConfiguration::InputHeader()
{
	if (ImGui::IsMousePosValid())
	{
		ImGui::Text("Mouse position: (%g, %g)", io.MousePos.x, io.MousePos.y);
		ImGui::Spacing();
		ImGui::Text("Mouse motion: (%g,  %g)", io.MouseDelta.x, io.MouseDelta.y);
		ImGui::Spacing();
		ImGui::Text("Mouse Wheel: %g", io.MouseWheel);
		ImGui::Spacing();
		ImGui::Text("Key: "); //ImGui::Text("Chars queue:");
		for (int i = 0; i < io.InputQueueCharacters.Size; i++)
		{
			ImWchar c = io.InputQueueCharacters[i];
			ImGui::SameLine();
			ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c);
		}
	}
}

void PanelConfiguration::RenderingHeader()
{
	if (ImGui::Checkbox("Vsync ", &rProps->vsync))
	{
		rProps->ToggleVsync();
		LOG(LOG_TYPE::ENGINE, "Vsync '%s'", rProps->vsync ? "ON" : "OFF");
	}

	if (ImGui::Checkbox("Wireframe", &rProps->wireframe))
	{
		rProps->ToggleWireframe();
		LOG(LOG_TYPE::ENGINE, "Wireframe '%s'", rProps->wireframe ? "ON" : "OFF");
	}

	if (ImGui::Checkbox("DepthTest", &rProps->depthTest))
	{
		rProps->ToggleDepthTest();
		LOG(LOG_TYPE::ENGINE, "Depth Test '%s'", rProps->depthTest ? "ON" : "OFF");
	}

	/*if (ImGui::Checkbox("Fog", &rProps->fog))
	{
		rProps->ToggleFog();
		LOG(LOG_TYPE::ENGINE, "Fog '%s'", rProps->fog ? "ON" : "OFF");
	}*/

	if (ImGui::Checkbox("Cull Face", &rProps->cullFace))
	{
		rProps->ToggleCullFace();
		LOG(LOG_TYPE::ENGINE, "Cull Face '%s'", rProps->cullFace ? "ON" : "OFF");
	}

	/*if (ImGui::Checkbox("Lighting", &rProps->lighting))
	{
		rProps->ToggleLighting();
		LOG(LOG_TYPE::ENGINE, "Lighting '%s'", rProps->lighting ? "ON" : "OFF");
	}*/

	/*if (ImGui::Checkbox("Color Material", &rProps->colorMaterial))
	{
		rProps->ToggleColorMaterial();
		LOG(LOG_TYPE::ENGINE, "Color Material '%s'", rProps->colorMaterial ? "ON" : "OFF");
	}*/

	/*if (ImGui::Checkbox("Texture 2D", &rProps->texture2D))
	{
		rProps->ToggleTexture2D();
		LOG(LOG_TYPE::ENGINE, "Texture 2D '%s'", rProps->texture2D ? "ON" : "OFF");
	}*/
}

void PanelConfiguration::EditorHeader()
{
	int aux = (int)&eProps->colorMode;
	if (ImGui::RadioButton("Customize mode", (eProps->colorMode == COLORMODE::CustomizeMode ? true : false)))
	{
		eProps->colorMode = COLORMODE::CustomizeMode;
		eProps->SwitchColorMode();
		LOG(LOG_TYPE::ENGINE, "Customize mode 'ON'");
	}
	if (ImGui::RadioButton("Light mode", (eProps->colorMode == COLORMODE::LightMode ? true : false)))
	{
		eProps->colorMode = COLORMODE::LightMode;
		eProps->SwitchColorMode();
		LOG(LOG_TYPE::ENGINE, "Light mode 'ON'");
	}
	if (ImGui::RadioButton("Dark mode", (eProps->colorMode == COLORMODE::DarkMode ? true : false)))
	{
		eProps->colorMode = COLORMODE::DarkMode;
		eProps->SwitchColorMode();
		LOG(LOG_TYPE::ENGINE, "Dark mode 'ON'");
	}
	if (ImGui::RadioButton("Classic mode", (eProps->colorMode == COLORMODE::ClassicMode ? true : false)))
	{
		eProps->colorMode = COLORMODE::ClassicMode;
		eProps->SwitchColorMode();
		LOG(LOG_TYPE::ENGINE, "Classic mode 'ON'");
	}
}

void PanelConfiguration::HardwareHeader()
{
	ImGui::Separator();
	ImGui::Text("CPU cores: %i ", cpuCount);
	ImGui::Text("System RAM: %.1f Gb", (ram / 1000.0f));
	ImGui::Text("Cache: %i Bytes", (int)cache);
	ImGui::Text("%s", strCaps.c_str());
	/*ImGui::Text("Caps: %s", strCaps);*/
	ImGui::Separator();

	ImGui::Text("GPU Vendor: %s", glGetString(GL_VENDOR));
	ImGui::Text("GPU: %s", glGetString(GL_RENDERER));

	ImGui::Text("VRam Budget: %i Mb", (int)(VRamBudget / (1024.f * 1024.f)));
	ImGui::Text("VRam Usage: %i Mb", (int)(VRamCurrentUsage / (1024.f * 1024.f)));
	ImGui::Text("VRam Available: %i Mb", (int)(VRamAvailable / (1024.f * 1024.f)));
	ImGui::Text("VRAM Reserved: %i Mb", (int)(VRamReserve / (1024.f * 1024.f)));
}

void PanelConfiguration::GameHeader()
{
	if (cProps->gameCameras.size() == 0)
	{
		ImGui::Text("There are no game objects with a Camera component.");
	}
	else
	{
		std::string aux = cProps->gameCameras.at(cProps->mainCameraId)->owner->GetUUName();
		aux += "##";
		aux += cProps->mainCameraId;

		std::string auxLabel = "Cameras: ";
		auxLabel += std::to_string(cProps->gameCameras.size());

		if (ImGui::BeginCombo(auxLabel.c_str(), aux.c_str()))
		{
			for (int i = 0; i < cProps->gameCameras.size(); ++i)
			{
				aux = cProps->gameCameras.at(i)->owner->name;
				aux += "##";
				aux += cProps->mainCameraId;

				if (ImGui::Selectable(aux.c_str()))
				{	//Sets new game camera
					cProps->gameCameras.at(cProps->mainCameraId)->isMainCamera = false;

					cProps->mainCameraId = i;
					cProps->gameCameras.at(i)->isMainCamera = true;
				}
			}

			ImGui::EndCombo();
		}
	}
}

void PanelConfiguration::ActiveResourceHeader()
{
	uint total = 0;

	ImGui::Columns(3, 0);
	for (auto const& res : resProps->resources)
	{
		if (res.second != nullptr)
		{
			if (res.second->GetType() == RESOURCE_TYPE::MODEL)
			{
				ResourceModel* model = (ResourceModel*)resProps->resources[res.first];
				if (model == nullptr) continue;

				for (auto const& m : *model->meshRendererMap)
				{
					if (m.second->referenceCount > 0)
					{
						ImGui::Text(std::to_string(m.second->referenceCount).c_str());
						ImGui::NextColumn();
						ImGui::Text(m.first.c_str());
						ImGui::NextColumn();
						ImGui::Text(m.second->libPath.c_str());
						ImGui::NextColumn();
						total++;
					}
				}
			}
			else
			{
				if (res.second->GetRC() > 0)
				{
					ImGui::Text(std::to_string(res.second->GetRC()).c_str());
					ImGui::NextColumn();
					ImGui::Text(res.first.c_str());
					ImGui::NextColumn();
					ImGui::Text(res.second->GetLibraryFile().c_str());
					ImGui::NextColumn();
					total++;
				}
			}
		}
	}
	ImGui::Columns(1);

	std::string totalText = "Total: ";
	totalText += std::to_string(total);
	ImGui::Text(totalText.c_str());
}

#pragma endregion Configuration methods

void PanelConfiguration::GetCaps()
{
	strCaps = "Caps: ";
	strCaps += SDL_HasRDTSC() ? "RDTSC " : "";
	strCaps += SDL_HasMMX() ? "MMX " : "";
	strCaps += SDL_HasSSE() ? "SSE " : "";
	strCaps += SDL_HasSSE2() ? "SSE2 " : "";
	strCaps += SDL_HasSSE3() ? "SSE3 " : "";
	strCaps += SDL_HasSSE41() ? "SSE41 " : "";
	strCaps += SDL_HasSSE42() ? "SSE42 " : "";
	strCaps += SDL_HasAVX() ? "AVX " : "";
	strCaps += SDL_HasAVX2() ? "AVX2 " : "";
	strCaps += SDL_Has3DNow() ? "3DNow " : "";
	strCaps += SDL_HasAltiVec() ? "AltiVec " : "";
}