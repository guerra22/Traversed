#include "PhysicBody.h"

PhysicBody::PhysicBody()
{

}

PhysicBody::~PhysicBody()
{
}

PhysicBody::PhysicBody(iPoint pos, BodyType type, float width, float height)
{
	this->position.x = pos.x;
	this->position.y = pos.y;
	this->type = type;
	this->shape = ShapeType::RECT;
	this->width = width;
	this->height = height;
}

PhysicBody::PhysicBody(iPoint pos, BodyType type, float radius)
{
	this->position.x = pos.x;
	this->position.y = pos.y;
	this->type = type;
	this->shape = ShapeType::CIRCLE;
	this->radius = radius;
}


void PhysicBody::OnCollisionEnter(PhysicBody* col)
{
	
}

void PhysicBody::OnCollisionStay(PhysicBody* col)
{
	
}

void PhysicBody::OnCollisionExit(PhysicBody* col)
{
	
}


void PhysicBody::AddForceToCenter(fPoint force)
{
	additionalForce += force;
}

void PhysicBody::ResetForces()
{
	acceleration = totalForce = { 0,0 };
}