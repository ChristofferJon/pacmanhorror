#include "ScreenManager.h"

ScreenManager* instance = NULL;

ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{
}

ScreenManager* ScreenManager::GetSM()
{
	if (instance == NULL)
		instance = new ScreenManager();

	return instance;
}

void ScreenManager::AddScreen(Screen* _screen)
{
	mScreens.push_back(_screen);
}

void ScreenManager::RemoveScreen(Screen* _screen)
{
	for (int i = 0; i < mScreens.size(); i++)
		if (mScreens[i] == _screen)
		{
			mScreens.erase(mScreens.begin() + i);
			mScreens.shrink_to_fit();
		}

	if (_screen != NULL)
		_screen->~Screen();
}

void ScreenManager::Update()
{
	mScreensToUpdate.clear();

	for each (Screen* screen in mScreens)
		mScreensToUpdate.push_back(screen);

	while ( mScreensToUpdate.size() > 0)
	{
		Screen* screen = mScreensToUpdate[mScreensToUpdate.size() - 1];
		mScreensToUpdate.erase(mScreensToUpdate.end()- 1);

		screen->Update();

		if ( screen->mScreenState == screen->SS_ACTIVE )
		{
			screen->CheckForInput();
		}
	}
}