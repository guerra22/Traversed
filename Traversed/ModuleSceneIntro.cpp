#include "ModuleSceneIntro.h"
#include "Application.h"

#include "GameObject.h"
#include "MeshImporter.h"
#include "TextureImporter.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

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
		(TextureImporter::ImportTexture("Assets/Baker_house.png"));
	}

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
	InitGameObjects(sProps->root);

	return UPDATE_CONTINUE;
}

UpdateStatus ModuleSceneIntro::Update()
{

	//Update Game Objects
	UpdateGameObjects(sProps->root);

	return UPDATE_CONTINUE;
}

UpdateStatus ModuleSceneIntro::PostUpdate()
{

	return UPDATE_CONTINUE;
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
void ModuleSceneIntro::LoadSettingsData(pugi::xml_node& load)
{

}

void ModuleSceneIntro::SaveSettingsData(pugi::xml_node& save)
{

}
#pragma endregion Save & Load of Settings