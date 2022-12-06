#include "MeshImporter.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "Globals.h"
#include "ModuleSceneintro.h"

#include <vector>

#include "External/Assimp/include/assimp/cimport.h"
#include "External/Assimp/include/assimp/scene.h"
#include "External/Assimp/include/assimp/postprocess.h"

#pragma comment (lib, "lib/Assimp/lib/assimp.lib")

MeshImporter::MeshImporter()
{

}

MeshImporter::~MeshImporter()
{

}

void MeshImporter::Start()
{
	//Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void MeshImporter::CleanUp()
{
	//detach log stream
	aiDetachAllLogStreams();
}

GameObject* MeshImporter::ImportMesh(std::string filePath, GameObject* parent, bool dragAndDrop)
{
	GameObject* toReturn = nullptr;

	const aiScene* scene = aiImportFile(filePath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	aiNode* node = nullptr;

	if (scene != nullptr && scene->HasMeshes())
	{
		if (dragAndDrop) LOG(LOG_TYPE::SUCCESS, "IMPORTING FILE: %s", filePath.c_str());

		node = scene->mRootNode;

		if (parent == nullptr)
		{
			toReturn = GenerateGameObjects(node, scene);
			SceneProperties::Instance()->root->AddChildren(toReturn);
		}
		else
		{
			parent->AddChildren(GenerateGameObjects(node, scene));
			toReturn = parent;
		}
	}

	if (scene == nullptr && dragAndDrop) LOG(LOG_TYPE::ERRO, "ERROR: Importing file: '%s'", filePath.c_str());

	return toReturn;
}
			
GameObject* MeshImporter::GenerateGameObjects(aiNode* node, const aiScene* scene, GameObject* parent)
{
	if (parent == nullptr && scene->mNumMeshes > 1) parent = new GameObject(scene->mRootNode->mName.C_Str());

	if (scene->HasMeshes())
	{
		//Meshes
		for (uint i = 0; i < node->mNumChildren; ++i)
		{
			//New Spatial GameObject with MeshRenderer component
			GameObject* go = new GameObject(node->mChildren[i]->mName.C_Str());
			go->CreateComponent(MESH);
			go->CreateComponent(MATERIAL);

			//Add Mesh to the gameObject
			MeshRenderer* meshRenderer = new MeshRenderer(GenerateMesh(scene->mMeshes[i]));
			go->GetComponent<ComponentMesh>(MESH)->SetMesh(meshRenderer);

			//Recursivnes
			if (node->mChildren[i]->mNumChildren > 1)
			{
				for (uint i2 = 0; i2 < node->mChildren[i]->mNumChildren; ++i2)
				{
					go = GenerateGameObjects(node->mChildren[i]->mChildren[i2], scene, go);
				}
			}

			//Add GameObject to it's parent
			if (parent == nullptr) parent = go;
			else parent->AddChildren(go);
		}
	}

	return parent;
}

Meshe MeshImporter::GenerateMesh(aiMesh* mesh)
{
	Meshe newMesh = Meshe();
	//newMesh.InitMesh();

	bool hasTex = mesh->HasTextureCoords(0);

	newMesh.numFaces = mesh->mNumFaces;

	//Vertex
	for (uint i = 0; i < mesh->mNumVertices; ++i)
	{
		float3 position = float3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		float3 normal;
		float2 textCoords = float2(0.0f, 0.0f);

		if (mesh->HasNormals()) normal = float3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->HasTextureCoords(i)) textCoords = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		newMesh.vertices.emplace_back(position, normal, textCoords);
	}
	LOG(LOG_TYPE::SUCCESS, "New mesh with %d vertices", mesh->mNumVertices);

	//Index
	if (mesh->HasFaces())
	{
		newMesh.indices.resize(mesh->mNumFaces * 3);
		for (uint i = 0; i < mesh->mNumFaces; ++i)
		{
			if (mesh->mFaces[i].mNumIndices != 3)
			{
				LOG(LOG_TYPE::ATTENTION, "WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&newMesh.indices[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}
	return newMesh;
}