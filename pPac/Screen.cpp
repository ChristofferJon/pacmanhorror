#include "Screen.h"

Screen::Screen()
{
	mScreenState = SS_ACTIVE;
}

Screen::~Screen()
{

}

void Screen::Update()
{
	CheckForInput();
}