#ifndef _COMPONENTMESH_H
#define _COMPONENTMESH_H

#pragma once
#include "Component.h"

#include "MeshRenderer.h"

struct CameraProperties;

class Shader;
class Camera;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* owner);
	~ComponentMesh() override;

	void Update() override;

	void UpdateGUI() override;

	void Render(Shader* shader, Shader* debugShader, Camera* camera);

	MeshRenderer* GetMesh();
	void SetMesh(MeshRenderer* mesh);

private:
	MeshRenderer* mesh = nullptr;

	CameraProperties* camInstance = nullptr;

	bool displayNormals;
	bool faceNormals;

	float normalsMagnitude;
};


#endif