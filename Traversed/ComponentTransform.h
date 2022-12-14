#ifndef _COMPONENTTRANSFORM_H
#define _COMPONENTTRANSFORM_H

#include "Component.h"

#include "External/MathGeo/include/Math/float4x4.h"
#include "External/MathGeo/include/Math/float3.h"
#include "External/MathGeo/include/Math/Quat.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* owner, std::string uuid);
	~ComponentTransform() override;

	void Init() override;
	void Update() override;

	void UpdateGUI() override;

	nlohmann::ordered_json SaveUnique(nlohmann::JsonData data) override;
	void LoadUnique(nlohmann::JsonData data) override;

	float4x4 GetWorldMatrix();
	float4x4 GetLocalMatrix();

	void SetWorldMatrix(float4x4 matrix);

	Quat GetRotationAsQuat();
public:

	float4x4 localTransform;
	float4x4 globalTransform;

	float3 position;
	//Quat rotation;
	float3 rotation;
	float3 localScale;
};

#endif