#ifndef _ComponentTransform_H
#define _ComponentTransform_H

#include "Module.h"
#include "GameObject.h"
#include "External/MathGeo/include/Math/float4x4.h"
#include "External/MathGeo/include/Math/float3.h"
#include <string>

class GameObject;

class ComponentTransform : public Component
{
public:
	ComponentTransform(Application* app, GameObject* owner);
	virtual ~ComponentTransform();

	update_status Update(float dt) override;
	bool CleanUp() override;

	void Transform();

	float3 GetPosition() const;
	float3 GetRotation() const;
	float3 GetScale() const;

	void SetPosition(const float3& position);
	void SetRotation(const float3& rotation);
	void SetScale(const float3& scale);

public:

	float4x4	matrix;

	float3		position = { 0,0,0 };
	float4x4	rotation;
	float3		scale = { 0,0,0 };

	float3		euler_rotation = { 0,0,0 };



private:
	const char* name;
	bool		is_active;
};


#endif