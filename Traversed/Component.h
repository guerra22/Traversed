#ifndef _COMPONENT_H
#define _COMPONENT_H

#pragma once

#include "JsonUtils.h"

enum CO_TYPE
{
	NONE,
	TRANSFORM,
	MESH,
	MATERIAL,
	CAMERA,
	LAST
};

inline const char* CompTypeToString(CO_TYPE type)
{
	switch (type)
	{
	    case TRANSFORM:   return "Transform";
	    case MESH:   return "Mesh";
	    case MATERIAL: return "Material";
	    case CAMERA: return "Camera";
	}
}

class GameObject;

class Component
{
public:
	Component(GameObject* owner, std::string uuid);
	virtual ~Component();

	virtual void Init();
	virtual void Update();

	virtual void UpdateGUI();

	void Enable();
	void Disable();

	nlohmann::ordered_json Save();
	void Load(nlohmann::JsonData data);

protected:
	virtual nlohmann::ordered_json SaveUnique(nlohmann::JsonData data);
	virtual void LoadUnique(nlohmann::JsonData data);

public:
	std::string uuid;
	CO_TYPE type;
	bool active;
	bool deleteQueue;

	GameObject* owner = nullptr;
};


#endif