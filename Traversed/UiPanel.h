#ifndef __UI_PANEL_H_
#define __UI_PANEL_H_

#include "Application.h"
#include <string>

class UiPanel
{
public:
	UiPanel(Application* app);
	virtual ~UiPanel();

	virtual void Draw() {};
	bool IsActive() const;
	void switchActive();
	virtual bool CleanUp() { return true; }

	bool active = false;
	
	Application* App = nullptr;
};

#endif
