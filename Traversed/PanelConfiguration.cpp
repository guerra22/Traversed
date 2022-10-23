#include "Application.h"
#include "PanelConfiguration.h"
#include "ImGuiUtils.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleHardware.h"
#include "ModuleRenderer3D.h"


PanelConfiguration::PanelConfiguration(Application* app) : UiPanel(app), fps_log(FPS_LOG_SIZE), ms_log(FPS_LOG_SIZE)
{
	active = true;
	screenHeight = app->window->screen_surface->h;
	screenWidth = app->window->screen_surface->w;
	screenBrightness = 1.0f;
}

PanelConfiguration::~PanelConfiguration()
{
	
}

void PanelConfiguration::Draw()
{
	ImGui::Begin("Configuration", &active);
	{
		if (ImGui::CollapsingHeader("Application", ImGuiTreeNodeFlags_DefaultOpen))
		{
			/*static char app_name[120];
			strcpy_s(app_name, 120, App->GetAppName());
			if (ImGui::InputText("App Name", app_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
				App->SetAppName(app_name);

			static char org_name[120];
			strcpy_s(org_name, 120, App->GetOrganizationName());
			if (ImGui::InputText("Organization", org_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
				App->SetOrganizationName(org_name);*/

			int max_fps = App->GetFramerateLimit();
			if (ImGui::SliderInt("Max FPS", &max_fps, 0, 120))
				App->SetFramerateLimit(max_fps);

			ImGui::Text("Limit Framerate:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "%i", App->GetFramerateLimit());

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
		}

		if (ImGui::CollapsingHeader("Window", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Checkbox("Vsync", &Vsync))
			{
				App->window->Vsync(Vsync);
			}
			if (ImGui::Checkbox("Fullscreen", &fullscreen))
			{
				App->window->SetFullscreen(fullscreen);
			}
			if (ImGui::SliderFloat("Brightness", &screenBrightness, 0.0001f, 1.0001f))
			{
				App->window->SetBrightness(screenBrightness);
			}
			if (ImGui::SliderInt("Width", &screenWidth, 800, 1920))
			{
				App->window->SetWidth(screenWidth);
			}
			if (ImGui::SliderInt("Height", &screenHeight, 600, 1080))
			{
				App->window->SetHeight(screenHeight);
			}
		}

		if (ImGui::CollapsingHeader("Render", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Checkbox("GL_Depth_test", &App->renderer3D->atributes.Depth_test))
			{

			}
			if (ImGui::Checkbox("GL_Cull_face", &App->renderer3D->atributes.Cull_Face))
			{

			}
			if (ImGui::Checkbox("GL_Lightning", &App->renderer3D->atributes.Lightning))
			{

			}
			if (ImGui::Checkbox("GL_Front", &App->renderer3D->atributes.Front))
			{

			}
			if (ImGui::Checkbox("GL_AmbientOclussion", &App->renderer3D->atributes.AmbientOclussion))
			{

			}
			if (ImGui::Checkbox("GL_Color_material", &App->renderer3D->atributes.Color_Materials))
			{

			}
			if (ImGui::Checkbox("Wireframe Mode", &App->renderer3D->atributes.Wireframe))
			{

			}
		}

		if (ImGui::CollapsingHeader("Input", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::TextWrapped("\tMouse Input\t");

			ImGui::TextWrapped("Mouse Position: x = "); ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%d", App->input->GetMouseX()); ImGui::SameLine();
			ImGui::TextWrapped(" y = "); ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%d", App->input->GetMouseY());
		}

		if (ImGui::CollapsingHeader("Hardware", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ModuleHardware::hw_info info = App->hardware->GetInfo(); 
			IMGUI_PRINT("SDL Version:", info.sdl_version);

			ImGui::Separator();
			IMGUI_PRINT("CPUs:", "%u (Cache: %ukb)", info.cpu_count, info.l1_cachekb);
			IMGUI_PRINT("System RAM:", "%.1fGb", info.ram_gb);
			IMGUI_PRINT("Caps:", "%s%s%s%s%s%s",
				info.rdtsc ? "RDTSC," : "",
				info.altivec ? "AltiVec," : "",
				info.mmx ? "MMX," : "",
				info.now3d ? "3DNow," : "",
				info.sse ? "SSE," : "",
				info.sse2 ? "SSE2," : "");
			IMGUI_PRINT("", "%s%s%s%s%s",
				info.sse3 ? "SSE3," : "",
				info.sse41 ? "SSE41," : "",
				info.sse42 ? "SSE42," : "",
				info.avx ? "AVX," : "",
				info.avx2 ? "AVX2" : "");


			ImGui::Separator();
			IMGUI_PRINT("GPU:", "vendor %u device %u", info.gpu_vendor, info.gpu_device);
			IMGUI_PRINT("Brand:", info.gpu_brand);
			IMGUI_PRINT("VRAM Budget:", "%.1f Mb", info.vram_mb_budget);
			IMGUI_PRINT("VRAM Usage:", "%.1f Mb", info.vram_mb_usage);
			IMGUI_PRINT("VRAM Available:", "%.1f Mb", info.vram_mb_available);
			IMGUI_PRINT("VRAM Reserved:", "%.1f Mb", info.vram_mb_reserved);
		}
	}
	ImGui::End();

}

void PanelConfiguration::AddFPS(float fps, float ms)
{
	static uint count = 0;

	if (count == FPS_LOG_SIZE)
	{
		for (uint i = 0; i < FPS_LOG_SIZE - 1; ++i)
		{
			fps_log[i] = fps_log[i + 1];
			ms_log[i] = ms_log[i + 1];
		}
	}
	else
		++count;

	fps_log[count - 1] = fps;
	ms_log[count - 1] = ms;
}