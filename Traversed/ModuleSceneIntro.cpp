#include "ModuleSceneIntro.h"
#include "Application.h"
#include "ModuleInput.h"
#include "LibraryManager.h"
#include "ModuleCamera3D.h"

#include "GameObject.h"
#include "MeshImporter.h"
#include "TextureImporter.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include <fstream>

#include "External/ImGui/imgui_internal.h"
#include "External/ImGuizmo/ImGuizmo.h"

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

void SceneProperties::UnselectGO()
{
	GameObject* currentSelected = GetSelectedGO(root);
	if (currentSelected != nullptr) currentSelected->selected = false;
}

bool SceneProperties::Intersect(GameObject* go, LineSegment ray)
{
	ComponentMesh* meshRenderer = go->GetComponent<ComponentMesh>(MESH);
	if (meshRenderer != nullptr)
	{
		if (meshRenderer->GetAABB().Intersects(ray))
		{
			UnselectGO(); //Unselects current selected GO;
			go->selected = true;
			return true;
		}
	}

	//Iteration and check of childrens
	if (go->HasChildren())
	{
		for (int i = 0; i < go->children.size(); ++i)
		{
			if (Intersect(go->children[i], ray))
			{
				return true;
			}
		}
	}
	return false;
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
	if (sProps->root == nullptr) return UPDATE_CONTINUE;
	InitGameObjects(sProps->root);

	//sProps->loadSceneRequest = true;
	//sProps->scenePath = "/Library/Scenes/Street.sc";

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
	SceneControls();

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
	if (sProps->loadSceneRequest)
	{
		LoadScene(sProps->scenePath);
		sProps->loadSceneRequest = false;
		sProps->scenePath = "";
	}

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

void ModuleSceneIntro::SceneControls()
{
	if (!cProps->isMouseOnScene) return;
	//Translate
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && App->input->GetMouseButton(SDL_BUTTON_RIGHT) != KEY_REPEAT)
	{
		sProps->SetGuizmoOperation(ImGuizmo::OPERATION::TRANSLATE);
	}
	//Rotate
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && App->input->GetMouseButton(SDL_BUTTON_RIGHT) != KEY_REPEAT)
	{
		sProps->SetGuizmoOperation(ImGuizmo::OPERATION::ROTATE);
	}
	//Scale
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && App->input->GetMouseButton(SDL_BUTTON_RIGHT) != KEY_REPEAT)
	{
		sProps->SetGuizmoOperation(ImGuizmo::OPERATION::SCALE);
	}
}

#pragma region Save/Load Settings

void LoadGameObjects()
{

}

void ModuleSceneIntro::SaveScene()
{
	nlohmann::JsonData data;
	std::vector<nlohmann::ordered_json> goPool;
	MeshImporter::SaveGameObjects(sProps->root, goPool);

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