#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleUI.h"
#include "PanelAbout.h"

#include "External/Glew/include/glew.h"
#include "External/Imgui/imgui.h"
#include "External/Imgui/imgui_impl_sdl.h"
#include "External/Imgui/imgui_impl_opengl2.h"

#pragma comment (lib, "External/Glew/lib/glew32.lib")

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "ui";
}

// Destructor
ModuleUI::~ModuleUI()
{}

bool ModuleUI::Init()
{
	screenHeight = App->window->screen_surface->h;
	screenWidth = App->window->screen_surface->w;
	screenBrightness = 1.0f;

    LOGGING("Loading start UI")

	//IMGUI start
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.BackendFlags 
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL2_Init();

	panels.push_back(about = new PanelAbout());

    return true;
}

update_status ModuleUI::PreUpdate(float dt)
{

    return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	MainMenu();

	for (std::vector<UiPanel*>::iterator it = panels.begin(); it != panels.end(); ++it)
	{
		if ((*it)->IsActive())
		{
			(*it)->Draw();
		}
	}

	ImGui::Render();
	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{

    return UPDATE_CONTINUE;
}


bool ModuleUI::CleanUp()
{
	for (int i = 0; i < panels.size(); i++)
	{
		panels[i]->CleanUp();
		delete panels[i];
	}
	panels.clear();

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

    return true;
}

void ModuleUI::MainMenu()
{
	//MENUS 
	ImGui::BeginMainMenuBar();
	{
		if (ImGui::BeginMenu("GeneralStuff"))
		{
			if (ImGui::Checkbox("AboutUi", &enableAboutPanel))
			{
				about->active = enableAboutPanel;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Configuration"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
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

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("File System"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Input"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Hardware"))
		{
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}