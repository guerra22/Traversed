#ifndef __PANEL_HIERARCHY_H_
#define __PANEL_HIERARCHY_H_

#include "UiPanel.h"

class PanelHierarchy : public UiPanel
{
public:
	PanelHierarchy(Application* app);
	virtual ~PanelHierarchy();

	void Draw() override;

private:
};

#endif

