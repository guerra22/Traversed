#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "External/SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	void SetResizable(bool resizable);

	void SetFullDesktop(bool fullDesktop);

	void SetFullscreen(bool fullscreen);

	void SetWidth(int x);

	void SetHeight(int y);

	void Vsync(bool vsync);

	void SetBrightness(float brightness);

	void SetBorderless(bool borderless);

	bool LoadConfig(JsonParser& node) override;
	bool SaveConfig(JsonParser& node) const override;

public:
	bool fullscreen = false;
	bool resizable = false;
	bool screenBorderless = false;
	int screenWidth;
	int screenHeight;
	bool vsync = false;
	float screenBrightness;

	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__