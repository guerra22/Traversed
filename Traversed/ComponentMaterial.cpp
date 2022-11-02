#include "Globals.h"
#include "ComponentMaterial.h"
#include "ModuleFBXLoader.h"

ComponentMaterial::ComponentMaterial(Application* app, GameObject* owner) : Component(app, owner, COMPONENT_TYPES::MATERIAL, "Material"),
materialUsed(nullptr),
defaultTexture(false)
{

}

ComponentMaterial::~ComponentMaterial()
{

}

update_status ComponentMaterial::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ComponentMaterial::CleanUp()
{
	bool ret = true;

	textures.clear();

	return ret;
}

Texture* ComponentMaterial::GetTexture()
{
	return materialUsed;
}

void ComponentMaterial::SetTexture(Texture* texture)
{
	materialUsed = texture;
}
