#ifndef __SCENE_H__
#define __SCENE_H__

#include "App.h"
#include "Globals.h"
#include "List.h"
#include "Animation.h"
#include "Module.h"

class PhysicWorld;
class PhysicBody;

struct Player1 {
	Animation idlePlayerAnim;
	Animation jumpingPlayerAnim;
	Animation walkingPlayerAnim;
	Animation deathPlayerAnim;
	PhysicBody* player;
};

class Scene : public Module
{
protected:

	App* _app;

	List<SDL_Texture*> sceneTextures;
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	PhysicBody* walls[3];
	PhysicBody* floor[6];
	PhysicBody* water;

	PhysicWorld* world;

private:
	SDL_Texture* playerTexture;

	Player1* p;
	Animation* currentAnim = nullptr;
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim, deathPlayerAnim;
	enum State
	{
		IDLE,
		WALK,
		JUMP
	};
	State pState;
	float maxSpeedX;
	float minSpeedX;

	SDL_Texture* img;

	int playerWidth;
	int playerHeight;

	bool fx_on;
	float playerJumpForce;

	SDL_RendererFlip playerFlip;

	SDL_Texture* playerTex;
	iPoint position;

	int healthFont = -1;
	char livesText[10] = { "\0" };

	PhysicBody* playerBody;
};

#endif // __SCENE_H__