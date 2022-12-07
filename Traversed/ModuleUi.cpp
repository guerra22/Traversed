#include "ModuleUI.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"
#include "ModuleSceneintro.h"

#include "UiPanel.h"
#include "PanelAbout.h"
#include "PanelConfiguration.h"
#include "PanelConsole.h"
#include "PanelScene.h"
#include "PanelGame.h"
#include "PanelHierarchy.h"
#include "PanelInspector.h"
#include "PanelLibrary.h"

#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "External/Imgui/imgui_impl_sdl.h"
#include "External/Imgui/imgui_impl_opengl3.h"
#include "External/ImGuizmo/ImGuizmo.h"

#pragma region EditorProperties
EditorProperties::EditorProperties()
{

}

EditorProperties* EditorProperties::Instance()
{
	if (instance == nullptr) instance = new EditorProperties();

	return instance;
}

void EditorProperties::Delete()
{
	if (instance != nullptr)
	{
		RELEASE(instance);
	}
}

void EditorProperties::SwitchColorMode() {
	switch (colorMode)
	{
	    case COLORMODE::LightMode: ImGui::StyleColorsLight(); break;
	    case COLORMODE::DarkMode: ImGui::StyleColorsDark(); break;
	    case COLORMODE::ClassicMode: ImGui::StyleColorsClassic(); break;
	}
}

EditorProperties* EditorProperties::instance = nullptr;

#pragma endregion Editor Properties Singleton Struct

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Ui";
	eProps = EditorProperties::Instance();
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	LOG(LOG_TYPE::ENGINE, "INIT: ImGui.")

	//Flags
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.WantCaptureMouse = true;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	return true;
}

bool ModuleUI::Start()
{
	//Create Panels
	panels.emplace_back(new PanelConsole());
	panels.emplace_back(new PanelConfiguration());
	panels.emplace_back(new PanelScene());
	panels.emplace_back(new PanelGame());
	panels.emplace_back(new PanelHierarchy());
	panels.emplace_back(new PanelInspector());
	panels.emplace_back(new PanelLibrary());

	panels.emplace_back(new PanelAbout());

	//START
	for (int i = 0; i < panels.size(); ++i)
	{
		panels[i]->Start();
	}

	ImGui_ImplSDL2_InitForOpenGL(WindowProperties::Instance()->window, App->renderer3D->GetGLContext());
	ImGui_ImplOpenGL3_Init();

	return true;
}

bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//Clean Segments
	for (int i = 0; i < panels.size(); ++i)
	{
		RELEASE(panels[i]);
	}

	//Delete Editor Properties
	eProps->Delete();

	return true;
}

UpdateStatus ModuleUI::Update()
{
	DrawEditorGui();

	return UPDATE_CONTINUE;
}

UpdateStatus ModuleUI::PostUpdate()
{
	//DrawEditorGui();

	return UPDATE_CONTINUE;
}

void ModuleUI::DrawEditorGui()
{
	BeginRender();

	//Menus
	MainMenuBar();
	UpdatePanels();
	FileDialogMenu();

	//Demo
	//ImGui::ShowDemoWindow();

	EndRender();
}

#pragma region EditorRender
void ModuleUI::BeginRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();// App->window->GetSDLWindow());
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void ModuleUI::EndRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}
#pragma endregion Imgui Render methods

#pragma region GUI
void ModuleUI::MainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene"))
			{
				App->sceneintro->NewScene();
			}

			if (ImGui::MenuItem("Save Scene"))
			{
				App->sceneintro->SaveScene();
			}

			if (ImGui::MenuItem("Load Scene"))
			{
				//ImGuiFileDialog::OpenModal
				ImGuiFileDialogFlags flags = ImGuiFileDialogFlags_DisableCreateDirectoryButton;
				flags |= ImGuiFileDialogFlags_DontShowHiddenFiles;
				flags |= ImGuiFileDialogFlags_ReadOnlyFileNameField;
				ImGuiFileDialog::Instance()->OpenDialog("ChooseSceneFile", "Choose a scene file", ".sc", "", 1, nullptr, flags);
			}

			if (ImGui::MenuItem("Exit"))
			{
				App->StopEngine();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			for (int i = 0; i < (panels.size() - 1); ++i)
			{
				if (ImGui::MenuItem(panels[i]->name.c_str(), NULL, &panels[i]->enabled))
				{
					LOG(LOG_TYPE::ENGINE, "%s '%s'", panels[i]->name.c_str(), panels[i]->enabled ? "OPENED" : "CLOSED");
				}
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Visit Github", ""))
			{
				ShellExecute(0, 0, "https://github.com/guerra22/Traversed", 0, 0, SW_SHOW);
			}

			if (ImGui::MenuItem(panels[panels.size() - 1]->name.c_str(), NULL, &panels[panels.size() - 1]->enabled))
			{
				LOG(LOG_TYPE::ENGINE, "%s '%s'", panels[panels.size() - 1]->name.c_str(), panels[panels.size() - 1]->enabled ? "OPENED" : "CLOSED");
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void ModuleUI::FileDialogMenu()
{
	std::string filePath = "Library/Scenes/";

	//Display
	if (ImGuiFileDialog::Instance()->Display("ChooseSceneFile", 32, ImVec2({ 400, 400 })))
	{
		//On ok.
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			filePath += ImGuiFileDialog::Instance()->GetCurrentFileName();

			App->sceneintro->LoadScene(filePath);
		}

		ImGuiFileDialog::Instance()->Close();
	}

}

void ModuleUI::UpdatePanels()
{
	for (int i = 0; i < panels.size(); ++i)
	{
		if (panels[i]->enabled)
		{
			panels[i]->Update();
		}
	}
}

#pragma endregion Gui Elements of the editor

#pragma region Save/Load Settings

void ModuleUI::LoadSettingsData(pugi::xml_node& load)
{
	for (int i = 0; i < panels.size(); ++i)
	{
		panels[i]->enabled = load.child(panels[i]->name.c_str()).attribute("value").as_bool();
	}
	//Editor Properties
	eProps->colorMode = (COLORMODE)load.child("ColorMode").attribute("value").as_int();
	eProps->SwitchColorMode();
}

void ModuleUI::SaveSettingsData(pugi::xml_node& save)
{
	for (int i = 0; i < panels.size(); ++i)
	{
		save.child(panels[i]->name.c_str()).attribute("value") = panels[i]->enabled;
	}
	save.child("ColorMode").attribute("value") = (int)eProps->colorMode;
}

#pragma endregion Save & Load of Settings