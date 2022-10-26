#include "Application.h"
#include "Module.h"
#include "ModuleHardware.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleFileSystem.h"
#include "ModuleFBXLoader.h"

#include "Resource.h"

Application::Application()
{
	window = new ModuleWindow(this);
	hardware = new ModuleHardware(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	ui = new ModuleUI(this);
	sceneintro = new ModuleSceneIntro(this);
	filesystem = new ModuleFileSystem(this, RESOURCES_FOLDER);
	loader = new ModuleFBXLoader(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(hardware);
	AddModule(camera);
	AddModule(input);
	
	// Scenes
	AddModule(sceneintro);
	AddModule(loader);
	AddModule(ui);

	// Renderer last!
	AddModule(renderer3D);

	frames = 0;
	last_frame_ms = -1;
	last_fps = -1;
	capped_ms = 1000 / 60;
	fps_counter = 0;

	loadRequest = false;
	saveRequest = false;
}

Application::~Application()
{
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		delete item._Ptr->_Myval;
		item++;
	}

	RELEASE(filesystem);
	list_modules.clear();
}

bool Application::Init()
{
	//bool ret = true;

	//filesystem->Load(SETTINGS_FOLDER "config.json", &buffer);

	//std::list<Module*>::iterator item = list_modules.begin();

	//// Call Init() in all modules

	//while (item != list_modules.end() && ret == true)
	//{
	//	ret = item._Ptr->_Myval->Init();

	//	item++;
	//}

	//// After all Init calls we call Start() in all modules
	//LOGGING("Application Start --------------");
	//item = list_modules.begin();

	//while (item != list_modules.end() && ret == true)
	//{
	//	ret = item._Ptr->_Myval->Start();

	//	item++;
	//}
	//
	//return ret;

	bool ret = true;

	char* buffer = nullptr;
	filesystem->Load(SETTINGS_FOLDER "config.json", &buffer);

	if (buffer != nullptr)
	{
		JsonParser jsonFile((const char*)buffer);
		jsonFile.ValueToObject(jsonFile.GetRootValue());

		std::list<Module*>::iterator item;

		RELEASE_ARRAY(buffer);
	}

	std::list<Module*>::iterator item;
	
	for (item = list_modules.begin(); item != list_modules.end() && ret; ++item)
	{
		ret = (*item)->Init();
		ret = (*item)->Start();
	}

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	if (loadRequest) LoadConfig();
	if (saveRequest) SaveConfig();

	// Recap on framecount and fps
	++frames;
	++fps_counter;

	if (fps_timer.Read() >= 1000)
	{
		last_fps = fps_counter;
		fps_counter = 0;
		fps_timer.Start();
	}

	last_frame_ms = ms_timer.Read();

	// cap fps
	if (capped_ms > 0 && (last_frame_ms < capped_ms))
		SDL_Delay(capped_ms - last_frame_ms);

	// notify the editor
	ui->LogFPS((float)last_fps, (float)last_frame_ms);
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::list<Module*>::iterator item = list_modules.begin();
	
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PreUpdate(dt);

		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->Update(dt);

		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PostUpdate(dt);

		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::iterator item = list_modules.end();
	item--;

	while (item != list_modules.begin() && ret == true)
	{
		ret = item._Ptr->_Myval->CleanUp();
		item--;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::SaveConfig()
{
	LOGGING("Saving configuration");
	JsonParser jsonFile;

	// Call Init() in all modules
	std::list<Module*>::iterator item;

	for (item = list_modules.begin(); item != list_modules.end(); ++item)
	{
		(*item)->SaveConfig(jsonFile.SetChild(jsonFile.GetRootValue(), (*item)->name));
	}

	char* buf;
	uint size = jsonFile.Save(&buf);

	if (filesystem->Save(SETTINGS_FOLDER CONFIG_FILENAME, buf, size) > 0)
	{
		LOGGING("Saved Engine Preferences");
	}

	RELEASE_ARRAY(buf);

	//jsonFile.SerializeFile(root, CONFIG_FILENAME);
	saveRequest = false;
}

void Application::LoadConfig()
{
	LOGGING("Loading configuration");

	char* buffer = nullptr;

	filesystem->Load(SETTINGS_FOLDER "config.json", &buffer);

	if (buffer != nullptr)
	{
		JsonParser jsonFile((const char*)buffer);
		jsonFile.ValueToObject(jsonFile.GetRootValue());

		std::list<Module*>::iterator item;

		for (item = list_modules.begin(); item != list_modules.end(); ++item)
		{
			(*item)->LoadConfig(jsonFile.GetChild(jsonFile.GetRootValue(), (*item)->name));
		}

		RELEASE_ARRAY(buffer);
	}

	loadRequest = false;
}

uint Application::GetFramerateLimit() const
{
	if (capped_ms > 0)
		return (uint)((1.0f / (float)capped_ms) * 1000.0f);
	else
		return 0;
}

void Application::SetFramerateLimit(uint max_framerate)
{
	if (max_framerate > 0)
		capped_ms = 1000 / max_framerate;
	else
		capped_ms = 0;
}

void Application::RequestBrowser(const char* url) const
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}