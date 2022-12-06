#ifndef __PANEL_GAME_H_
#define __PANEL_GAME_H_

#include "UiPanel.h"

struct CameraProperties;
class ComponentCamera;

class PanelGame : public UiPanel
{
public:
	PanelGame(bool enabled = false);
	~PanelGame();

	void Start() override;

	void Update() override;

private:
	void RenderSpace();

	void LookForCamera();

private:
	ImVec2 segmentSize;

	CameraProperties* camInstance = nullptr;

	ComponentCamera* mainCamera = nullptr;
};

#endif