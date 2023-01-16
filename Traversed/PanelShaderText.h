#pragma once
#include "UiPanel.h"

class ResourceShader;
struct ResourceProperties;

class PanelShaderText : public UiPanel
{
public:
	PanelShaderText(bool enabled = false);
	~PanelShaderText() override;

	void Start() override;
	void Update() override;

	void SetResource(std::string resourceUuid);

private:
	ResourceShader* currentResource = nullptr;

	ResourceProperties* resInstance = nullptr;

};
