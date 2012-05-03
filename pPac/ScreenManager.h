#ifndef __SCREENMANAGER__
#define __SCREENMANAGER__

#include <vector>
#include "Screen.h"
#include "Dbg.h"

#include <string>

#include "D3DManager.h"

class ScreenManager
{
public:
	ScreenManager();
	ScreenManager(D3DManager* _D3DManager);
	~ScreenManager();

public:
	std::vector<Screen*> mScreens;
	std::vector<Screen*> mScreensToUpdate;

public:
	void			AddScreen(Screen* _screen);
	void			RemoveScreen(Screen* _screen);
	void			ClearAllScreens();
	void			Update(float deltaTime);
	void			Draw(float deltaTime);
	Dbg*			dbg;

private:
	D3DManager*		mD3DManager;
	ID3D10Device*	mD3DDevice;
};

#endif