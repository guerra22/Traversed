#ifndef _COMPONENTCAMERA_H
#define _COMPONENTCAMERA_H

#include "Component.h"

#include "Camera.h"

class CameraProperties;

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* owner);
	~ComponentCamera() override;

	void Init() override;
	void Update() override;

	void UpdateGUI() override;

public:
	Camera camera;

	bool isMainCamera;

private:
	CameraProperties* camInstance = nullptr;
};

#endif