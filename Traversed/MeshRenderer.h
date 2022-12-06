#pragma once

#include "Mesh.h"
#include "TextureImporter.h"

#include "External/Glew/include/glew.h"
#include "External/MathGeo/include/Math/float2.h"
#include "External/MathGeo/include/Math/float3.h"
#include "External/MathGeo/include/Math/float4x4.h"

#include <vector>

typedef unsigned int uint;

class Shader;

struct Vertex {
	Vertex(float3 position, float3 normal, float2 texCoord)
	{
		this->position = position;
		this->normal = normal;
		this->texCoords = texCoord;
	}

	float3 position;
	float3 normal;
	float2 texCoords;
};

struct Meshe
{
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;
	uint numFaces;
};

struct TextureData;

class MeshRenderer
{
public:
	MeshRenderer();
	MeshRenderer(Meshe meshData);
	~MeshRenderer();

	void Draw(Shader* shader, Texture text, float4x4 model = float4x4::identity);

	void SetShader(Shader* shader);
	void SetDebugShader(Shader* shader);

	void SetTexture(Texture texture);

	void SetPosition(float3 newPos);
	void SetRotation(float3 newRot);
	void SetSize(float3 newSize);

	void DrawNormals(Shader* shader, float4x4 model, bool faceNormals = false);

	void CreateNormals(float magnitude = 0.25f);
	void CleanNormals();

public:
	Meshe mesh;

private:

	uint VAO;
	uint VBO;
	uint EBO;

	uint VNVAO;
	uint VNVBO;
	std::vector<float3> vNormals;

	uint FNVAO;
	uint FNVBO;
	std::vector<float3> fNormals;

	Shader* shader = nullptr;
	Shader* debugShader = nullptr;
};

