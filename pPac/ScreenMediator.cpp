#include "ScreenMediator.h"

#include "ScreenManager.h"

ScreenMediator::ScreenMediator(ScreenManager* _screenManager) : mScreenManager(_screenManager)
{
}


ScreenMediator::~ScreenMediator()
{
}

void ScreenMediator::RemoveMe( Screen* _screen )
{
	mScreenManager->RemoveScreen( _screen );
	this->~ScreenMediator();
}

void ScreenMediator::RemoveAll()
{
	mScreenManager->ClearAllScreens();
}

void ScreenMediator::AddNewScreen( Screen* _screen )
{
	mScreenManager->AddScreen( _screen );
}