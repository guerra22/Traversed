#include "UiPanel.h"

UiPanel::UiPanel()
{

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