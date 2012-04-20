#include "Screen.h"

Screen::Screen()
{
	mScreenState = SS_TRANSITION_ON;
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