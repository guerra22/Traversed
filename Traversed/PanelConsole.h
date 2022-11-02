#ifndef __PANEL_CONSOLE_H_
#define __PANEL_CONSOLE_H_

#include "UiPanel.h"

class PanelConsole : public UiPanel
{
public:
	PanelConsole(Application* app);
	virtual ~PanelConsole();

	void Draw() override;

public:

	void AddLog(const char* log);

private:

	void ClearLog();
	void ConsoleMenu();

private:

	std::vector<char*> logsConsole;
	bool scrollBottom;
};

#endif

