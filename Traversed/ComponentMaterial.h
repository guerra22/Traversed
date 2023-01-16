#ifndef _COMPONENTMATERIAL_H
#define _COMPONENTMATERIAL_H

#include "Component.h"

class Shader;
struct ResourceProperties;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* owner, std::string uuid);
	~ComponentMaterial() override;

	void Init() override;
	void Update() override;

	void UpdateGUI() override;

	nlohmann::ordered_json SaveUnique(nlohmann::JsonData data) override;
	void LoadUnique(nlohmann::JsonData data) override;

private:
	void ShaderGUICombo();

	ResourceProperties* resInstance = nullptr;

public:
	Shader* shader = nullptr;
};


#endif