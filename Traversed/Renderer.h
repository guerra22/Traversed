#pragma once

#include "External/MathGeo/include/Math/float2.h"
#include "External/MathGeo/include/Math/float4x4.h"
#include "External/MathGeo/include/Geometry/AABB.h"
#include <queue>

#define DEBUG_VERTEX_SHADER "Shader/debug.vs"
#define DEBUG_FRAGMENT_SHADER "Shader/debug.fs"

#define BASE_VERTEX_SHADER "Shader/base.vs"
#define BASE_FRAGMENT_SHADER "Shader/base.fs"

class FrameBuffer;
class ComponentMesh;
class MeshRenderer;

class Shader;
class Camera;

struct DebugMesh
{
	DebugMesh(MeshRenderer* mesh, float4x4 model)
	{
		this->mesh = mesh;
		this->model = model;
	}
	MeshRenderer* mesh;
	float4x4 model;
};

class Renderer
{
public:
	Renderer() {};
	Renderer(float2 size, Camera* camera);
	~Renderer();

	void Init();
	void Start();
	void CleanUp();

	void Render(bool game = true);
	void Resize(float2 size);

	FrameBuffer* GetFrameBufffer() { return frameBuffer; }

	void QueueMesh(ComponentMesh* mesh);
	void QueueDebug(DebugMesh* mesh);

public:
	float2 size = { 0, 0 };

	int numOfMeshes = 0;
private:
	void PreUpdate();
	void Update(bool game);
	void PostUpdate();

	//std::vector<MeshRenderer*> meshes;
	std::queue<ComponentMesh*> meshes;

	std::queue<DebugMesh*> debugMeshes;

private:
	Camera* owner;
	FrameBuffer* frameBuffer = nullptr;

	Shader* baseShader = nullptr;
	Shader* debugShader = nullptr;
};

