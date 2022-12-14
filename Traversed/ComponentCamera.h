#ifndef _COMPONENTCAMERA_H
#define _COMPONENTCAMERA_H

#include "Component.h"

#include "Camera.h"

class CameraProperties;
class DebugMesh;

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* owner, std::string uuid);
	~ComponentCamera() override;

	void Init() override;
	void Update() override;

	void UpdateGUI() override;

	nlohmann::ordered_json SaveUnique(nlohmann::JsonData data) override;
	void LoadUnique(nlohmann::JsonData data) override;

private:
	void SetFustrumBox();

public:
	Camera camera;

	bool isMainCamera;

private:
	CameraProperties* camInstance = nullptr;

	int numOfMeshes;

	DebugMesh* frustumMesh;
};

#endif