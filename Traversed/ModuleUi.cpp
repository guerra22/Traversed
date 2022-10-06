#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleUI.h"

#include "lib\SDL\include\SDL_opengl.h"
#include "lib\Imgui\backends\imgui_impl_opengl3.h"
#include "lib\Imgui\backends\imgui_impl_sdl.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
    LOG("Loading start UI")
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init("version #420");

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    return true;
}
update_status ModuleUI::Update(float dt)
{
    ImGui::Begin("WindowTest");
    return UPDATE_CONTINUE;
}
update_status ModuleUI::PostUpdate(float dt)
{
   
    return UPDATE_CONTINUE;
}


bool ModuleUI::CleanUp()
{
    ImGui::End();

    return true;
}