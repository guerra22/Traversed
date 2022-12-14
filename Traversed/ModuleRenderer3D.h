#ifndef __MODULERENDERER3D_H__
#define __MODULERENDERER3D_H__

#include "Module.h"
#include "Light.h"

#define MAX_LIGHTS 8

#include "External/SDL/include/SDL.h"

class Renderer;

struct RenderProperties
{
public:
	bool vsync = false;
	bool wireframe = false;
	bool depthTest = false;
	bool cullFace = false;
	bool lighting = false;
	bool fog = false;
	bool colorMaterial = false;
	bool texture2D = false;

	Light* worldLight;

	RenderProperties();

	static RenderProperties* Instance();

	static void Delete();

	void ToggleVsync();
	void ToggleWireframe();
	void ToggleDepthTest();
	void ToggleCullFace();
	void ToggleLighting();
	void ToggleFog();
	void ToggleColorMaterial();
	void ToggleTexture2D();

private:
	static RenderProperties* rProps;

};

class WindowProperties;
struct CameraProperties;
struct SceneProperties;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	UpdateStatus PreUpdate();
	UpdateStatus PostUpdate();
	bool CleanUp();

	void SaveSettingsData(pugi::xml_node& save) override;

	void LoadSettingsData(pugi::xml_node& load) override;

	void OnResize(int width, int height);

public:
	SDL_GLContext GetGLContext() { return context; }

public:

	//Light lights[MAX_LIGHTS];
	float3x3 NormalMatrix;
	float4x4 ModelMatrix, ViewMatrix;
	//ProjectionMatrix;

private:
	SDL_GLContext context;

	RenderProperties* rProps = nullptr;
	WindowProperties* wProps = nullptr;
	CameraProperties* cProps = nullptr;
	SceneProperties* sProps = nullptr;
};

#endif // !__MODULERENDERER3D_H__