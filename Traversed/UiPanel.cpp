#include "UiPanel.h"

UiPanel::UiPanel(Application* app)
{
	this->App = app;
}

UiPanel::~UiPanel()
{
	
}

bool UiPanel::IsActive() const
{
	return active;
}

void UiPanel::switchActive()
{
	active = !active;
}