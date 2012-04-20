
E:\Programmering\Github\pacmanhorror>@git.exe %*
#include "AppMain.h"

AppMain::AppMain()
{
	mGameTime->getInstance();	
	mCfg->getCFG();
}


AppMain::~AppMain()
{
	if( mD3DManager != NULL ) 
	{
		mD3DManager->~D3DManager();
		delete mD3DManager;
		mD3DManager = NULL;
	}
	if ( mCfg ) mCfg->~CFG();
	if ( mScreenManager ) mScreenManager->~ScreenManager();
}

bool AppMain::Initialize(HWND* _hWnd, HINSTANCE _hInstance)
{

	mD3DManager = new D3DManager();

	// if initialization failes, shutdown application
	if( mD3DManager->Initialize( _hWnd, _hInstance ) == false )
		return false;

	mScreenManager->GetSM()->AddScreen( new InGameScreen() );
	mScreenManager->GetSM()->AddScreen( new PrototypeScreen() );
	mGameTime->getInstance()->start();
	return true;
}

void AppMain::Update()
{
	// update gametime
	mGameTime->getInstance()->tick();
	float dt = mGameTime->getInstance()->deltaTime();

	// update screenManager
	mScreenManager->GetSM()->Update(dt);
}
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
