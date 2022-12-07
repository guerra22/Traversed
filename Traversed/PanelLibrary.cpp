#include "PanelLibrary.h"
#include "ModuleFileSystem.h"
#include "LibraryFolder.h"

PanelLibrary::PanelLibrary(bool enabled) : UiPanel(enabled)
{
	name = "Library";
}

PanelLibrary::~PanelLibrary()
{

}

void PanelLibrary::Start()
{
	fsIntance = FileSystemProperties::Instance();

	currentFolder = fsIntance->rootFolder;
}

void PanelLibrary::Update()
{
	if (ImGui::Begin(name.c_str()))
	{
		Hierarchy();
		BoxView();
	}
	ImGui::End();
}

void PanelLibrary::Hierarchy()
{
	if (ImGui::BeginChild("Library##Hierarchy", ImVec2(0, 0), true))
	{
		for (int i = 0; i < currentFolder->children.size(); ++i)
		{
			ImGui::Text(currentFolder->children[i]->name.c_str());
		}
	}
	ImGui::EndChild();
}

void PanelLibrary::BoxView()
{
	if (ImGui::BeginChild("Library##BoxView"))
	{
		for (int i = 0; i < currentFolder->children.size(); ++i)
		{
			ImGui::Text(currentFolder->children[i]->name.c_str());
		}
	}
	ImGui::EndChild();
}