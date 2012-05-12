
#include "AppMain.h"

AppMain::AppMain()
{
	mGameTime->getInstance();	
	mCfg->getCFG();
}


AppMain::~AppMain()
{
	mScreenManager.~ScreenManager();

	mD3DManager.~D3DManager();
	if ( mCfg ) mCfg->~CFG();
}

bool AppMain::Initialize(HWND _hWnd, HINSTANCE _hInstance)
{
	// create d3dManager
	mD3DManager = D3DManager();
	if( mD3DManager.Initialize( &_hWnd, _hInstance ) == false )
		return false;	// if initialization fails, shutdown application

	// create inputManager
	mInputManager = InputManager();
	if ( mInputManager.Initialize( _hWnd, _hInstance, mD3DManager.mWidth, mD3DManager.mHeight ) == false )	// change to read from either file or global access
		return false;	// if initialization fails, shutdown application

	// create screenManager and add first screen
	mScreenManager = ScreenManager( &mD3DManager );
	mScreenManager.Initialize();
	mScreenManager.AddScreen( new MainMenuScreen("Main Menu", &mD3DManager, &mInputManager) );
	//mScreenManager.AddScreen( new InGameScreen("InGame", &mD3DManager, &mInputManager) );
	// initiate gametimer
	mGameTime->getInstance()->start();

	// everything's golden
	return true;
}

void AppMain::Update()
{
	// update gametime
	mGameTime->getInstance()->tick();
	float dt = mGameTime->getInstance()->deltaTime();

	// update screens
	mScreenManager.Update(dt);

	// draw screens
	mScreenManager.Draw(dt);
}