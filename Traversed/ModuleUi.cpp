#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"

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
    LOG("Loading start UI")

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

    return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

    return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
    
    return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	ImGui::ShowDemoWindow();
	ImGui::Begin("Traversed");
	ImGui::SetWindowSize({ 250,250 }, 0);
	ImGui::Text("First Window");
	if (ImGui::Button("TEST", { 100,50 }))
	{
		exit(0);
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}


bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

    return true;
}