#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Window";
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOGGING("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOGGING("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOGGING("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOGGING("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::SetResizable(bool resizable)
{

}

void ModuleWindow::SetBorderless(bool borderless)
{
	if (fullscreen == false)
	{
		SDL_SetWindowBordered(window, (SDL_bool)!borderless);
	}
}

void ModuleWindow::SetFullscreen(bool fullscreen)
{
	SDL_SetWindowFullscreen(window, fullscreen);
}

void ModuleWindow::SetWidth(int x)
{
	SDL_SetWindowSize(window, x, screen_surface->h);
	App->renderer3D->OnResize(x, screen_surface->h);
	screen_surface->w = x;
}

void ModuleWindow::SetHeight(int y)
{
	SDL_SetWindowSize(window, screen_surface->w, y);
	App->renderer3D->OnResize(screen_surface->w, y);
	screen_surface->h = y;
}

void ModuleWindow::Vsync(bool vsync)
{
	vsync = SDL_HINT_RENDER_VSYNC;
}

void ModuleWindow::SetBrightness(float brightness)
{
	int result = SDL_SetWindowBrightness(window, brightness);

	if (result != 0)
	{
		LOGGING("Setting Brightness Value");
	}
}

bool ModuleWindow::LoadConfig(JsonParser& node)
{
	screenBrightness = node.GetJsonNumber("brightness");
	SetBrightness(screenBrightness);
	vsync = node.GetJsonBool("vsync");
	fullscreen = node.GetJsonBool("fullscreen");
	SetFullscreen(fullscreen);
	screenBorderless = node.GetJsonBool("borderless");
	SetBorderless(screenBorderless);
	resizable = node.GetJsonBool("resizable");
	SetResizable(resizable);
	screenWidth = node.GetJsonNumber("screenwidth");
	SetWidth(screenWidth);
	screenHeight = node.GetJsonNumber("screenheight");
	SetHeight(screenHeight);

	return true;
}

bool ModuleWindow::SaveConfig(JsonParser& node) const
{
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "brightness", screenBrightness);
	node.SetNewJsonBool(node.ValueToObject(node.GetRootValue()), "fullscreen", fullscreen);
	node.SetNewJsonBool(node.ValueToObject(node.GetRootValue()), "borderless", screenBorderless);
	node.SetNewJsonBool(node.ValueToObject(node.GetRootValue()), "resizable", resizable);
	node.SetNewJsonBool(node.ValueToObject(node.GetRootValue()), "vsync", vsync);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "screenwidth", screenWidth);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "screenheight", screenHeight);

	return true;
}