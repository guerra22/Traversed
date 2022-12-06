#ifndef __PANEL_CONSOLE_H_
#define __PANEL_CONSOLE_H_

#include "UiPanel.h"
//#include "Globals.h"

class Loggs;

class PanelConsole : public UiPanel
{
public:
	PanelConsole(bool enabled = false);
	~PanelConsole();

	void Update() override;

private:
	void NormalLog();
	void CollapseLog();

	void ClearGUI();
	void LogGUI();
	void OptionsGUI();

private:
	Loggs* loggs;

	int lastSize = 0;
	bool scrollDown = false;
	bool showTime = true;
	bool collapse = false;

	bool logError = true;
	bool logAttention = true;
	bool logEngine = true;
	bool logSuccess = true;
};

#endif

