#ifndef __APPMAIN__
#define __APPMAIN__

#include <cstdlib>
#include "D3DManager.h"
#include "ScreenManager.h"
#include "ResourceHandler.h"
#include "InputManager.h"

#include "CFG.h"

#include "GameTimer.h"

#include "MainMenuScreen.h"
#include "CreditScreen.h"
#include "InGameScreen.h"

#pragma region Class Description

/*	Main updater and initializer for all managers.	*/

#pragma endregion

class AppMain
{
public:
	AppMain();
	~AppMain();

public:
	bool		Initialize(HWND _hWnd, HINSTANCE _hInstance);
	void		Update();

private:
	D3DManager		mD3DManager;
	ScreenManager	mScreenManager;
	InputManager	mInputManager;
	CFG*			mCfg;
	GameTimer*		mGameTime;

	ResourceHandler* resourceHandler;
};

#endif