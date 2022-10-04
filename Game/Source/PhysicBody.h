#pragma once
#include "Point.h"
#include "List.h"
#include "Globals.h"

enum class BodyType
{
	STATIC,
	DYNAMIC,
	KINEMATIC,
	WATER,
};

enum class ShapeType
{
	CIRCLE,
	RECT,
};

class PhysicBody
{
public:
	// Position
	fPoint position = { 0.0, 0.0 };
	fPoint lastPosition = { 0.0,0.0 };

	//Properties
	float restitution = 0.0f;
	float friction = 0.0f;
	float coefficient = 0.0f;
	float hydrodynamic = 0.3f;
	float mass = 1.0f;
	fPoint velocity = { 0.0f, 0.0f };
	fPoint acceleration = { 0.0, 0.0 };
	float rotation = 0.0f;
	float gravityScale = 1.0f;
	float width = 1.0f;
	float height = 1.0f;
	float radius = 1.0f;

	BodyType type = BodyType::STATIC;
	ShapeType shape = ShapeType::RECT;

	float maximumVelocity = 1000.0f;

	fPoint totalForce = { 0.0, 0.0 };
	fPoint additionalForce = { 0.0, 0.0 };

	List<PhysicBody*> colList;

public:
	PhysicBody();

	~PhysicBody();

	PhysicBody(iPoint pos, BodyType type, float width, float height);

	PhysicBody(iPoint pos, BodyType type, float radius);

	void OnCollisionEnter(PhysicBody* col);

	void OnCollisionStay(PhysicBody* col);

	void OnCollisionExit(PhysicBody* col);

	void AddForceToCenter(fPoint force);

	fPoint GetLinearVelocity()
	{
		return velocity;
	}
	void SetLinearVelocity(fPoint velocity)
	{
		this->velocity = velocity;
	}

private:

	void ResetForces();

	friend class PhysicWorld;
};