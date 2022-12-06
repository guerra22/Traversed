#ifndef _COMPONENTCAMERA_H
#define _COMPONENTCAMERA_H

#include "Component.h"

#include "Camera.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* owner);
	~ComponentCamera() override;

	void Init() override;
	void Update() override;

private:
	Camera camera;
};

#endif