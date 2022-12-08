#ifndef __UI_PANEL_H_
#define __UI_PANEL_H_

#include "ImGuiUtils.h"

#include <string>

class UiPanel
{
public:
	UiPanel(bool enabled = false)
	{
		name = "NONE";
		this->enabled = enabled;
	};

	virtual ~UiPanel() {};

	virtual void Start() {};

	virtual void Update() {};

public:

	bool enabled = true;

	std::string name = "EmptyPanel";

};

#endif
