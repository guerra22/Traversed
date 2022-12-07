#pragma once

#include "Module.h"

#include <vector>
#include "External/MathGeo/include/Geometry/LineSegment.h"

class Application;
class GameObject;
class ComponentCamera;
class MeshRenderer;

struct CameraProperties;

struct SceneProperties
{
public:
	GameObject* root = nullptr;

	SceneProperties();

	static SceneProperties* Instance();

	static void Delete();

	GameObject* GetSelectedGO(GameObject* go = nullptr);

	void UnselectGO();

	bool Intersect(GameObject* go, LineSegment ray);

	int GetGuizmoOperation() { return guizmoOperation; }
	void SetGuizmoOperation(int value) { guizmoOperation = value; }

	bool loadSceneRequest = false;
	std::string scenePath = "";

private:
	static SceneProperties* instance;

	int guizmoOperation = 7;//Translate
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Init() override;
	bool Start() override;

	bool CleanUp() override;

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	void SaveSettingsData(pugi::xml_node& save) override;
	void LoadSettingsData(pugi::xml_node& load) override;

	void NewScene();

	void SaveScene();

	void LoadScene(std::string filePath);

private:
	void InitGameObjects(GameObject* go);
	void UpdateGameObjects(GameObject* go);

	//void SaveGameObjects(GameObject* go, nlohmann::JsonData data);
	void SceneControls();

private:
	SceneProperties* sProps = nullptr;
	CameraProperties* cProps = nullptr;
};