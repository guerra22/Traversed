#ifndef __PANEL_HIERARCHY_H_
#define __PANEL_HIERARCHY_H_

#include "UiPanel.h"

struct SceneProperties;
class GameObject;

class PanelHierarchy : public UiPanel
{
public:
	PanelHierarchy(bool enabled = false);
	~PanelHierarchy() override;

	void Start() override;

	void Update() override;

private:
	GameObject* DisplayGameObject(GameObject* go);

	void RightClickMenuContextItem(GameObject* go = nullptr);
	void RightClickMenuContextWindow();
	void RightClickMenuContent(GameObject* go);

	void GetSelectedNode(GameObject* go);

	inline bool CleanSelected(GameObject* go);

private:
	SceneProperties* sceneInstance = nullptr;
	GameObject* hoverGO = nullptr;
	GameObject* dropGO = nullptr;

	bool cleanSelected = false;
	bool winHover = false;
};

#endif

