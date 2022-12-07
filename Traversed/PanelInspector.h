#ifndef __PANEL_INSPECTOR_H_
#define __PANEL_INSPECTOR_H_

#include "UiPanel.h"

class GameObject;
struct SceneProperties;

class PanelInspector : public UiPanel
{
public:
	PanelInspector(bool enabled = false);
	~PanelInspector() override;

	void Start() override;

	void Update() override;

private:
	GameObject* IterateGameObject(GameObject* go);

private:
	SceneProperties* sceneInstance = nullptr;
};

#endif
