#pragma once

#include "External/MathGeo/include/Math/float2.h"
#include <queue>

#define DEBUG_VERTEX_SHADER "Shader/debug.vs"
#define DEBUG_FRAGMENT_SHADER "Shader/debug.fs"

#define BASE_VERTEX_SHADER "Shader/base.vs"
#define BASE_FRAGMENT_SHADER "Shader/base.fs"

class FrameBuffer;
class ComponentMesh;
class Shader;

class Renderer
{
public:
	Renderer() {};
	Renderer(float2 size);
	~Renderer();

	void Init();
	void Start();
	void CleanUp();

	void Render();
	void Resize(float2 size);

	FrameBuffer* GetFrameBufffer() { return frameBuffer; }

	void QueueMesh(ComponentMesh* mesh);
public:
	float2 size = { 0, 0 };
private:
	void PreUpdate();
	void Update();
	void PostUpdate();

	//std::vector<MeshRenderer*> meshes;
	std::queue<ComponentMesh*> meshes;
private:
	FrameBuffer* frameBuffer = nullptr;

	Shader* baseShader = nullptr;
	Shader* debugShader = nullptr;
};

