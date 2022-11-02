#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Module.h"
#include "Component.h"
#include <vector>
#include <map>
#include <string>

typedef unsigned int uint;
class Aplication;
class Component;
enum class COMPONENT_TYPES;

class GameObject
{
public:

	GameObject(Application* app, uint id, std::string name, bool isActive, bool isStatic);

	// Destructor
	virtual ~GameObject();

	bool Update(float dt);
	void Render();
	bool CleanUp();
	bool IsActive();
	void SetActive(bool state);
	bool IsStatic();
	void SetStatic(bool state);
	bool IsSelected();

	void SelectItem();

	bool AddChild(GameObject* child);
	bool DeleteChild(GameObject* child);

	std::string GetName();
	std::string GetMeshPath();
	std::string GetTexturePath();
	void SetName(const char* newName);
	Component* GetComponent(COMPONENT_TYPES type);
	Component* CreateComponent(COMPONENT_TYPES type);

public:

	std::vector<Component*>	components;
	std::vector<GameObject*>	childs;

	GameObject* parent;

	Application* App = nullptr;
private:

	uint id;
	std::string name;
	bool is_active;
	bool is_static;
	bool selectedForInspector = false;
};

#endif


