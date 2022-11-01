#ifndef __PANEL_CONSOLE_H_
#define __PANEL_CONSOLE_H_

#include "UiPanel.h"

class PanelConsole : public UiPanel
{
public:
	PanelConsole(Application* app);
	virtual ~PanelConsole();

	void Draw() override;

private:
};

#endif

