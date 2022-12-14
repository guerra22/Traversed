#pragma once

#include "External/MathGeo/include/MathGeoLib.h"
#include "External/MathGeo/include/Math/float2.h"
#include "External/MathGeo/include/Geometry/AABB.h"

class Renderer;

class Camera
{
public:
	Camera();
	~Camera();

	void Look(const float3& Position, const float3& Reference, bool RotateAroundReference);
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);

	//Quat GetRotationQuat();

	float* GetViewMatrix();
	float* GetProjectionMatrix();

	void SetRenderer(float2 size);

	bool ContainsBBox(AABB& bBox);

	LineSegment ScreenPointToRay(float2 screenPos);

	void SetAspectRatio(float aspectRatio);

public:
	float4x4 ProjectionMatrix;
	float4x4 ViewMatrix;

	float3 X, Y, Z;
	float3 Position;
	float3 Reference;

	Frustum frustum;

	Renderer* renderer = nullptr;
};

