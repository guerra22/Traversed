#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"

GameObject::GameObject(Application* app, uint id, std::string name, bool isActive, bool isStatic) : id(id), name(name), is_active(isActive), is_static(isStatic)
{
	this->App = app;
	name = "GameObject";
	CreateComponent(COMPONENT_TYPES::MESH);
	CreateComponent(COMPONENT_TYPES::MATERIAL);
	CreateComponent(COMPONENT_TYPES::TRANSFORM);
}

// Destructor
GameObject::~GameObject()
{

}
bool GameObject::Update(float dt)
{
	for (uint i = 0; i < components.size(); ++i)
	{
		if (components[i]->IsActive())
		{
			components[i]->Update(dt);
		}
	}
	return true;
}

// Called before quitting
bool GameObject::CleanUp()
{
	return true;
}

void GameObject::Render()
{
	for (int i = 0; i < App->sceneintro->game_objects.size(); i++)
	{
		App->renderer3D->DrawGameObjects(*App->sceneintro->game_objects.at(i));
		GameObject* owner = App->sceneintro->game_objects.at(i);
		for (int j = 0; j < owner->childs.size(); j++)
		{
			App->renderer3D->DrawGameObjects(*owner->childs.at(j));
		}
	}

}

Component* GameObject::CreateComponent(COMPONENT_TYPES type)
{
	Component* component = nullptr;

	bool findDuplicates = false;

	switch (type)
	{
	case COMPONENT_TYPES::TRANSFORM:
		component = new ComponentTransform(this->App, this);
		findDuplicates = true;
		break;

	case COMPONENT_TYPES::MESH:
		component = new ComponentMesh(this->App, this);
		findDuplicates = true;
		break;

	case COMPONENT_TYPES::MATERIAL:
		component = new ComponentMaterial(this->App, this);
		findDuplicates = true;
		break;

	}

	if (component != nullptr)
	{
		if (findDuplicates)
		{
			for (uint i = 0; i < components.size(); ++i)
			{
				if (type == components[i]->type)
				{
					LOGGING("[ERROR] %s Component could not be added to %s: No duplicates allowed!", component->GetName(), name.c_str());

					delete component;
					component = nullptr;

					return nullptr;
				}
			}
		}
		components.push_back(component);
	}

	return component;
}

Component* GameObject::GetComponent(COMPONENT_TYPES type)
{
	for (uint i = 0; i < components.size(); ++i)
	{
		if (components[i]->type == type)
		{
			return components[i];
		}
	}

	return nullptr;
}
bool GameObject::IsActive()
{
	return is_active;
}
void GameObject::SetActive(bool state)
{
	is_active = state;

	for (int j = 0; j < childs.size(); j++)
	{
		childs[j]->SetActive(state);
	}
}
bool GameObject::IsStatic()
{
	return is_static;
}

void GameObject::SetStatic(bool state)
{
	is_static = state;
}

std::string GameObject::GetName()
{
	return name;
}

void GameObject::SetName(const char* newName)
{
	name = newName;
}

bool GameObject::IsSelected()
{
	return selectedForInspector;
}

void GameObject::SelectItem()
{
	for (int i = 0; i < App->sceneintro->game_objects.size(); i++)
	{
		if (App->sceneintro->game_objects.at(i)->IsActive() && this != App->sceneintro->game_objects.at(i))
		{
			App->sceneintro->game_objects.at(i)->selectedForInspector = false;
		}
	}
	selectedForInspector = !selectedForInspector;
}

bool GameObject::AddChild(GameObject* child)
{
	child->parent = this;

	childs.push_back(child);

	return true;
}

bool GameObject::DeleteChild(GameObject* child)
{
	bool ret = false;

	for (uint i = 0; i < childs.size(); ++i)
	{
		if (childs[i] == child)
		{
			childs.erase(childs.begin() + i);
			ret = true;
			break;
		}
	}

	return ret;
}

std::string GameObject::GetMeshPath()
{
	for (int i = 0; i < App->sceneintro->game_objects.size(); i++)
	{
		if (App->sceneintro->game_objects[i]->IsSelected())
		{
			ComponentMesh* meshUsed = (ComponentMesh*)App->sceneintro->game_objects[i]->GetComponent(COMPONENT_TYPES::MESH);

			return meshUsed->meshPath;
		}
	}
}

std::string GameObject::GetTexturePath()
{
	for (int i = 0; i < App->sceneintro->game_objects.size(); i++)
	{
		if (App->sceneintro->game_objects[i]->IsSelected())
		{
			ComponentMaterial* materialUsed = (ComponentMaterial*)App->sceneintro->game_objects[i]->GetComponent(COMPONENT_TYPES::MATERIAL);

			return materialUsed->materialUsed->path;
		}
	}
}

