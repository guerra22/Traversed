#ifndef __PANEL_SCENE_H_
#define __PANEL_SCENE_H_

#include "UiPanel.h"
#include "Renderer.h"

struct CameraProperties;

class PanelScene : public UiPanel
{
public:
	PanelScene(bool enabled = false);
	~PanelScene();

	void Update() override;

	void Start() override;

private:
	void RenderSpace();

private:
	ImVec2 segmentSize;

	CameraProperties* camInstance = nullptr;
};
#endif