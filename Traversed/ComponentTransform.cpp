#include "Application.h"
#include "Module.h"
#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(Application* app, GameObject* owner) : Component(app, owner, COMPONENT_TYPES::TRANSFORM, "Transform")
{

}

ComponentTransform::~ComponentTransform()
{

}

update_status ComponentTransform::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ComponentTransform::CleanUp()
{
	bool ret = true;

	return ret;
}

void ComponentTransform::Transform()
{
	//Aqui poner todo lo que tenga que ver con rotación y posicion y todo
}
float3 ComponentTransform::GetPosition() const
{
	return position;
}

float3 ComponentTransform::GetRotation() const
{
	return euler_rotation;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}

void ComponentTransform::SetPosition(const float3& position)
{
	this->position = position;

}

void ComponentTransform::SetRotation(const float3& rotation)
{
	euler_rotation = rotation;

	this->rotation.RotateX(euler_rotation.x);
	this->rotation.RotateY(euler_rotation.y);
	this->rotation.RotateZ(euler_rotation.z);

}

void ComponentTransform::SetScale(const float3& scale)
{
	this->scale = scale;

}