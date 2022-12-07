#include "MeshImporter.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ModuleSceneintro.h"
#include "LibraryManager.h"

#include <vector>

#include "External/Assimp/include/assimp/cimport.h"
#include "External/Assimp/include/assimp/scene.h"
#include "External/Assimp/include/assimp/postprocess.h"

#pragma comment (lib, "assimp.lib")

MeshImporter::MeshImporter()
{

}

MeshImporter::~MeshImporter()
{

}

void MeshImporter::Init()
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
			Meshe mesh;

			std::string aux = "Library/Meshes/";
			aux += std::string(node->mChildren[i]->mName.C_Str());
			aux += ".mh";

			//Checks if the mesh already exists in the engine's CFF
			if (LibraryManager::Exists(aux))
			{
				mesh = LoadMesh(aux);
			}
			else
			{
				mesh = GenerateMesh(scene->mMeshes[i]);
				SaveMesh(mesh, aux);
				mesh.path = aux;
			}

			MeshRenderer* meshRenderer = new MeshRenderer(mesh);
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

	//Bounding box
	newMesh.bBox.SetNegativeInfinity();
	newMesh.bBox.Enclose((float3*)mesh->mVertices, newMesh.vertices.size());

	return newMesh;
}

void MeshImporter::SaveMesh(Meshe mesh, std::string filePath)
{
	uint ranges[2] =
	{
		mesh.indices.size(),
		mesh.vertices.size(),
	};

	uint size = sizeof(ranges) + sizeof(uint) * ranges[0] + sizeof(Vertex) * ranges[1] + sizeof(uint) + sizeof(float3) * 2;

	char* fileBuffer = new char[size];//Allocate
	char* cursor = fileBuffer;

	uint bytes = 0;

	//Store ranges
	bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);
	cursor += bytes;

	//Store indices
	bytes = sizeof(uint) * ranges[0];
	memcpy(cursor, &mesh.indices[0], bytes);

	cursor += bytes;

	//Store vertex position
	bytes = sizeof(Vertex) * ranges[1];
	memcpy(cursor, &mesh.vertices[0], bytes);
	cursor += bytes;

	//Store number of faces
	bytes = sizeof(uint);
	memcpy(cursor, &mesh.numFaces, bytes);
	cursor += bytes;

	//Bounding Box
	//Store BoundingBox MinPoint
	bytes = sizeof(float3);
	memcpy(cursor, &mesh.bBox.minPoint[0], bytes);
	cursor += bytes;

	//Store BoundingBox MaxPoint
	bytes = sizeof(float3);
	memcpy(cursor, &mesh.bBox.maxPoint[0], bytes);
	cursor += bytes;

	LibraryManager::Save(filePath, fileBuffer, size);

	RELEASE_ARRAY(fileBuffer);
}

Meshe MeshImporter::LoadMesh(std::string filePath)
{
	Meshe mesh;
	char* fileBuffer = nullptr;
	LibraryManager::Load(filePath, &fileBuffer);
	mesh.path = filePath;

	char* cursor = fileBuffer;

	uint ranges[2];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);
	cursor += bytes;

	mesh.indices.resize(ranges[0]);
	mesh.vertices.resize(ranges[1]);
	mesh.numFaces = 0;

	//Load indices
	bytes = sizeof(uint) * ranges[0];

	memcpy(&mesh.indices[0], cursor, bytes);
	cursor += bytes;

	//Load vertices
	bytes = sizeof(Vertex) * ranges[1];

	memcpy(&mesh.vertices[0], cursor, bytes);
	cursor += bytes;

	//Load number of faces
	bytes = sizeof(uint);
	memcpy(&mesh.numFaces, cursor, bytes);
	cursor += bytes;

	//Bounding Box
	mesh.bBox.SetNegativeInfinity();
	//Load BoundingBox MinPoint
	bytes = sizeof(float3);
	memcpy(&mesh.bBox.minPoint[0], cursor, bytes);
	cursor += bytes;

	//Load BoundingBox MaxPoint
	bytes = sizeof(float3);
	memcpy(&mesh.bBox.maxPoint[0], cursor, bytes);
	cursor += bytes;

	RELEASE_ARRAY(fileBuffer);

	return mesh;
}