#include "PanelShaderText.h"

#include "ModuleResources.h"
#include "ShaderManager.h"

PanelShaderText::PanelShaderText(bool enabled) : UiPanel(enabled)
{
	name = "Shader Text Editor";
}

PanelShaderText::~PanelShaderText()
{

}

void PanelShaderText::Start()
{
	resInstance = ResourceProperties::Instance();
}

void PanelShaderText::Update()
{
	if (ImGui::Begin(name.c_str()))
	{
		std::string aux = currentResource->GetName();
		ImGui::Text(aux.c_str());
	}
	ImGui::End();
}

void PanelShaderText::SetResource(std::string resourceUuid)
{
	this->currentResource = (ResourceShader*)ResourceProperties::Instance()->resources.at(resourceUuid);
}