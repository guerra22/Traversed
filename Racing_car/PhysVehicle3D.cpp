#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = White;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());
	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	chassis.color = Orange;

	Cube bridge(info.bridge_size.x, info.bridge_size.y, info.bridge_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&bridge.transform);
	btVector3 b_offset(info.bridge_offset.x, info.bridge_offset.y, info.bridge_offset.z);
	b_offset = b_offset.rotate(q.getAxis(), q.getAngle());
	bridge.transform.M[12] += b_offset.getX();
	bridge.transform.M[13] += b_offset.getY();
	bridge.transform.M[14] += b_offset.getZ();
	bridge.color = Orange;

	Cube front_wing(info.front_wing_size.x, info.front_wing_size.y, info.front_wing_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front_wing.transform);
	btVector3 fw_offset(info.front_wing_offset.x, info.front_wing_offset.y, info.front_wing_offset.z);
	fw_offset = fw_offset.rotate(q.getAxis(), q.getAngle());
	front_wing.transform.M[12] += fw_offset.getX();
	front_wing.transform.M[13] += fw_offset.getY();
	front_wing.transform.M[14] += fw_offset.getZ();
	front_wing.color = Blue;

	Cube rear_wing(info.rear_wing_size.x, info.rear_wing_size.y, info.rear_wing_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&rear_wing.transform);
	btVector3 rw_offset(info.rear_wing_offset.x, info.rear_wing_offset.y, info.rear_wing_offset.z);
	rw_offset = rw_offset.rotate(q.getAxis(), q.getAngle());
	rear_wing.transform.M[12] += rw_offset.getX();
	rear_wing.transform.M[13] += rw_offset.getY();
	rear_wing.transform.M[14] += rw_offset.getZ();
	rear_wing.color = Blue;

	Cube right_wing(info.vertical_wing_size.x, info.vertical_wing_size.y, info.vertical_wing_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&right_wing.transform);
	btVector3 vw_offset(info.vertical_wing_offset.x, info.vertical_wing_offset.y, info.vertical_wing_offset.z);
	vw_offset = vw_offset.rotate(q.getAxis(), q.getAngle());
	right_wing.transform.M[12] += vw_offset.getX();
	right_wing.transform.M[13] += vw_offset.getY();
	right_wing.transform.M[14] += vw_offset.getZ();
	right_wing.color = Blue;

	Cube left_wing = right_wing;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&left_wing.transform);
	btVector3 lw_offset(-info.vertical_wing_offset.x, info.vertical_wing_offset.y, info.vertical_wing_offset.z);
	lw_offset = lw_offset.rotate(q.getAxis(), q.getAngle());
	left_wing.transform.M[12] += lw_offset.getX();
	left_wing.transform.M[13] += lw_offset.getY();
	left_wing.transform.M[14] += lw_offset.getZ();
	left_wing.color = Blue;

	Cube upper(info.upper_size.x, info.upper_size.y, info.upper_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&upper.transform);
	btVector3 u_offset(info.upper_offset.x, info.upper_offset.y, info.upper_offset.z);
	u_offset = u_offset.rotate(q.getAxis(), q.getAngle());
	upper.transform.M[12] += u_offset.getX();
	upper.transform.M[13] += u_offset.getY();
	upper.transform.M[14] += u_offset.getZ();

	chassis.Render();
	bridge.Render();
	front_wing.Render();
	rear_wing.Render();
	right_wing.Render();
	left_wing.Render();
	upper.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}