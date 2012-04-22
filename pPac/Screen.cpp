#include "Screen.h"

Screen::Screen()
{
	mScreenState = SS_TRANSITION_ON;
	t = new TEST();
}

Screen::~Screen()
{

}

void Screen::Update()
{
	CheckForInput();
}

bool Screen::IsActive()const
{
	return ( mScreenState == SS_TRANSITION_ON || mScreenState == SS_ACTIVE );
}