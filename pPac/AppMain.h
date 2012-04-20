
E:\Programmering\Github\pacmanhorror>@git.exe %*
#ifndef __APPMAIN__
#define __APPMAIN__

#include <cstdlib>
#include "D3DManager.h"
#include "ScreenManager.h"

#include "CFG.h"

#include "GameTimer.h"

#include "InGameScreen.h"
#include "PrototypeScreen.h"

#pragma region Class Description

/*	Main updater and initializer for all managers.	*/

#pragma endregion

class AppMain
{
public:
	AppMain();
	~AppMain();

public:
	bool		Initialize(HWND* _hWnd, HINSTANCE _hInstance);
	void		Update();

private:
	D3DManager*		mD3DManager;
	ScreenManager*	mScreenManager;
	CFG*			mCfg;
	GameTimer*		mGameTime;
};

#endif
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
