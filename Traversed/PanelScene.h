#ifndef __PANEL_SCENE_H_
#define __PANEL_SCENE_H_

#include "UiPanel.h"
#include "Renderer.h"

struct CameraProperties;
struct SceneProperties;
struct EditorProperties;

class Camera;
class GameObject;

class PanelScene : public UiPanel
{
public:
	PanelScene(bool enabled = false);
	~PanelScene();

	void Update() override;

	void Start() override;

private:
	void RenderSpace();
	void Guizmo(Camera& cam, GameObject* go);

private:
	ImVec2 segmentSize;

	CameraProperties* camInstance = nullptr;
	SceneProperties* sceneInstance = nullptr;
	EditorProperties* editorInstance = nullptr;
};
#endif