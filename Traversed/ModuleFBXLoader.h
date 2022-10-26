#pragma once

#include "Module.h"

#include "External/SDL/include/SDL.h"
#include "External/Glew/include/glew.h"

#include <gl/GL.h>
#include <gl/GLU.h>

class Application;

struct VertexData
{
	GLuint id_index = 0; // index in VRAM
	GLuint num_index = 0;
	GLuint* index = nullptr;
	GLuint id_vertex = 0; // unique vertex in VRAM
	GLuint num_vertex = 0;
	float* vertex = nullptr;
};

class ModuleFBXLoader : public Module
{
public:

	ModuleFBXLoader(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleFBXLoader();

	bool Init();
	bool CleanUp();

	bool LoadMesh(const char* file_path);

	bool LoadConfig(JsonParser& node) override;
	bool SaveConfig(JsonParser& node) const override;

public:
	std::vector<VertexData> meshes;
};
