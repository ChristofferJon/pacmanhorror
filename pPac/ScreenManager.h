#ifndef __SCREENMANAGER__
#define __SCREENMANAGER__

#include "StandardCalls.h"
#include "Screen.h"


#include "D3DManager.h"
#include "SoundManager.h"
#include "ResourceHandler.h"

class ScreenManager
{
public:
	ScreenManager();
	ScreenManager(D3DManager* _D3DManager);
	~ScreenManager();
	void Initialize();

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
	D3DManager*			mD3DManager;
	ID3D10Device*		mD3DDevice;
	SoundManager*		mSoundManager;
	ResourceHandler*	mResources;
};

#endif