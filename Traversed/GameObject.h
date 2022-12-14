#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Globals.h"

#include "Component.h"

#include <vector>
#include <map>
#include <typeinfo>

class ComponentMesh;

class GameObject
{
public:
	GameObject(std::string name = "Spatial Node", bool spatial = true);
	~GameObject();

	void Init();

	void Update();

	void UpdateCompMenuGUI();

	Component* CreateComponent(CO_TYPE type);
	void DeleteComponent(CO_TYPE type);

	std::vector<GameObject*> GetChildrens();

	Component* GetComponent(CO_TYPE type);
	Component* GetComponentInChildren(CO_TYPE type);

	template <class T>
	std::vector<T*> GetComponentsInChildrens(CO_TYPE type)
	{
		std::vector<T*> toReturn;

		for (int i = 0; i < children.size(); ++i)
		{
			T* aux = children[i]->GetComponent<T>(type);

			if (aux != nullptr) toReturn.emplace_back(aux);
		}

		return toReturn;
	}

	template <class T>
	T* GetComponent(CO_TYPE type)
	{
		if (components.count(type)) return (T*)components[type];
		else return nullptr;
	}

	void AddChildren(GameObject* go);
	void RemoveChildren(GameObject* go);
	void SetParent(GameObject* go);

	bool HasChildren() { return (children.size() != 0) ? true : false; }

	void DeleteGameObject();

	std::string GetUUName();

	nlohmann::ordered_json Save();
	void Load(nlohmann::JsonData data);

public:
	std::string name;
	std::string uuid;
	bool selected;

	std::map<CO_TYPE, Component*> components;

	std::vector<GameObject*> children;

	GameObject* parent = nullptr;

private:

	bool CheckParentsOfParent(GameObject* go, GameObject* checkGO);

	//Operator
	bool operator==(GameObject& other) const
	{
		if (this == &other) return true; //This is the pointer for 
		else return false;
	}
};

#endif


