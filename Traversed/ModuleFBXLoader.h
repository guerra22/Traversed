#pragma once

#include "Module.h"

#include "External/Assimp/include/assimp/material.h"
#include "External/SDL/include/SDL.h"
#include "External/Glew/include/glew.h"

#include <gl/GL.h>
#include <gl/GLU.h>

class Application;

enum class TEXTURE_TYPE
{
	NONE = 0x0,
	DIFFUSE = 0x1,
	SPECULAR = 0x2,
	UNKNOWN = 0xC
};

struct Texture
{

	std::string		path;
	TEXTURE_TYPE	type;
	uint			id;
	uint			uid;
	uint			width;
	uint			height;
};

struct VertexData
{
	GLuint id_index = 0; // index in VRAM
	GLuint num_index = 0;
	GLuint* index = nullptr;
	GLuint id_vertex = 0; // unique vertex in VRAM
	GLuint num_vertex = 0;
	float* vertex = nullptr;

	GLfloat* textCords = nullptr;
	GLuint num_uvs = 0;
	GLuint id_uvs = 0;

	Texture texture_data;
};

class ModuleFBXLoader : public Module
{
public:

	ModuleFBXLoader(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleFBXLoader();

	bool Init();
	bool Start();
	bool CleanUp();

	bool LoadMesh(const char* file_path, const char* texturePath);

	bool LoadConfig(JsonParser& node) override;
	bool SaveConfig(JsonParser& node) const override;

public:
	std::vector<VertexData> meshes;
	std::vector<VertexData*> textures;
};
