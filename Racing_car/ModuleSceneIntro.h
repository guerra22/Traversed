#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define INITIAL_TIME 100

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Plane* ground;

	PhysBody3D* physSensor;

	Cube wall[4];
	Cube borders[4];
	Cube map[25];
	Sphere ball[5];
	Cube grass[7];
	Cube ramp[20];
	Cube turbo[5];
	Cube checkpoints[4];
	Cube flag[3];

	uint lap = 1;
	uint secondsSinceInit;
	uint timer = INITIAL_TIME;
	uint frames = 0;
	bool starting;
	int passedCheckpoints;
};
