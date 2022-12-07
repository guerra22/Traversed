#include "ComponentMaterial.h"
#include "TextureImporter.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_impl_sdl.h"
#include "External/ImGui/imgui_impl_opengl3.h"

ComponentMaterial::ComponentMaterial(GameObject* owner, std::string uuid) : Component(owner, uuid)
{
	this->type = MATERIAL;

	isCheckers = false;
}

ComponentMaterial::~ComponentMaterial()
{

}

void ComponentMaterial::Init()
{
	checkersTexture = TextureImporter::checkers;
	//checkersTexture.path = "DEBUG TEXTURE(CHECKERS)";
}

void ComponentMaterial::Update()
{
	if (!active) return;
}

void ComponentMaterial::UpdateGUI()
{
	ImGui::NewLine();
	ImGui::Checkbox("Checkers Texture", &isCheckers);

	//Texture Path
	ImGui::NewLine();
	std::string txt = "Texture Path: ";
	if (this->texture.w == 0 && this->texture.h == 0 && !isCheckers) txt += "No texture loaded, using debug texture";
	else if (!isCheckers) txt += texture.path;
	else txt += checkersTexture.path;
	ImGui::Text(txt.c_str());

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

void ComponentMaterial::SetTexture(Texture texture)
{
	this->texture = texture;
}

void ComponentMaterial::SetTexture(unsigned int id, std::string path)
{
	this->texture.id = id;
	this->texture.path = path;
}

Texture ComponentMaterial::GetTexture()
{
	if (isCheckers) return this->checkersTexture;
	else if (this->texture.w == 0 && this->texture.h == 0) return this->checkersTexture;
	else return this->texture;
}

#pragma region Save/Load
nlohmann::ordered_json ComponentMaterial::SaveUnique(nlohmann::JsonData data)
{

	data.SetString("Path", texture.path);
	data.SetBool("Checkers", isCheckers);


	return data.data;
}

void ComponentMaterial::Load(nlohmann::json data)
{

}

#pragma endregion Save & Load