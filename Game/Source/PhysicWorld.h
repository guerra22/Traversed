#pragma once
#include "PhysicBody.h"
#include "List.h"

class PhysicWorld
{
public:
	PhysicWorld(fPoint gravity);

	~PhysicWorld();

	void Update(float simulationTime);

	bool CheckCollision(PhysicBody* body);

	void AddPhysicBody(PhysicBody* body);

	void DelPhysicBody(PhysicBody* body);

	void BoxColBox(PhysicBody& b1, PhysicBody& b2);

	void CircleColCircle(PhysicBody& b1, PhysicBody& b2);

	void BoxColCircle(PhysicBody& b1, PhysicBody& b2);

	void ResolveColForce(PhysicBody& b1, PhysicBody& b2, fPoint colPoint);

	// Detect collision point in 2 shapes
	fPoint CollisionPoint(PhysicBody& b1, PhysicBody& b2);

	// Dectet center of shape -> collision point(any point) vector
	fPoint CollisionDir(PhysicBody& b1, fPoint colPoint);

public:

	fPoint gravity;

	float density = 1.0f;
public:

	bool gravityOn = true;
	bool buoyancyOn = true;
	bool hydrioDragOn = true;
	bool aeroDragOn = true;
	bool clippingOn = true;
	bool frictioOn = true;

	List<PhysicBody*> physicBodies;
};