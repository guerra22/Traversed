#ifndef __PANEL_ABOUT_H_
#define __PANEL_ABOUT_H_

#include "UiPanel.h"

class PanelAbout : public UiPanel
{
public:
	PanelAbout();
	virtual ~PanelAbout();

	void Draw() override;
};

#endif

