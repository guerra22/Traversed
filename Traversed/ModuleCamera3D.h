#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

#define ZOOM_SPEED 2.0f

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);

	void Zoom();
	void SetZoomSpeed(const float& zoom_speed);
	float GetZoomSpeed() const;

	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

	bool FocusObject;

	float zoomSpeed;
private:

	mat4x4 ViewMatrix, ViewMatrixInverse;
};