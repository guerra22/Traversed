#ifndef __UI_ELEMENTS_H_
#define __UI_ELEMENTS_H_

#include "Application.h"
#include <string>

class UiElements
{
public:
	UiElements();
	virtual ~UiElements();

	virtual void Draw() {};
	bool IsActive() const;
	void switchActive();
	virtual bool CleanUp() { return true; }

	bool active = false;

};

#endif
