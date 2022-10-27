#pragma once

#include "Resource.h"
#include "Module.h"
#include "ModuleFBXLoader.h"

struct aiScene;
struct aiMaterials;

class ModuleMaterials : public Module
{
public:

	ModuleMaterials(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleMaterials();

	bool Init();

	bool CleanUp();

	bool Import(const char* path, VertexData* newMaterial);
	//bool Import(const char* buffer, uint size, R_Material* r_material);

	uint CreateTexture(const void* data, uint width,
		uint height,
		int internal_format = 0x1908,		// 0x1908 = GL_RGBA
		uint format = 0x1908,				// 0x1908 = GL_RGBA
		uint target = 0x0DE1,				// 0x0DE1 = GL_TEXTURE_2D
		int filter_type = 0x2600,			// 0x2600 = GL_NEAREST
		int filling_type = 0x2901);		// 0x2901 = GL_REPEAT
public:

};


