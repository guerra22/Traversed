#ifndef __PANEL_INSPECTOR_H_
#define __PANEL_INSPECTOR_H_

#include "UiPanel.h"

class PanelInspector : public UiPanel
{
public:
	PanelInspector(Application* app);
	virtual ~PanelInspector();

	void Draw() override;

private:
};

#endif
