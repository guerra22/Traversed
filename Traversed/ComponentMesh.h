#ifndef _COMPONENTMESH_H
#define _COMPONENTMESH_H

#pragma once
#include "Component.h"

#include "MeshRenderer.h"
#include "External/MathGeo/include/Geometry/OBB.h"

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
	void LoadUnique(nlohmann::JsonData data) override;

	void Render(Shader* shader, Shader* debugShader, Camera* camera, bool game);

	MeshRenderer* GetMesh();
	void SetMesh(MeshRenderer* mesh);

	OBB& GetOBB() { return obb; }
	AABB& GetAABB() { return aabb; }

private:
	void SetNormalsString();

private:
	MeshRenderer* mesh = nullptr;

	OBB obb;
	AABB aabb;

	CameraProperties* camInstance = nullptr;

	Debug_Normals normals;
	std::string normalsString;

	float normalsMagnitude;
};


#endif