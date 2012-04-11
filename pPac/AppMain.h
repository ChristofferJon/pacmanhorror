#ifndef __APPMAIN__
#define __APPMAIN__

#include <cstdlib>
#include "D3DManager.h"
#include "ScreenManager.h"

#include "CFG.h"

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
	bool		Initialize();
	void		Update();

private:
	D3DManager*		mD3DManager;
	ScreenManager*	mScreenManager;
	CFG*		mCfg;
};

#endif