#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Module.h"
#include "GameObject.h"
#include <string>

class Application;
class GameObject;

enum class COMPONENT_TYPES
{
	NONE,
	TRANSFORM,
	MESH,
	MATERIAL,
	UNKNOWN = -1
};

class Component : public Module
{
public:
	Component(Application* app, GameObject* owner, COMPONENT_TYPES type, const char* name, bool is_active = true);
	~Component();

	update_status Update(float dt) override;
	bool CleanUp() override;

public:
	const char* GetName() const;
	void			SetName(const char* new_name);

	bool			IsActive() const;
	void			SetIsActive(const bool& is_active);

public:
	COMPONENT_TYPES	type;

	GameObject* owner = nullptr;
private:
	const char* name;
	bool is_active;
};

#endif