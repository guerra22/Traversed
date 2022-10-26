#include "Globals.h"
#include "Application.h"
#include "ModuleFBXLoader.h"
#include "ModuleRenderer3D.h"

#include "External/Assimp/include/assimp/cimport.h"
#include "External/Assimp/include/assimp/scene.h"
#include "External/Assimp/include/assimp/postprocess.h"
#include "External/Assimp/include/assimp/ai_assert.h"
#include "External/Glew/include/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include <vector>

#pragma comment (lib, "External/Assimp/lib/assimp-vc142-mt.lib")

ModuleFBXLoader::ModuleFBXLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Loader";
}

// Destructor
ModuleFBXLoader::~ModuleFBXLoader()
{
}

// Called before render is available
bool ModuleFBXLoader::Init()
{
	LOGGING("Init FBX loader");

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
	LoadMesh("Game/Assets/BakerHouse.fbx");

	return true;
}

bool ModuleFBXLoader::CleanUp()
{
	LOGGING("Cleaning up FBX loader");

	aiDetachAllLogStreams();
	return true;
}

bool ModuleFBXLoader::LoadMesh(const char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		VertexData NewMesh;
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			NewMesh.num_vertex = scene->mMeshes[i]->mNumVertices;
			NewMesh.vertex = new float[NewMesh.num_vertex * 3];

			memcpy(NewMesh.vertex, scene->mMeshes[i]->mVertices, sizeof(float3) * NewMesh.num_vertex);

			glGenBuffers(1, &NewMesh.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, NewMesh.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NewMesh.num_vertex * 3, NewMesh.vertex, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			LOGGING("New mesh with %d vertices", NewMesh.num_vertex);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				NewMesh.num_index = scene->mMeshes[i]->mNumFaces * 3;
				NewMesh.index = new GLuint[NewMesh.num_index]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOGGING("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&NewMesh.index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
				glGenBuffers(1, &NewMesh.id_index);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewMesh.id_index);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * NewMesh.num_index, NewMesh.index, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			meshes.push_back(NewMesh);
		}
		return true;
	}
	else
	{
		LOGGING("Error loading scene % s", file_path);
	}
	aiReleaseImport(scene);
}

bool ModuleFBXLoader::LoadConfig(JsonParser& node)
{

	return true;
}

bool ModuleFBXLoader::SaveConfig(JsonParser& node) const
{

	return true;
}