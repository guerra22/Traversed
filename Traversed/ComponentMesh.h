#ifndef _ComponentMesh_H
#define _ComponentMesh_H

#include "Module.h"
#include "GameObject.h"
#include "ModuleFBXLoader.h"
#include <string>

class GameObject;
class FBXLoader;

class ComponentMesh : public Component
{
public:
	ComponentMesh(Application* app, GameObject* owner);
	~ComponentMesh();

	update_status Update(float dt) override;
	bool CleanUp() override;

public:
	ModuleFBXLoader* GetMesh() const;
	void SetMesh(VertexData mesh);

	VertexData GetMesh();

	VertexData mesh;

	const char* meshPath;
};


#endif