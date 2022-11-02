#include "Globals.h"
#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(Application* app, GameObject* owner) : Component(app, owner, COMPONENT_TYPES::MESH, "Mesh")
{

}

ComponentMesh::~ComponentMesh()
{

}

update_status ComponentMesh::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ComponentMesh::CleanUp()
{
	bool ret = true;


	return ret;
}

void ComponentMesh::SetMesh(VertexData mesh)
{
	this->mesh = mesh;
}

VertexData ComponentMesh::GetMesh()
{
	return mesh;
}
