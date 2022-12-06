#pragma once

#include "Module.h"

#include <vector>

class Application;
class GameObject;
class ComponentCamera;

struct SceneProperties
{
public:
	GameObject* root = nullptr;

	SceneProperties();

	static SceneProperties* Instance();

	static void Delete();

	GameObject* GetSelectedGO(GameObject* go = nullptr);

private:
	static SceneProperties* instance;
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


private:
	SceneProperties* sProps = nullptr;

private:
	void InitGameObjects(GameObject* go);
	void UpdateGameObjects(GameObject* go);
};