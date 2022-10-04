#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "PhysicWorld.h"

#include "Defs.h"
#include "Log.h"

iPoint position;
Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	img = app->tex->Load("Assets/Textures/map1.png");
	//app->audio->PlayMusic("Assets/Audio/Music/Retro_Platforming_David_Fesliyan.ogg");
	app->render->camera.x = app->render->camera.y = 0;

	p = new Player1;
	pState = IDLE;

	//Idle anim
	p->idlePlayerAnim.PushBack({ 28, 19, 50, 50 });
	p->idlePlayerAnim.PushBack({ 109, 20, 50, 50 });
	p->idlePlayerAnim.PushBack({ 190, 19, 50, 50 });
	p->idlePlayerAnim.PushBack({ 269, 18, 50, 50 });
	p->idlePlayerAnim.loop = true;
	p->idlePlayerAnim.mustFlip = true;
	p->idlePlayerAnim.speed = 0.01f;
	//Walking anim
	p->walkingPlayerAnim.PushBack({ 29, 82, 50, 50 });
	p->walkingPlayerAnim.PushBack({ 108, 81, 50, 50 });
	p->walkingPlayerAnim.PushBack({ 189, 82, 50, 50 });
	p->walkingPlayerAnim.PushBack({ 271, 81, 50, 50 });
	p->walkingPlayerAnim.loop = true;
	p->walkingPlayerAnim.mustFlip = true;
	p->walkingPlayerAnim.speed = 0.1f;
	//Jump anim
	p->jumpingPlayerAnim.PushBack({ 431, 80, 50, 50 });
	p->jumpingPlayerAnim.PushBack({ 428, 16, 50, 50 });
	p->jumpingPlayerAnim.loop = true;
	p->walkingPlayerAnim.mustFlip = true;
	p->jumpingPlayerAnim.speed = 0.1f;

	playerTexture = app->tex->Load("Assets/Textures/Mage80x64.png");

	world = new PhysicWorld({ 0,10 });

	p->player = new PhysicBody({ 100,100 }, BodyType::DYNAMIC, 25);

	world->AddPhysicBody(p->player);
	p->player->gravityScale = 5;
	p->player->friction = 1;

	water = new PhysicBody({ 504,674 }, BodyType::WATER, 464, 48);
	world->AddPhysicBody(water);

	walls[0] = new PhysicBody({ 640,0 }, BodyType::STATIC, 1280, 5);
	walls[1] = new PhysicBody({ 0,360 }, BodyType::STATIC, 5, 720);
	walls[2] = new PhysicBody({ 1270,354 }, BodyType::STATIC, 5, 720);

	floor[0] = new PhysicBody({ 280,674 }, BodyType::STATIC, 560, 144);
	floor[1] = new PhysicBody({ 650,722 }, BodyType::STATIC, 192, 48);
	floor[2] = new PhysicBody({ 1064,674 }, BodyType::STATIC, 560, 144);
	floor[3] = new PhysicBody({ 124,450 }, BodyType::STATIC, 4, 16);
	floor[4] = new PhysicBody({ 412,578 }, BodyType::STATIC, 4, 16);
	floor[5] = new PhysicBody({ 954,450 }, BodyType::STATIC, 4, 16);


	for (int i = 0; i < 3; i++)
	{
		world->AddPhysicBody(walls[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		world->AddPhysicBody(floor[i]);
	}

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	world->Update(1.0 / 60);

	switch (pState)
	{
	case IDLE:
		currentAnim = &p->idlePlayerAnim;
		break;
	case WALK:
		currentAnim = &p->walkingPlayerAnim;
		break;
	case JUMP:
		currentAnim = &p->jumpingPlayerAnim;
		break;
	}
	SDL_Rect rect = currentAnim->GetCurrentFrame();

	
	bool ret = true;

	//Player movement
	maxSpeedX = 2;
	minSpeedX = -2;

	if (pState == WALK || pState == JUMP) {
		pState = IDLE;
	}

	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
	{
		p->player->SetLinearVelocity({ 80, p->player->GetLinearVelocity().y });
		if (pState == IDLE) {
			pState = WALK;
		}
		p->walkingPlayerAnim.Update();
		p->idlePlayerAnim.Reset();
	}
	//Left
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
	{
		p->player->SetLinearVelocity({ -80, p->player->GetLinearVelocity().y });
		if (pState == IDLE) {
			pState = WALK;
		}
		p->walkingPlayerAnim.Update();
		p->idlePlayerAnim.Reset();
	}
	//Jump
	if ((app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN))
	{
		p->player->AddForceToCenter({ 0.0f, -6000.0f });
		if (pState == IDLE) {
			pState = JUMP;
		}
		p->jumpingPlayerAnim.Update();
		p->idlePlayerAnim.Reset();
		p->walkingPlayerAnim.Reset();
	}

    return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(img, 0, 0);

	app->render->DrawTexture(playerTexture, (p->player->position.x - 25), (p->player->position.y - 25),
		&(currentAnim->GetCurrentFrame()), 1);

	app->render->DrawRectangle({ 0,0,1280,5 }, 255, 0, 0);
	app->render->DrawRectangle({ 1275,0,5,720 }, 255, 0, 0);
	app->render->DrawRectangle({ 0,0,5,720 }, 255, 0, 0);
	app->render->DrawRectangle({ 0,576,560,144 }, 255, 0, 255, 70);
	app->render->DrawRectangle({ 560,672,192,48 }, 255, 0, 255, 70);
	app->render->DrawRectangle({ 752,576,560,144 }, 255, 0, 255, 70);
	app->render->DrawRectangle({ 96,416,32,32 }, 255, 0, 255, 70);
	app->render->DrawRectangle({ 384,544,32,32 }, 255, 0, 255, 70);
	app->render->DrawRectangle({ 928,416,32,32 }, 255, 0, 255, 70);

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	RELEASE(world);

	for (int i = 0; i < sceneTextures.count(); i++)
	{
		if (sceneTextures[i])
		{
			_app->tex->UnLoad(sceneTextures[i]);
			sceneTextures[i] = nullptr;
		}
	}

	return true;
}