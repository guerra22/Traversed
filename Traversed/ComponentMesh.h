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
	ComponentMesh(GameObject* owner, std::string uuid);
	~ComponentMesh() override;

	void Update() override;

	void UpdateGUI() override;

	nlohmann::ordered_json SaveUnique(nlohmann::JsonData data) override;
	void Load(nlohmann::json data) override;

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