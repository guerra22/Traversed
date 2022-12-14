#pragma once

#include <string>
#include <vector>
#include "JsonUtils.h"

class aiMesh;
class aiNode;
class aiScene;
class Mesh;
class GameObject;
class ResourceModel;
class MeshRenderer;
class LibraryFolder;

struct Meshe;

class MeshImporter
{
public:
	MeshImporter();
	~MeshImporter();

	void Init();
	void CleanUp();

public:
	static MeshRenderer* ImportMeshFromLibrary(ResourceModel* model, std::string meshUuid);
	static void ImportToLibrary(ResourceModel* resource);
	static GameObject* ImportFromLibrary(ResourceModel* resource);

	static GameObject* ImportMesh(std::string filePath, GameObject* parent = nullptr, bool dragAndDrop = false);

	static Meshe LoadMesh(std::string filePath);

	static void SaveGameObjects(GameObject* go, std::vector<nlohmann::ordered_json>& goPool);

private:
	static std::vector<std::string> GetMaterials(const aiScene* scene);

	static Meshe GenerateMesh(aiMesh* mesh);
	static GameObject* GenerateGameObjects(aiNode* node, const aiScene* scene, std::vector<std::string> matUuid, GameObject* parent = nullptr, ResourceModel* resource = nullptr);
	static void SaveMesh(Meshe mesh, std::string filePath);

	static void IterateForFolders(LibraryFolder* fol, std::vector<LibraryFolder*>& folders);
};


