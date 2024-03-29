#include "ComponentTexture.h"
#include "TextureImporter.h"
#include "ModuleResources.h"
#include "ResourceTexture.h"
#include "LibraryFolder.h"

#include "External/Glew/include/glew.h"
#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_impl_sdl.h"
#include "External/ImGui/imgui_impl_opengl3.h"

ComponentTexture::ComponentTexture(GameObject* owner, std::string uuid) : Component(owner, uuid)
{
	this->type = TEXTURE;

	isCheckers = false;

	if (TextureImporter::checkers.id == 0) TextureImporter::CheckerImage();
	checkersTexture = TextureImporter::checkers;
}

ComponentTexture::~ComponentTexture()
{
	if (!texture.resUuid.empty())
	{
		ResourceTexture* resource = (ResourceTexture*)ResourceProperties::Instance()->resources[texture.resUuid];

		if (resource != nullptr)
		{
			resource->DecreaseRC();
		}
	}
}

void ComponentTexture::Init()
{
	checkersTexture = TextureImporter::checkers;
}

void ComponentTexture::Update()
{
	if (!active) return;
}

void ComponentTexture::UpdateGUI()
{
	ImGui::NewLine();
	ImGui::Checkbox("Checkers Texture", &isCheckers);

	//Texture Path
	ImGui::NewLine();
	std::string txt = "Texture Path: ";
	if (this->texture.id == 0 && !isCheckers) txt += "No texture loaded, using debug texture";
	else if (!isCheckers) txt += this->texture.path;
	else txt += checkersTexture.path;
	ImGui::Text(txt.c_str());

	TextureDrop();

	//Texture Width and Height
	txt = "Size: ";
	if (isCheckers || (this->texture.w == 0 && this->texture.h))
	{
		txt += std::to_string(checkersTexture.w);
		txt += " x ";
		txt += std::to_string(checkersTexture.h);
	}
	else
	{
		txt += std::to_string(texture.w);
		txt += " x ";
		txt += std::to_string(texture.h);
	}
	ImGui::Text(txt.c_str());

	//Texture ID
	txt = "Texture ID: ";
	if (isCheckers || (this->texture.w == 0 && this->texture.h)) txt += std::to_string(checkersTexture.id);
	else txt += std::to_string(texture.id);
	ImGui::Text(txt.c_str());
}

void ComponentTexture::TextureDrop()
{
	ImGui::ImageButton((ImTextureID)texture.id, { 100, 100 });

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentBrowserItem"))
		{
			IM_ASSERT(payload->DataSize == sizeof(LibraryItem));
			const LibraryItem item = *static_cast<const LibraryItem*>(payload->Data);

			switch (str2int(item.extension.c_str()))
			{
			case str2int("png"):
			case str2int("PNG"):
			case str2int("DDS"):
			case str2int("dds"):
			case str2int("jpg"):
			case str2int("JPG"):

				ResourceTexture* res = (ResourceTexture*)ResourceProperties::Instance()->resources.at(item.resUuid);

				if (!texture.resUuid.empty()) //Decrease current RC
					ResourceProperties::Instance()->resources[texture.resUuid]->DecreaseRC();

				this->texture = TextureImporter::ImportFromLibrary(res);
			}
		}
	}
}

void ComponentTexture::SetTexture(Texture texture)
{
	this->texture = texture;
}

void ComponentTexture::SetTexture(unsigned int id, std::string path)
{
	this->texture.id = id;
	this->texture.path = path;
}

void ComponentTexture::SetTextureUuid(std::string uuid)
{
	this->texture.resUuid = uuid;
}

Texture ComponentTexture::GetTexture()
{
	if (!glIsTexture(this->texture.id))
	{
		this->texture = Texture();
	}

	if (isCheckers) return this->checkersTexture;
	else if (this->texture.w == 0 && this->texture.h == 0) return this->checkersTexture;
	else return this->texture;
}

#pragma region Save/Load
nlohmann::ordered_json ComponentTexture::SaveUnique(nlohmann::JsonData data)
{

	data.SetString("Path", texture.path);
	data.SetString("Texture Uuid", texture.resUuid);
	data.SetBool("Checkers", isCheckers);


	return data.data;
}

void ComponentTexture::LoadUnique(nlohmann::JsonData data)
{
	std::string texToLoad(data.GetString("Path"));
	std::string texUuid = data.GetString("Texture Uuid");

	if (!texUuid.empty())
	{
		ResourceTexture* res = nullptr;
		if (ResourceProperties::Instance()->resources.count(texUuid) == 1)
			res = (ResourceTexture*)ResourceProperties::Instance()->resources.at(texUuid);
		if (res != nullptr)
		{

			texture = TextureImporter::ImportFromLibrary(res);
		}
	}
	else
		texture = Texture();

	isCheckers = data.GetBool("Checkers");
}

#pragma endregion Save & Load