#ifndef __PANEL_INSPECTOR_H_
#define __PANEL_INSPECTOR_H_

#include "UiPanel.h"
#include "GameObject.h"

class PanelInspector : public UiPanel
{
public:
	PanelInspector(Application* app);
	virtual ~PanelInspector();

	GameObject* GetSelectedGameObject();
	void DrawInfoOfGameObject(GameObject* game_object);
	void DrawGameObjectComponents();
	void DrawTransformComponent();
	void DrawMeshComponent();
	void DrawMaterialComponent();
	void Draw() override;

	GameObject* selectedGameObject;

private:
};

#endif
