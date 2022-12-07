#include "ComponentTransform.h"
#include "GameObject.h"

#include "External/MathGeo/include/MathGeoLib.h"
#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_impl_sdl.h"
#include "External/ImGui/imgui_impl_opengl3.h"

ComponentTransform::ComponentTransform(GameObject* owner, std::string uuid) : Component(owner, uuid)
{
	this->type = CO_TYPE::TRANSFORM;
	position = float3(.0f, .0f, .0f);
	//rotation = Quat::identity;
	rotation = float3(.0f, .0f, .0f);
	localScale = float3(1.0f, 1.0f, 1.0f);
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::Init()
{
	
}

void ComponentTransform::Update()
{

}

void ComponentTransform::UpdateGUI()
{
	ImGui::NewLine();

	ImGui::DragFloat3("Position", &position[0], 0.25f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoInput);
	ImGui::DragFloat3("Rotation", &rotation[0]);
	ImGui::DragFloat3("Scale", &localScale[0], 0.25f, 0.0f, 0.0f, "%.2f");
}

float4x4 ComponentTransform::GetWorldMatrix()
{
	float4x4 parentFloat = float4x4::identity;
	if (owner->parent != nullptr)
	{
		ComponentTransform* parentTransform = owner->parent->GetComponent<ComponentTransform>(TRANSFORM);
		if (parentTransform != nullptr)
		{
			parentFloat = parentTransform->GetWorldMatrix();
		}
	}

	math::Quat q = Quat::FromEulerXYZ(math::DegToRad(rotation.x), math::DegToRad(rotation.y), math::DegToRad(rotation.z));
	float4x4 toReturn = float4x4::FromTRS(position, q.ToFloat4x4(), localScale);
	toReturn.Transpose();
	toReturn = toReturn * parentFloat;
	return toReturn;
}

float4x4 ComponentTransform::GetLocalMatrix()
{
	math::Quat q = Quat::FromEulerXYZ(math::DegToRad(rotation.x), math::DegToRad(rotation.y), math::DegToRad(rotation.z));
	float4x4 toReturn = float4x4::FromTRS(position, q.ToFloat4x4(), localScale);

	toReturn.Transpose();

	return toReturn;
}

void ComponentTransform::SetWorldMatrix(float4x4 matrix)
{
	//if (owner->parent != nullptr)
	math::Quat q;
	matrix.Decompose(position, q, localScale);

	rotation = q.ToEulerXYX();
	rotation.x = math::RadToDeg(rotation.x);
	rotation.y = math::RadToDeg(rotation.y);
	rotation.z = math::RadToDeg(rotation.z);
}

Quat ComponentTransform::GetRotationAsQuat()
{
	return Quat::FromEulerXYZ(math::DegToRad(rotation.x), math::DegToRad(rotation.y), math::DegToRad(rotation.z));
}

#pragma region Save/Load
nlohmann::ordered_json ComponentTransform::SaveUnique(nlohmann::JsonData data)
{
	data.SetFloat3("Position", position);
	data.SetFloat3("Rotation", rotation);
	data.SetFloat3("Scale", localScale);

	return data.data;
}

void ComponentTransform::LoadUnique(nlohmann::JsonData data)
{
	this->position = data.GetFloat3("Position");
	this->rotation = data.GetFloat3("Rotation");
	this->localScale = data.GetFloat3("Scale");
}

#pragma endregion Save & Load