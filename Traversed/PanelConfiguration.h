#ifndef __PANEL_CONFIGURATION_H_
#define __PANEL_CONFIGURATION_H_

#include "PanelAbout.h"


class PanelConfiguration : public UiPanel
{
public:
	PanelConfiguration(Application* app);
	virtual ~PanelConfiguration();

	void Draw() override;

	bool fullscreen = false;
	int screenWidth;
	int screenHeight;
	bool Vsync = false;
	float screenBrightness;

};

#endif

