#ifndef __ABOUT_UI_H_
#define __ABOUT_UI_H_

#include "UiElements.h"

class AboutUi : public UiElements
{
public:
	AboutUi();
	virtual ~AboutUi();

	void Draw() override;
};

#endif

