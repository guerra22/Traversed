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
#include "PanelShaderText.h"

#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "External/Imgui/imgui_impl_sdl.h"
#include "External/Imgui/imgui_impl_opengl3.h"
#include "External/ImGuizmo/ImGuizmo.h"

#pragma region EditorProperties
EditorProperties::EditorProperties()
{
	requestShaderTextUuid = "NULL";
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
		case COLORMODE::CustomizeMode: SetupImGuiStyle(); break;
	}
}

void EditorProperties::RequestShaderTextSwitch(std::string shaderResourceUuid)
{
	requestShaderTextSwitch = true;
	requestShaderTextUuid = shaderResourceUuid;
}

void EditorProperties::ForceClose()
{
	requestShaderTextSwitch = true;
}

void EditorProperties::SetupImGuiStyle()
{
	// Green Font style by aiekick from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 0.9399999976158142f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.6000000238418579f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.5686274766921997f, 0.5686274766921997f, 0.5686274766921997f, 0.699999988079071f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.7568627595901489f, 0.7568627595901489f, 0.7568627595901489f, 0.800000011920929f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.6000000238418579f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.5490196347236633f, 0.800000011920929f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.7490196228027344f, 0.800000011920929f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 1.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.5490196347236633f, 0.4000000059604645f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.7490196228027344f, 0.6000000238418579f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 1.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.5490196347236633f, 0.4000000059604645f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.7490196228027344f, 0.6000000238418579f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 1.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.5490196347236633f, 0.4000000059604645f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.7490196228027344f, 0.6000000238418579f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 1.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.5490196347236633f, 0.4000000059604645f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.7490196228027344f, 0.6000000238418579f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 1.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.5490196347236633f, 0.800000011920929f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 0.7490196228027344f, 0.800000011920929f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.1294117718935013f, 0.7490196228027344f, 1.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1764705926179886f, 0.1764705926179886f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3568627536296844f, 0.3568627536296844f, 0.3568627536296844f, 0.5400000214576721f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.07000000029802322f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}
EditorProperties* EditorProperties::instance = nullptr;

#pragma endregion Editor Properties Singleton Struct

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Editor";
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
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

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
	panelViewPoolOff = 1;

	//Create Panels
	panels.emplace_back(new PanelConsole());
	panels.emplace_back(new PanelConfiguration());
	panels.emplace_back(new PanelGame());
	panels.emplace_back(new PanelScene());
	panels.emplace_back(new PanelHierarchy());
	panels.emplace_back(new PanelInspector());
	panels.emplace_back(new PanelLibrary());

	panels.emplace_back(new PanelAbout());

	//START
	for (int i = 0; i < panels.size(); ++i)
	{
		panels[i]->Start();
	}

	//Start Special segments
	panelShaderText = new PanelShaderText();
	panelShaderText->Start();

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

	RELEASE(panelShaderText);

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
	RequestSwitchHandler();
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
			for (int i = 0; i < (panels.size() - panelViewPoolOff); ++i)
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

void ModuleUI::RequestSwitchHandler()
{
	if (eProps->GetShaderTextRequest())
	{
		panelShaderText->enabled = !panelShaderText->enabled;

		if (panelShaderText->enabled) panelShaderText->SetResource(eProps->GetShaderTextRequestUuid());
	}
}

void ModuleUI::UpdatePanels()
{
	//Main acces Panels
	for (int i = 0; i < panels.size(); ++i)
	{
		if (panels[i]->enabled)
		{
			panels[i]->Update();
		}
	}

	//Special Segments
	if (panelShaderText->enabled)
	{
		panelShaderText->Update();
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