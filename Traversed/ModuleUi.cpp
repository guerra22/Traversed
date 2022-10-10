#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleUI.h"
#include "AboutUi.h"

#include "External/Glew/include/glew.h"
#include "External/Imgui/imgui.h"
#include "External/Imgui/imgui_impl_sdl.h"
#include "External/Imgui/imgui_impl_opengl2.h"

#pragma comment (lib, "External/Glew/lib/glew32.lib")

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleUI::~ModuleUI()
{}

bool ModuleUI::Init()
{
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

	menus.push_back(aboutUi = new AboutUi());

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

	for (std::vector<UiElements*>::iterator it = menus.begin(); it != menus.end(); ++it)
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
	for (int i = 0; i < menus.size(); i++)
	{
		menus[i]->CleanUp();
		delete menus[i];
	}
	menus.clear();

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
			if (ImGui::Checkbox("AboutUi", &enableAboutUi))
			{
				aboutUi->active = enableAboutUi;
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
			if (ImGui::Checkbox("Fullscreen", &fullscreen))
			{
				App->window->SetFullscreen(fullscreen);
			}
			if (ImGui::SliderInt("Width", &screenWidth, 0, 1080))
			{
				App->window->ModifyWidth(screenWidth);
			}
			if (ImGui::SliderInt("Height", &screenHeight, 0, 1920))
			{
				App->window->ModifyHeight(screenHeight);
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