#include "UiElements.h"

UiElements::UiElements()
{

}

UiElements::~UiElements()
{

}

bool UiElements::IsActive() const
{
	return active;
}

void UiElements::switchActive()
{
	active = !active;
}