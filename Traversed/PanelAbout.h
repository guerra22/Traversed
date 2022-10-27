#ifndef __PANEL_ABOUT_H_
#define __PANEL_ABOUT_H_

#include "UiPanel.h"

class PanelAbout : public UiPanel
{
public:
	PanelAbout(Application* app);
	virtual ~PanelAbout();

	void Draw() override;

private:
	std::string sdlVersion;
	std::string glewVersion;
	std::string imGUIVersion;
	std::string jsonVersion;
	std::string mathGeoLibVersion;
	std::string assimpLibVersion;
	std::string devilLibVersion;
};

#endif

