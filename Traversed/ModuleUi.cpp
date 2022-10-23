#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleUI.h"
#include "panelConfiguration.h"

#include "External/Glew/include/glew.h"
#include "External/Imgui/imgui.h"
#include "External/Imgui/imgui_impl_sdl.h"
#include "External/Imgui/imgui_impl_opengl2.h"

#pragma comment (lib, "External/Glew/lib/glew32.lib")

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Ui";
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

	panels.push_back(about = new PanelAbout(this->App));
	panels.push_back(configuration = new PanelConfiguration(this->App));

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
	//ImGui::ShowDemoWindow();

	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

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
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New ...");

			if (ImGui::MenuItem("Load ..."))
			{
				App->LoadConfigRequest();
			}
			if (ImGui::MenuItem("Save ..."))
			{
				App->SaveConfigRequest();
			}

			if (ImGui::MenuItem("Quit", "ESC"))
			{
				exit(0);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Configuration"))
			{
				configuration->active = true;
			}

			if (ImGui::MenuItem("About"))
			{
				about->active = true;
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("test"))
		{
			if (ImGui::Checkbox("CreateTestCube", &testCube))
			{

			}
			ImGui::EndMenu();

		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/guerra22/Traversed");

			if (ImGui::MenuItem("Download latest"))
				App->RequestBrowser("https://github.com/guerra22/Traversed");

			if (ImGui::MenuItem("Report a bug"))
				App->RequestBrowser("https://github.com/guerra22/Traversed/issues");

			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}

void ModuleUI::LogFPS(float fps, float ms)
{
	if (configuration != nullptr)
		configuration->AddFPS(fps, ms);
}