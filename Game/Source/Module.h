#ifndef __MODULE_H__
#define __MODULE_H__

#include "SString.h"

#include "PugiXml/src/pugixml.hpp"

class App;
class PhysicBody;

class Module
{
public:

	Module() : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	// L01: DONE 5: Sending config file to all modules
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual void Activate() {
		active = true;
	}

	// Called to deactivate module
	virtual void Deactivate() {
		active = false;
	}

	// Called on two bodies collision
	virtual void OnCollision(PhysicBody* bodyA, PhysicBody* bodyB)
	{
	}
public:

	SString name;
	bool active;

	void Enable() {
		if (!isEnabled)
		{
			isEnabled = true;
			Start();
		}
	}

	// Switches isEnabled and calls CleanUp() method
	void Disable() {
		if (isEnabled)
		{
			isEnabled = false;
			CleanUp();
		}
	}

	inline bool IsEnabled() const { return isEnabled; }

private:
	bool isEnabled = true;
};

#endif // __MODULE_H__