#include "ModuleSceneIntro.h"
#include "Application.h"
#include "LibraryManager.h"
#include "ModuleCamera3D.h"

#include "GameObject.h"
#include "MeshImporter.h"
#include "TextureImporter.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include <fstream>

#pragma region SceneProperties
SceneProperties::SceneProperties()
{
	root = new GameObject("Scene");
	root->DeleteComponent(TRANSFORM);
}

SceneProperties* SceneProperties::Instance()
{
	if (instance == nullptr) instance = new SceneProperties();

	return instance;
}

GameObject* SceneProperties::GetSelectedGO(GameObject* go)
{
	GameObject* toReturn = go;
	if (go == nullptr) toReturn = root;

	if (toReturn->selected) return toReturn;
	else
	{
		GameObject* aux = nullptr;
		for (int i = 0; i < toReturn->children.size(); ++i)
		{
			aux = GetSelectedGO(toReturn->children[i]);
			if (aux != nullptr && aux->selected) return aux;
		}
	}

	return nullptr;
}

void SceneProperties::Delete()
{
	if (instance != nullptr)
	{
		RELEASE(instance);
	}
}

SceneProperties* SceneProperties::instance = nullptr;

#pragma endregion Scene Properties Singleton Struct

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Scene";
}

ModuleSceneIntro::~ModuleSceneIntro()
{

}

bool ModuleSceneIntro::Init()
{
	sProps = sProps->Instance();
	cProps = cProps->Instance();

	return true;
}

bool ModuleSceneIntro::Start()
{
	//Import Example mesh & texture
	GameObject* aux = MeshImporter::ImportMesh("Assets/BakerHouse.fbx");

	std::vector<GameObject*> vGO = aux->GetChildrens();

	for (int i = 0; i < vGO.size(); ++i)
	{
		vGO[i]->GetComponent<ComponentMaterial>(MATERIAL)->SetTexture
		(TextureImporter::ImportTexture("Assets/Resources/Baker_house.png"));
	}

	if (sProps->root == nullptr) return UPDATE_CONTINUE;
	InitGameObjects(sProps->root);

	return true;
}

bool ModuleSceneIntro::CleanUp()
{
	RELEASE(sProps->root);
	sProps->Delete();

	return true;
}

UpdateStatus ModuleSceneIntro::PreUpdate()
{

	return UPDATE_CONTINUE;
}

UpdateStatus ModuleSceneIntro::Update()
{
	if (sProps->root == nullptr) return UPDATE_CONTINUE;

	//Update Game Objects
	UpdateGameObjects(sProps->root);

	return UPDATE_CONTINUE;
}

UpdateStatus ModuleSceneIntro::PostUpdate()
{

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::NewScene()
{
	RELEASE(sProps->root);

	sProps->root = new GameObject("Root", false);
}


void ModuleSceneIntro::InitGameObjects(GameObject* go)
{
	go->Init();

	if (go->HasChildren())
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			InitGameObjects(go->children[i]);
		}
	}
}

void ModuleSceneIntro::UpdateGameObjects(GameObject* go)
{
	go->Update();

	if (go->HasChildren())
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			UpdateGameObjects(go->children[i]);
		}
	}
}

#pragma region Save/Load Settings
void SaveGameObjects(GameObject* go, std::vector<nlohmann::ordered_json>& goPool)
{
	goPool.push_back(go->Save());

	if (go->HasChildren())
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			SaveGameObjects(go->children[i], goPool);
		}
	}
}

void LoadGameObjects()
{

}

void ModuleSceneIntro::SaveScene()
{
	nlohmann::JsonData data;
	std::vector<nlohmann::ordered_json> goPool;
	SaveGameObjects(sProps->root, goPool);

	data.data.emplace("GameObjects", goPool);

	//Save to JSON
	LibraryManager::SaveJSON("Library/Scenes/Test.sc", data.data.dump(4));
}

void ModuleSceneIntro::LoadScene(std::string filePath)
{
	NewScene();//Cleans scene

	nlohmann::JsonData data;

	try
	{
		char* buffer = nullptr;

		uint size = LibraryManager::Load(filePath, &buffer);
		data.data = nlohmann::ordered_json::parse(buffer, buffer + size);
		RELEASE(buffer);
	}
	catch (nlohmann::json::parse_error& ex)
	{
		LOG(LOG_TYPE::ERRO, "Error: Scene parse at byte %i: %s", ex.byte, ex.what());
	}

	std::vector<nlohmann::ordered_json> aux;
	aux = data.GetJsonVector("GameObjects");

	if (aux.size() > 0)
	{
		std::map<std::string, GameObject*> sceneMap;

		//Load scene root
		nlohmann::JsonData rootData;
		rootData.data = aux.at(0);
		sProps->root->Load(rootData);

		//Load all other GO
		for (int i = 1; i < aux.size(); ++i)
		{
			nlohmann::JsonData goData;
			goData.data = aux.at(i);

			std::string parentUUID(goData.GetString("Parent_UUID"));

			GameObject* go = new GameObject("", false);
			go->Load(goData);

			if (sceneMap.count(parentUUID) == 1)
			{
				sceneMap[parentUUID]->AddChildren(go);
			}
			else sProps->root->AddChildren(go);


			sceneMap.insert({ go->uuid, go });
		}
	}

}

void ModuleSceneIntro::LoadSettingsData(pugi::xml_node& load)
{

}

void ModuleSceneIntro::SaveSettingsData(pugi::xml_node& save)
{

}
#pragma endregion Save & Load of Settings