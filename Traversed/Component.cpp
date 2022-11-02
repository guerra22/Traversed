#include "Globals.h"
#include "Application.h"
#include "Component.h"


Component::Component(Application* app, GameObject* owner, COMPONENT_TYPES type, const char* name, bool is_active) : Module(app),
type(type),
owner(owner),
name(name),
is_active(is_active)
{

}

Component::~Component()
{

}

update_status Component::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool Component::CleanUp()
{
	bool ret = true;

	return ret;
}

const char* Component::GetName() const
{
	return name;
}

void Component::SetName(const char* new_name)
{
	name = new_name;
}

bool Component::IsActive() const
{
	return is_active;
}

void Component::SetIsActive(const bool& set_to)
{
	is_active = set_to;

	for (int j = 0; j < owner->childs.size(); j++)
	{
		for (int i = 0; i < owner->components.size(); i++)
		{
			owner->childs[j]->components[i]->SetIsActive(owner->components[i]->IsActive());
		}
	}
}