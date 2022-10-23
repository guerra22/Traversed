#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct Gl_Attributes
{
	bool Depth_test = true;
	bool Cull_Face = true;
	bool Lightning = true;
	bool Color_Materials = true;
	bool Front = true;
	bool AmbientOclussion = true;
	bool Wireframe = false;
};

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	bool LoadConfig(JsonParser& node) override;
	bool SaveConfig(JsonParser& node) const override;

public:
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	Gl_Attributes atributes;
};