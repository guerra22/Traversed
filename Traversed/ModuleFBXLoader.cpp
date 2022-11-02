#include "Globals.h"
#include "Application.h"
#include "ModuleFBXLoader.h"
#include "ModuleRenderer3D.h"
#include "ModuleMaterials.h"
#include "ModuleSceneIntro.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"

#include "External/Assimp/include/assimp/cimport.h"
#include "External/Assimp/include/assimp/scene.h"
#include "External/Assimp/include/assimp/postprocess.h"
#include "External/Assimp/include/assimp/ai_assert.h"

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

	return true;
}

bool ModuleFBXLoader::Start()
{
	LOGGING("Setting up the loader");
	bool ret = true;

	//LoadMeshToGameObject(App->sceneintro->CreateGameObject("BakerHouse", nullptr), "Assets/BakerHouse.fbx", "Assets/Resources/Baker_House.png");

	return ret;
}

bool ModuleFBXLoader::CleanUp()
{
	LOGGING("Cleaning up FBX loader");

	aiDetachAllLogStreams();
	return true;
}

bool ModuleFBXLoader::LoadMeshToGameObject(GameObject* owner, const char* file_path, const char* texturePath)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			ComponentMesh* NewMesh;
			ComponentMaterial* MaterialUsed;
			Texture* textureUsed = new Texture();
			if (i == 0)
			{
				NewMesh = (ComponentMesh*)owner->GetComponent(COMPONENT_TYPES::MESH);
				MaterialUsed = (ComponentMaterial*)owner->GetComponent(COMPONENT_TYPES::MATERIAL);
			}
			if (i > 0)
			{
				GameObject* child = App->sceneintro->CreateGameObject("child", owner);

				NewMesh = (ComponentMesh*)child->GetComponent(COMPONENT_TYPES::MESH);
				MaterialUsed = (ComponentMaterial*)child->GetComponent(COMPONENT_TYPES::MATERIAL);
			}

			NewMesh->mesh.num_vertex = scene->mMeshes[i]->mNumVertices;
			NewMesh->mesh.vertex = new float[NewMesh->mesh.num_vertex * 3];

			memcpy(NewMesh->mesh.vertex, scene->mMeshes[i]->mVertices, sizeof(float3) * NewMesh->mesh.num_vertex);

			glGenBuffers(1, &NewMesh->mesh.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, NewMesh->mesh.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NewMesh->mesh.num_vertex * 3, NewMesh->mesh.vertex, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			LOGGING("New mesh with %d vertices", NewMesh->mesh.num_vertex);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				NewMesh->mesh.num_index = scene->mMeshes[i]->mNumFaces * 3;
				NewMesh->mesh.index = new GLuint[NewMesh->mesh.num_index]; 

				for (uint z = 0; z < scene->mMeshes[i]->mNumFaces; z++)
				{
					if (scene->mMeshes[i]->mFaces[z].mNumIndices != 3)
					{
						LOGGING("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&NewMesh->mesh.index[z * 3], scene->mMeshes[i]->mFaces[z].mIndices, 3 * sizeof(uint));
					}
				}

				glGenBuffers(1, &NewMesh->mesh.id_index);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewMesh->mesh.id_index);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * NewMesh->mesh.num_index, NewMesh->mesh.index, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			}

			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				NewMesh->mesh.num_uvs = scene->mMeshes[i]->mNumVertices;

				NewMesh->mesh.textCords = new float[NewMesh->mesh.num_uvs * 3];

				memcpy(NewMesh->mesh.textCords, scene->mMeshes[i]->mTextureCoords[0], NewMesh->mesh.num_uvs * sizeof(float3));
				int x = scene->mMeshes[i]->mNumUVComponents[0];
			}
			NewMesh->mesh.texture_data.id = scene->mMeshes[i]->mMaterialIndex;

			glGenBuffers(1, &(NewMesh->mesh.id_uvs));
			glBindBuffer(GL_ARRAY_BUFFER, NewMesh->mesh.id_uvs);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NewMesh->mesh.num_uvs * 3, NewMesh->mesh.textCords, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			if (texturePath != nullptr)
			{
				App->materials->Import(texturePath, textureUsed);
				MaterialUsed->materialUsed = textureUsed;
				MaterialUsed->textures.push_back(textureUsed);
			}
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