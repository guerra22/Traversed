#ifndef _COMPONENTMATERIAL_H
#define _COMPONENTMATERIAL_H

#include "Component.h"
#include "MeshRenderer.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* owner, std::string uuid);
	~ComponentMaterial() override;

	void Init() override;
	void Update() override;

	void UpdateGUI() override;

	Texture GetTexture();

	void SetTexture(Texture texture);
	void SetTexture(unsigned int id, std::string path);

private:
	Texture texture;
	Texture checkersTexture;

	bool isCheckers;
};


#endif