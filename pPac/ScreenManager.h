#ifndef __SCREENMANAGER__
#define __SCREENMANAGER__

#include <vector>
#include "Screen.h"
#include "Dbg.h"

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
	void			AddScreen(Screen* _screen);
	void			RemoveScreen(Screen* _screen);
	void			Update(float deltaTime);
	ScreenManager*	GetSM();
	Dbg*			dbg;
};

#endif