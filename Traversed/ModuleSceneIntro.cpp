#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "Primitive.h"
#include "ModuleUI.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Scene";
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOGGING("Loading Intro assets");
	bool ret = true;

	//App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOGGING("Unloading Intro scene");

	for (int n = 0; n < primitives.size(); n++)
	{
		delete primitives[n];
	}
	primitives.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	NormalPlane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	if (App->ui->testCube)
	{
		Cube c(2, 2, 2);
	}
	if (App->ui->testSphere)
	{
		SpherePrimitive s(6.0, 6.0, 12);
	}
	if (App->ui->testCylinder)
	{
		CylinderPrimitive k(6.0, 12.0);
	}

	//TODO 3: Nothing to do here. But it's good to know where all primitives are being updated
	for (uint n = 0; n < primitives.size(); n++)
	{
		primitives[n]->Update();
	}

	for (uint i = 0; i < game_objects.size(); i++)
	{
		if (game_objects[i]->IsActive())
		{
			game_objects[i]->Update(dt);
		}
	}	
	//App->renderer3D->DrawExampleMesh();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//TODO 3: Nothing to do here. But it's good to know where all primitives are being rendered
	for (uint n = 0; n < primitives.size(); n++)
	{
		primitives[n]->Render();
	}
	for (uint j = 0; j < game_objects.size(); j++)
	{
		game_objects.at(j)->Render();
	}

	return UPDATE_CONTINUE;
}

GameObject* ModuleSceneIntro::CreateGameObject(const char* name, GameObject* parent)
{
	if (parent == nullptr)
	{
		std::string gameObjName = name;

		if (!game_objects.empty())
		{
			gameObjName += std::to_string(game_objects.size());
		}
		GameObject* gameObject = new GameObject(this->App, game_objects.size(), gameObjName, true, false);
		game_objects.push_back(gameObject);
		return gameObject;
	}

	if (parent != nullptr)
	{
		GameObject* gameObject = new GameObject(this->App, parent->childs.size(), name, true, false);
		parent->childs.push_back(gameObject);
		return gameObject;

	}
}