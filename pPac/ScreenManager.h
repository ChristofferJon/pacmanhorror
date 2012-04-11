#ifndef __SCREENMANAGER__
#define __SCREENMANAGER__

#include <vector>
#include "Screen.h"

class ScreenManager
{
private:
	ScreenManager();

public:
	~ScreenManager();

public:
	std::vector<Screen*> mScreens;
	std::vector<Screen*> mScreensToUpdate;

public:
	void		AddScreen(Screen* _screen);
	void		RemoveScreen(Screen* _screen);
	void		Update();
	ScreenManager*	GetSM();
};

#endif