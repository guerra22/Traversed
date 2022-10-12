#include "Application.h"
#include "PanelConfiguration.h"
#include "ImGuiUtils.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"


PanelConfiguration::PanelConfiguration(Application* app) : UiPanel(app)
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
		/*if (ImGui::CollapsingHeader("Application", ImGuiTreeNodeFlags_DefaultOpen))
		{
			static char app_name[120];
			strcpy_s(app_name, 120, App->GetAppName());
			if (ImGui::InputText("App Name", app_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
				App->SetAppName(app_name);

			static char org_name[120];
			strcpy_s(org_name, 120, App->GetOrganizationName());
			if (ImGui::InputText("Organization", org_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
				App->SetOrganizationName(org_name);

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
		}*/

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

		if (ImGui::CollapsingHeader("Input", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::TextWrapped("\tMouse Input\t");

			ImGui::TextWrapped("Mouse Position: x = "); ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%d", App->input->GetMouseX()); ImGui::SameLine();
			ImGui::TextWrapped(" y = "); ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%d", App->input->GetMouseY());
		}

		/*if (ImGui::CollapsingHeader("Hardware", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::TextWrapped("CPU Count: "); ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(countCPU).c_str());

			ImGui::TextWrapped("RAM: "); ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), std::to_string(systemRAM).c_str());

			ImGui::TextWrapped("--------OpenGL-------- ");
			ImGui::TextWrapped("Vendor %s", glGetString(GL_VENDOR));
			ImGui::TextWrapped("Renderer: %s", glGetString(GL_RENDERER));
			ImGui::TextWrapped("OpenGL version supported %s", glGetString(GL_VERSION));
			ImGui::TextWrapped("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		}*/
	}
	ImGui::End();

}