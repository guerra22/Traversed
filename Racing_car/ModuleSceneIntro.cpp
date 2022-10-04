#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ground = new Plane(0, 1, 0, 0);
	ground->axis = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	starting = true;
	passedCheckpoints = 0;

	wall[0].SetPos(0, 0, 256);
	wall[0].size.x = 5;
	wall[0].size.y = 512;
	wall[0].size.z = 512;
	wall[0].axis = false;
	wall[0].color = Green;
	App->physics->AddBody(wall[0], 0);

	wall[1].SetPos(512, 0, 256);
	wall[1].size.x = 5;
	wall[1].size.y = 512;
	wall[1].size.z = 512;
	wall[1].axis = false;
	wall[1].color = Green;
	App->physics->AddBody(wall[1], 0);

	wall[2].SetPos(256, 0, 0);
	wall[2].size.x = 512;
	wall[2].size.y = 512;
	wall[2].size.z = 5;
	wall[2].axis = false;
	wall[2].color = Green;
	App->physics->AddBody(wall[2], 0);

	wall[3].SetPos(256, 0, 512);
	wall[3].size.x = 512;
	wall[3].size.y = 512;
	wall[3].size.z = 5;
	wall[3].axis = false;
	wall[3].color = Green;
	App->physics->AddBody(wall[3], 0);

	borders[0].SetPos(0, 1, 256);
	borders[0].size.x = 9;
	borders[0].size.y = 6;
	borders[0].size.z = 512;
	borders[0].axis = false;
	borders[0].color.Set(255, 0, 0);
	App->physics->AddBody(borders[0], 0);

	borders[1].SetPos(512, 1, 256);
	borders[1].size.x = 9;
	borders[1].size.y = 6;
	borders[1].size.z = 512;
	borders[1].axis = false;
	borders[1].color.Set(255, 0, 0);
	App->physics->AddBody(borders[1], 0);

	borders[2].SetPos(256, 1, 0);
	borders[2].size.x = 512;
	borders[2].size.y = 6;
	borders[2].size.z = 9;
	borders[2].axis = false;
	borders[2].color.Set(255, 0, 0);
	App->physics->AddBody(borders[2], 0);

	borders[3].SetPos(256, 1, 512);
	borders[3].size.x = 512;
	borders[3].size.y = 6;
	borders[3].size.z = 9;
	borders[3].axis = false;
	borders[3].color.Set(255, 0, 0);
	App->physics->AddBody(borders[3], 0);

	//race track 
	map[0].SetPos(0, -1, 0);
	map[0].size.x = 1200;
	map[0].size.y = 2;
	map[0].size.z = 1200;
	map[0].axis = false;
	map[0].color = Blue;
	App->physics->AddBody(map[0], 0);
	
	map[1].SetPos(25, 0, 122);
	map[1].size.x = 2;
	map[1].size.y = 60;
	map[1].size.z = 146;
	map[1].axis = false;
	map[1].color = White;
	App->physics->AddBody(map[1], 0);

	map[2].SetPos(47, 0, 194);
	map[2].size.x = 45;
	map[2].size.y = 60;
	map[2].size.z = 2;
	map[2].axis = false;
	map[2].color = White;
	App->physics->AddBody(map[2], 0);

	map[3].SetPos(25, 0, 224);
	map[3].size.x = 45;
	map[3].size.y = 60;
	map[3].size.z = 2;
	map[3].axis = false;
	map[3].color = White;
	App->physics->AddBody(map[3], 0);

	map[4].SetPos(68.5, 0, 324);
	map[4].size.x = 2;
	map[4].size.y = 60;
	map[4].size.z = 260;
	map[4].axis = false;
	map[4].color = White;
	App->physics->AddBody(map[4], 0);
	
	map[5].SetPos(48.5, 0, 273);
	map[5].size.x = 2;
	map[5].size.y = 60;
	map[5].size.z = 100;
	map[5].axis = false;
	map[5].color = White;
	App->physics->AddBody(map[5], 0);
	
	map[6].SetPos(25, 0, 322);
	map[6].size.x = 45;
	map[6].size.y = 60;
	map[6].size.z = 2;
	map[6].axis = false;
	map[6].color = White;
	App->physics->AddBody(map[6], 0);

	map[7].SetPos(111, 0, 455);
	map[7].size.x = 87;
	map[7].size.y = 60;
	map[7].size.z = 2;
	map[7].axis = false;
	map[7].color = White;
	App->physics->AddBody(map[7], 0);

	map[8].SetPos(439, 0, 455);
	map[8].size.x = 79;
	map[8].size.y = 60;
	map[8].size.z = 2;
	map[8].axis = false;
	map[8].color = White;
	App->physics->AddBody(map[8], 0);

	map[9].SetPos(475, 0, 410);
	map[9].size.x = 79;
	map[9].size.y = 60;
	map[9].size.z = 2;
	map[9].axis = false;
	map[9].color = White;
	App->physics->AddBody(map[9], 0);

	map[10].SetPos(400.5, 0, 420);
	map[10].size.x = 2;
	map[10].size.y = 60;
	map[10].size.z = 69;
	map[10].axis = false;
	map[10].color = White;
	App->physics->AddBody(map[10], 0);

	map[11].SetPos(435, 0, 385);
	map[11].size.x = 71;
	map[11].size.y = 60;
	map[11].size.z = 2;
	map[11].axis = false;
	map[11].color = White;
	App->physics->AddBody(map[11], 0);

	map[12].SetPos(470, 0, 351.5);
	map[12].size.x = 2;
	map[12].size.y = 60;
	map[12].size.z = 69;
	map[12].axis = false;
	map[12].color = White;
	App->physics->AddBody(map[12], 0);

	map[13].SetPos(453.5, 0, 317);
	map[13].size.x = 35;
	map[13].size.y = 60;
	map[13].size.z = 2;
	map[13].axis = false;
	map[13].color = White;
	App->physics->AddBody(map[13], 0);

	map[14].SetPos(472, 0, 250.5);
	map[14].SetRotation(-70.0f, { 1,0,0 });
	map[14].size.x = 71;
	map[14].size.y = 110;
	map[14].size.z = 1;
	map[14].axis = false;
	map[14].color = White;
	App->physics->AddBody(map[14], 0);

	map[15].SetPos(435, 0, 183.5);
	map[15].size.x = 2;
	map[15].size.y = 60;
	map[15].size.z = 269;
	map[15].axis = false;
	map[15].color = White;
	App->physics->AddBody(map[15], 0);

	map[16].SetPos(472, 0, 150.5);
	map[16].size.x = 71;
	map[16].size.y = 60;
	map[16].size.z = 1;
	map[16].axis = false;
	map[16].color = White;
	App->physics->AddBody(map[16], 0);

	map[17].SetPos(230, 0, 50);
	map[17].size.x = 408;
	map[17].size.y = 60;
	map[17].size.z = 2;
	map[17].axis = false;
	map[17].color = White;
	App->physics->AddBody(map[17], 0);

	map[18].SetPos(330, 8, 33);
	map[18].size.x = 16;
	map[18].size.y = 16;
	map[18].size.z = 16;
	map[18].axis = false;
	map[18].color = White;
	App->physics->AddBody(map[18], 0);

	map[19].SetPos(304, 8, 20);
	map[19].size.x = 16;
	map[19].size.y = 16;
	map[19].size.z = 16;
	map[19].axis = false;
	map[19].color = White;
	App->physics->AddBody(map[19], 0);

	map[20].SetPos(260, 8, 40);
	map[20].size.x = 16;
	map[20].size.y = 16;
	map[20].size.z = 16;
	map[20].axis = false;
	map[20].color = White;
	App->physics->AddBody(map[20], 0);

	map[21].SetPos(260, 8, 13);
	map[21].size.x = 16;
	map[21].size.y = 16;
	map[21].size.z = 16;
	map[21].axis = false;
	map[21].color = White;
	App->physics->AddBody(map[21], 0);

	map[22].SetPos(230, 10, 28);
	map[22].size.x = 20;
	map[22].size.y = 20;
	map[22].size.z = 20;
	map[22].axis = false;
	map[22].color = White;
	App->physics->AddBody(map[22], 0);

	map[23].SetPos(198, 9, 39.5);
	map[23].size.x = 18;
	map[23].size.y = 18;
	map[23].size.z = 18;
	map[23].axis = false;
	map[23].color = White;
	App->physics->AddBody(map[23], 0);

	map[24].SetPos(198, 9, 13.5);
	map[24].size.x = 18;
	map[24].size.y = 18;
	map[24].size.z = 18;
	map[24].axis = false;
	map[24].color = White;
	App->physics->AddBody(map[24], 0);

	ball[0].SetPos(158, 12, 27);
	ball[0].radius = 12;
	ball[0].axis = false;
	ball[0].color = White;
	App->physics->AddBody(ball[0], 0);

	ball[1].SetPos(118, 12, 27);
	ball[1].radius = 12;
	ball[1].axis = false;
	ball[1].color = White;
	App->physics->AddBody(ball[1], 0);

	ball[2].SetPos(78, 12, 27);
	ball[2].radius = 12;
	ball[2].axis = false;
	ball[2].color = White;
	App->physics->AddBody(ball[2], 0);

	//grass
	grass[0].SetPos(65.5, 1.0, 324);
	grass[0].size.x = 5;
	grass[0].size.y = 0.4;
	grass[0].size.z = 260;
	grass[0].axis = false;
	grass[0].wire = false;
	grass[0].color = Yellow;
	physSensor = App->physics->AddBody(grass[0], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	grass[1].SetPos(51.5, 1.0, 273);
	grass[1].size.x = 5;
	grass[1].size.y = 0.4;
	grass[1].size.z = 100;
	grass[1].axis = false;
	grass[1].wire = false;
	grass[1].color = Yellow;
	physSensor = App->physics->AddBody(grass[1], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	grass[2].SetPos(24, 1.0, 418);
	grass[2].size.x = 40;
	grass[2].size.y = 0.4;
	grass[2].size.z = 192;
	grass[2].axis = false;
	grass[2].wire = false;
	grass[2].color = Yellow;
	physSensor = App->physics->AddBody(grass[2], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	grass[3].SetPos(439, 1.0, 455);
	grass[3].size.x = 89;
	grass[3].size.y = 0.4;
	grass[3].size.z = 20;
	grass[3].axis = false;
	grass[3].wire = false;
	grass[3].color = Yellow;
	physSensor = App->physics->AddBody(grass[3], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	grass[4].SetPos(475, 1.0, 410);
	grass[4].size.x = 89;
	grass[4].size.y = 0.4;
	grass[4].size.z = 20;
	grass[4].axis = false;
	grass[4].wire = false;
	grass[4].color = Yellow;
	physSensor = App->physics->AddBody(grass[4], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	grass[5].SetPos(109, 1.0, 45);
	grass[5].size.x = 170;
	grass[5].size.y = 0.4;
	grass[5].size.z = 10;
	grass[5].axis = false;
	grass[5].wire = false;
	grass[5].color = Yellow;
	physSensor = App->physics->AddBody(grass[5], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	//turbo
	turbo[0].SetPos(107, 0.8, 481.5);
	turbo[0].size.x = 6;
	turbo[0].size.y = 0.2;
	turbo[0].size.z = 52;
	turbo[0].axis = false;
	turbo[0].wire = false;
	turbo[0].color.Set(0, 255, 255);
	physSensor = App->physics->AddBody(turbo[0], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(3);

	turbo[1].SetPos(472, 0.8, 254.5);
	turbo[1].size.x = 76;
	turbo[1].size.y = 0.2;
	turbo[1].size.z = 6;
	turbo[1].axis = false;
	turbo[1].wire = false;
	turbo[1].color.Set(0, 255, 255);
	physSensor = App->physics->AddBody(turbo[1], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(3);

	turbo[2].SetPos(14, 0.8, 70);
	turbo[2].size.x = 23;
	turbo[2].size.y = 0.2;
	turbo[2].size.z = 6;
	turbo[2].axis = false;
	turbo[2].wire = false;
	turbo[2].color.Set(0, 255, 255);
	physSensor = App->physics->AddBody(turbo[2], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(3);

	//checkpoints
	checkpoints[0].SetPos(14, 2, 180);
	checkpoints[0].size.x = 16;
	checkpoints[0].size.y = 2;
	checkpoints[0].size.z = 0.5;
	checkpoints[0].axis = false;
	checkpoints[0].wire = true;
	checkpoints[0].color.Set(255, 255, 0);
	physSensor = App->physics->AddBody(checkpoints[0], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(4);

	checkpoints[1].SetPos(460, 2, 486);
	checkpoints[1].size.x = 0.5;
	checkpoints[1].size.y = 3;
	checkpoints[1].size.z = 42;
	checkpoints[1].axis = false;
	checkpoints[1].wire = false;
	checkpoints[1].color.Set(255, 255, 0);
	physSensor = App->physics->AddBody(checkpoints[1], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(5);

	checkpoints[2].SetPos(398, 2, 24.5);
	checkpoints[2].size.x = 0.5;
	checkpoints[2].size.y = 3;
	checkpoints[2].size.z = 52;
	checkpoints[2].axis = false;
	checkpoints[2].wire = true;
	checkpoints[2].color.Set(255, 255, 0);
	physSensor = App->physics->AddBody(checkpoints[2], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(6);

	//flags
	flag[0].SetPos(21, 20, 223);
	flag[0].size.x = 3;
	flag[0].size.y = 3;
	flag[0].size.z = 3;
	flag[0].axis = false;
	flag[0].color = Black;
	App->physics->AddBody(flag[0], 0);

	flag[1].SetPos(15, 20, 223);
	flag[1].size.x = 3;
	flag[1].size.y = 3;
	flag[1].size.z = 3;
	flag[1].axis = false;
	flag[1].color = Black;
	App->physics->AddBody(flag[1], 0);

	flag[2].SetPos(9, 20, 223);
	flag[2].size.x = 3;
	flag[2].size.y = 3;
	flag[2].size.z = 3;
	flag[2].axis = false;
	flag[2].color = Black;
	App->physics->AddBody(flag[2], 0);

	//ramps
	ramp[0].SetPos(275, 1, 473);
	ramp[0].SetRotation(20.0f, { 1,0,0 });
	ramp[0].size.x = 250;
	ramp[0].size.y = 2;
	ramp[0].size.z = 20;
	ramp[0].axis = false;
	ramp[0].color = White;
	App->physics->AddBody(ramp[0], 0);

	ramp[1].SetPos(275, 5, 465);
	ramp[1].SetRotation(40.0f, { 1,0,0 });
	ramp[1].size.x = 250.1;
	ramp[1].size.y = 2;
	ramp[1].size.z = 20;
	ramp[1].axis = false;
	ramp[1].color = White;
	App->physics->AddBody(ramp[1], 0);

	ramp[2].SetPos(275, 21, 454);
	ramp[2].SetRotation(80.0f, { 1,0,0 });
	ramp[2].size.x = 250.1;
	ramp[2].size.y = 2;
	ramp[2].size.z = 20;
	ramp[2].axis = false;
	ramp[2].color = White;
	App->physics->AddBody(ramp[2], 0);

	ramp[3].SetPos(275, 36, 454);
	ramp[3].SetRotation(100.0f, { 1,0,0 });
	ramp[3].size.x = 250;
	ramp[3].size.y = 2;
	ramp[3].size.z = 20;
	ramp[3].axis = false;
	ramp[3].color = White;
	App->physics->AddBody(ramp[3], 0);

	ramp[4].SetPos(275, 46, 459);
	ramp[4].SetRotation(120.0f, { 1,0,0 });
	ramp[4].size.x = 250.1;
	ramp[4].size.y = 2;
	ramp[4].size.z = 20;
	ramp[4].axis = false;
	ramp[4].color = White;
	App->physics->AddBody(ramp[4], 0);

	ramp[5].SetPos(275, 52, 465);
	ramp[5].SetRotation(140.0f, { 1,0,0 });
	ramp[5].size.x = 250;
	ramp[5].size.y = 2;
	ramp[5].size.z = 20;
	ramp[5].axis = false;
	ramp[5].color = White;
	App->physics->AddBody(ramp[5], 0);

	ramp[6].SetPos(275, 55, 471);
	ramp[6].SetRotation(160.0f, { 1,0,0 });
	ramp[6].size.x = 250.1;
	ramp[6].size.y = 2;
	ramp[6].size.z = 20;
	ramp[6].axis = false;
	ramp[6].color = White;
	App->physics->AddBody(ramp[6], 0);

	ramp[7].SetPos(275, 57, 479);
	ramp[7].SetRotation(180.0f, { 1,0,0 });
	ramp[7].size.x = 250;
	ramp[7].size.y = 2;
	ramp[7].size.z = 20;
	ramp[7].axis = false;
	ramp[7].color = White;
	App->physics->AddBody(ramp[7], 0);

	ramp[8].SetPos(275, 1, 491);
	ramp[8].SetRotation(-20.0f, { 1,0,0 });
	ramp[8].size.x = 250;
	ramp[8].size.y = 2;
	ramp[8].size.z = 20;
	ramp[8].axis = false;
	ramp[8].color = White;
	App->physics->AddBody(ramp[8], 0);

	ramp[9].SetPos(275, 5, 497);
	ramp[9].SetRotation(-40.0f, { 1,0,0 });
	ramp[9].size.x = 250.1;
	ramp[9].size.y = 2;
	ramp[9].size.z = 20;
	ramp[9].axis = false;
	ramp[9].color = White;
	App->physics->AddBody(ramp[9], 0);

	ramp[10].SetPos(275, 11, 503);
	ramp[10].SetRotation(-60.0f, { 1,0,0 });
	ramp[10].size.x = 250;
	ramp[10].size.y = 2;
	ramp[10].size.z = 20;
	ramp[10].axis = false;
	ramp[10].color = White;
	App->physics->AddBody(ramp[10], 0);

	ramp[11].SetPos(275, 21, 508);
	ramp[11].SetRotation(-80.0f, { 1,0,0 });
	ramp[11].size.x = 250.1;
	ramp[11].size.y = 2;
	ramp[11].size.z = 20;
	ramp[11].axis = false;
	ramp[11].color = White;
	App->physics->AddBody(ramp[11], 0);

	ramp[12].SetPos(275, 36, 508);
	ramp[12].SetRotation(-100.0f, { 1,0,0 });
	ramp[12].size.x = 250;
	ramp[12].size.y = 2;
	ramp[12].size.z = 20;
	ramp[12].axis = false;
	ramp[12].color = White;
	App->physics->AddBody(ramp[12], 0);

	ramp[13].SetPos(275, 46, 503);
	ramp[13].SetRotation(-120.0f, { 1,0,0 });
	ramp[13].size.x = 250.1;
	ramp[13].size.y = 2;
	ramp[13].size.z = 20;
	ramp[13].axis = false;
	ramp[13].color = White;
	App->physics->AddBody(ramp[13], 0);

	ramp[14].SetPos(275, 52, 497);
	ramp[14].SetRotation(-140.0f, { 1,0,0 });
	ramp[14].size.x = 250;
	ramp[14].size.y = 2;
	ramp[14].size.z = 20;
	ramp[14].axis = false;
	ramp[14].color = White;
	App->physics->AddBody(ramp[14], 0);

	ramp[15].SetPos(275, 55, 491);
	ramp[15].SetRotation(-160.0f, { 1,0,0 });
	ramp[15].size.x = 250.1;
	ramp[15].size.y = 2;
	ramp[15].size.z = 20;
	ramp[15].axis = false;
	ramp[15].color = White;
	App->physics->AddBody(ramp[15], 0);

	ramp[16].SetPos(275, 11, 459);
	ramp[16].SetRotation(60.0f, { 1,0,0 });
	ramp[16].size.x = 250;
	ramp[16].size.y = 2;
	ramp[16].size.z = 20;
	ramp[16].axis = false;
	ramp[16].color = White;
	App->physics->AddBody(ramp[16], 0);

	ramp[17].SetPos(230, 0, 482);
	ramp[17].size.x = 3;
	ramp[17].size.y = 40;
	ramp[17].size.z = 50;
	ramp[17].axis = false;
	ramp[17].color = White;
	App->physics->AddBody(ramp[17], 0);

	ramp[18].SetPos(295, 15, 500);
	ramp[18].size.x = 3;
	ramp[18].size.y = 80;
	ramp[18].size.z = 50;
	ramp[18].axis = false;
	ramp[18].color = White;
	App->physics->AddBody(ramp[18], 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//ground->Render();

	for (int i = 0; i < 4; i++)
	{
		wall[i].Render();
	}

	for (int i = 0; i < 4; i++)
	{
		borders[i].Render();
	}

	for (int i = 0; i < 25; i++)
	{
		map[i].Render();
	}

	for (int i = 0; i < 5; i++)
	{
		ball[i].Render();
	}

	for (int i = 0; i < 7; i++)
	{
		grass[i].Render();
	}

	for (int i = 0; i < 5; i++)
	{
		turbo[i].Render();
	}

	for (int i = 0; i < 4; i++)
	{
		checkpoints[i].Render();
	}

	for (int i = 0; i < 3; i++)
	{
		flag[i].Render();
	}

	for (int i = 0; i < 20; i++)
	{
		ramp[i].Render();
	}

	if (frames % 60 == 0 && timer > 0 && App->camera->finish == false)
	{
		if (App->player->turboTimer > 0)
		{
			App->player->turboTimer--;
		}
		App->player->turboSound = true;
		timer--;
	}
	frames++;

	secondsSinceInit = INITIAL_TIME - timer;

	if (secondsSinceInit == 2 && starting == true)
	{
		flag[0].color = Red;
	}
	else if (secondsSinceInit == 3 && starting == true)
	{
		flag[1].color = Red;
	}
	else if (secondsSinceInit == 4 && starting == true)
	{
		flag[2].color = Red;
	}
	else if (secondsSinceInit == 5 && starting == true)
	{
		for (int i = 0; i < 3; i++)
		{
			flag[i].color = Green;
			starting = false;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

