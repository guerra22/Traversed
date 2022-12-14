#ifndef __MESH_H__
#define __MESH_H__

#include "Globals.h"

#include "External/MathGeo/include/Math/float2.h"
#include "External/MathGeo/include/Math/float3.h"
#include "Color.h"
#include <vector>

enum PrimitiveTypes
{
	CUBE,
	SPHERE,
	PYRAMID,
	CYLINDER
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void InitMesh();

	void Init(PrimitiveTypes primitiveType, float3 position = { 0, 0, 0 }, float3 size = { 1, 1, 1 });

	std::vector<float3> GetVertex() { return vertex; };
	std::vector<uint> GetIndex() { return index; };
	//std::vector<float2> GetTexcoords() { return texcoords; }

private:
	void Cube();
	void Sphere();
	void Pyramid();
	void Cylinder();

	float3 size = { 1, 1, 1 };
	float3 position = { 0, 0, 0 };

public:
	std::vector<float3> vertex;
	std::vector<uint> index;
	//std::vector<float2> texcoords;

};

#endif // !__PRIMITIVE_H__