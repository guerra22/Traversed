#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

#include "External/PugiXml/src/pugixml.hpp"

class Application;

class Module
{
private :
	bool enabled = false;;

public:
	std::string name = "NONAME";

	Application* App = nullptr;

	pugi::xml_node config;

public:
	Module();

	Module(Application* parent, bool start_enabled = true) : App(parent), enabled(start_enabled)
	{}

	virtual ~Module()
	{}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}
	
	virtual UpdateStatus PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual UpdateStatus Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual UpdateStatus PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual void SaveSettingsData(pugi::xml_node& save)
	{

	}

	virtual void LoadSettingsData(pugi::xml_node& load)
	{

	}
};

#endif // !__MODULE_H__