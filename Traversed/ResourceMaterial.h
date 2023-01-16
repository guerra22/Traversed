#pragma once
#include "Resource.h"

class Material;
class ComponentMaterial;

class ResourceMaterial : public Resource
{
public:
	ResourceMaterial(std::string uuid);
	~ResourceMaterial();

	nlohmann::JsonData SaveUnique(nlohmann::JsonData data) override;
	void LoadUnique(nlohmann::JsonData data) override;

	void CleanInstance() override;
	void PlanDelete() override;

	void ImportToLibrary(Material* material = nullptr);
	void ImportFromLibrary(ComponentMaterial* comp);

	Material* GetMaterial() { return material; }
	void SetMaterialToComp(ComponentMaterial* comp);
	void RemoveMaterialToComp(ComponentMaterial* comp);

private:
	Material* material = nullptr;
	std::vector<ComponentMaterial*>* compRef = nullptr;
};