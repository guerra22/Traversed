#ifndef _ComponentMaterial_H
#define _ComponentMaterial_H

#include "Module.h"
#include "GameObject.h"
#include <string>

class GameObject;
class Material;
class FBXLoader;

struct Texture;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(Application* app, GameObject* owner);
	~ComponentMaterial();

	update_status Update(float dt) override;
	bool CleanUp() override;

	Texture* GetTexture();

	void SetTexture(Texture* texture);


public:
	std::vector<Texture*> textures;

	bool defaultTexture;

	Texture* materialUsed;

};


#endif