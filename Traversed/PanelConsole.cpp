#include "PanelConsole.h"
#include "ImGuiUtils.h"

PanelConsole::PanelConsole(Application* app) : UiPanel(app)
{
	active = true;
	scrollBottom = true;
}

PanelConsole::~PanelConsole()
{

}

void PanelConsole::Draw()
{
	ImGui::Begin("console", &active, ImGuiWindowFlags_MenuBar);
	{
		ConsoleMenu();
	}
	ImGui::End();
}

void PanelConsole::AddLog(const char* log)
{
	char* tmp = strdup(log);

	logsConsole.push_back(tmp);

	scrollBottom = true;
}

void PanelConsole::ClearLog()
{
	for (uint i = 0; i < logsConsole.size(); ++i)
	{
		free(logsConsole[i]);
	}

	logsConsole.clear();

	scrollBottom = true;
}

void PanelConsole::ConsoleMenu()
{
	ImGui::BeginMenuBar();

	if (ImGui::BeginMenu("Options"))
	{
		if (ImGui::MenuItem("Clear"))
		{
			ClearLog();
		}

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();
}