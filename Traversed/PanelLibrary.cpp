#include "PanelLibrary.h"
#include "ModuleSceneintro.h"
#include "ModuleFileSystem.h"
#include "ModuleResources.h"
#include "LibraryFolder.h"
#include "LibraryManager.h"
#include "ResourceModel.h"
#include "MeshImporter.h"
#include "MeshRenderer.h"

#include "ImGuiUtils.h"
#include "External/ImGui/imgui_internal.h"

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
	sInstance = SceneProperties::Instance();
	resInstance = ResourceProperties::Instance();

	currentFolder = fsIntance->rootFolder;
	fsIntance->currentFolder = currentFolder;
	//Checks firsts when the app loads 
	//resInstance->requestFolderFileCheck = true;

	leftWin = 0;
	rightWin = 0;
}

void PanelLibrary::Update()
{
	if (ImGui::Begin(name.c_str()))
	{
		ImVec2 winSize = ImGui::GetContentRegionAvail();
		leftWin = 150;
		rightWin = winSize.x - 150;

		ImGui::DrawSplitter(0, 10, &leftWin, &rightWin, 150, 200);

		if (leftWin > 0.0f)
		{
			Hierarchy();
		}

		ImGui::SameLine();

		if (rightWin > 0.0f)
		{
			BoxView();
		}
	}
	ImGui::End();

	fsIntance->currentFolder = currentFolder;
}

void PanelLibrary::Hierarchy()
{
	if (ImGui::BeginChild("Library##Hierarchy", ImVec2(leftWin, 0), true))
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
	static float padding = 8.0f;
	static float itemSize = 64;
	float cellSize = itemSize + padding;

	if (ImGui::BeginChild("Library##BoxView", ImVec2(rightWin, 0), true))
	{
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / (cellSize + padding * 2));

		if (columnCount <= 0) columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		//Go to previous folder topping the root Library folder
		if (currentFolder != fsIntance->rootFolder)
		{
			if (ImGui::Button("<--", { cellSize, cellSize })) currentFolder = currentFolder->parent;
			ImGui::NextColumn();
		}

		//Iterate folders
		for (int i = 0; i < currentFolder->children.size(); ++i)
		{
			//if (currentFolder->children[i]->name == "Primitives") continue;
			if (ImGui::Button(currentFolder->children[i]->name.c_str(), { cellSize, cellSize }))
			{
				LibraryManager::FolderSystemUpdate(currentFolder->children[i]);
				resInstance->requestFolderFileCheck = true;
				currentFolder = currentFolder->children[i];
			}
			else ImGui::Text(currentFolder->children[i]->name.c_str());
			ImGui::NextColumn();
		}

		//Iterate files
		for (int k = 0; k < currentFolder->libItem.size(); ++k)
		{
			ImGui::PushID(k);
			if (ImGui::ImageButton(0, { cellSize, cellSize }))
			{
				switch (str2int(currentFolder->libItem[k]->extension.c_str()))
				{
				case str2int("dds"):
				case str2int("png"):

					break;
				default:

					break;
				}
			}
			if (ImGui::IsItemHovered())
			{ //Hover tooltip
				ImGui::SetTooltip(currentFolder->libItem[k]->name.c_str());
			}

			//POPUP MENU
			if (ImGui::BeginPopupContextItem("LibraryItemMenu", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonDefault_))
			{
				k += RightClickMenuContent(currentFolder->libItem[k]);

				ImGui::EndPopup();
			}

			//Drag
			if (ImGui::BeginDragDropSource())
			{
				ImGui::SetDragDropPayload("ContentBrowserItem", currentFolder->libItem[k], sizeof(LibraryItem));
				std::string tooltip = "Dragging ";
				tooltip += currentFolder->libItem[k]->name;
				ImGui::Text(tooltip.c_str());

				ImGui::EndDragDropSource();
			}

			ImGui::Text(currentFolder->libItem[k]->name.c_str());

			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::Columns(1);
	}
	ImGui::EndChild();
}

void PanelLibrary::ExecuteItemActive(LibraryItem* item, float cellSize)
{
	ResourceModel* res = (ResourceModel*)ResourceProperties::Instance()->resources[item->resUuid];
	for (auto const& mesh : *res->meshRendererMap)
	{
		if (mesh.second != nullptr)
		{
			ImGui::NextColumn();
			if (ImGui::Button(mesh.first.c_str(), { cellSize, cellSize }))
			{

			}
			if (ImGui::BeginDragDropSource())
			{
				if (package != nullptr) RELEASE(package);
				package = new std::string(res->GetUUID());
				package->append("/");
				package->append(mesh.first);
				ImGui::SetDragDropPayload("MeshCFF", package, sizeof(std::string));
				std::string tooltip = "Dragging ";
				tooltip += mesh.second->libPath;
				ImGui::Text(tooltip.c_str());
				ImGui::EndDragDropSource();
			}
		}
	}

}

int PanelLibrary::RightClickMenuContent(LibraryItem* item)
{
	if (ImGui::MenuItem("DELETE", 0, false))
	{
		LOG(LOG_TYPE::ATTENTION, "DELETE LIBITEM %s", item->name.c_str());

		std::map<std::string, Resource*>::iterator iterator = resInstance->resources.find(item->resUuid);
		Resource* resource = iterator->second; // Need a pointer var for RELEASE.

		LibraryManager::RemoveFile(iterator->second->GetLibraryFile());
		LibraryManager::RemoveFile(iterator->second->GetAssetsFile());
		LibraryManager::RemoveFile(item->GetMeta());

		//RELEASE(item);
		currentFolder->libItem.erase(std::find(currentFolder->libItem.begin(), currentFolder->libItem.end(), item));

		//RELEASE(iterator->second);
		resInstance->resources.erase(iterator);

		RELEASE(item);


		//The delete of resources is handled by a vector on the next iterator iterator. 
		//PlanDelete() method only tells the pointes on the components that they should nullptr themselves.
		//Component's pointer = nullptr -> End of engine iteration -> Delete of pointers from memory
		resource->PlanDelete();
		resInstance->planDeleteLib.push_back(resource);

		return -1;
	}
	return 0;
}