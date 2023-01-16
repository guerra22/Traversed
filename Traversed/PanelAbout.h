#ifndef __PANEL_ABOUT_H_
#define __PANEL_ABOUT_H_

#include "UiPanel.h"

class PanelAbout : public UiPanel
{
public:
	PanelAbout(bool enabled = false);
	virtual ~PanelAbout();

	void Update() override;

public:
	//About Text
	void ThirdPartyLibs();
	void MyLicense();

private:
	//Engine version
	std::string vEngine;

	//Lib versions
	std::string vSdl;
	std::string vImGui;
	std::string vImGuiFileDialog;
	std::string vImGuiColorTextEdit;
	std::string vMathGeoLib;
	std::string vOpenGl;
	std::string vGlew;
	std::string vNlohmann;
	std::string vAssimp;
	std::string vPhysfs;
	std::string vPugiXml;
};

#endif

