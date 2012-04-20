#include "AppMain.h"

AppMain::AppMain()
{
	mCfg->getCFG();
	input = new InputManager();
}


AppMain::~AppMain()
{
	if( mD3DManager ) mD3DManager->~D3DManager();
	if ( mCfg ) mCfg->~CFG();
	if ( mScreenManager ) mScreenManager->~ScreenManager();
}

bool AppMain::Initialize(HWND* _hWnd, HINSTANCE _hInstance)
{

	//mD3DManager = new D3DManager(	mParser->getIntOfKey("resx"), 
	//								mParser->getIntOfKey("resy"));
	mScreenManager->GetSM()->AddScreen( new InGameScreen() );
	mScreenManager->GetSM()->AddScreen( new PrototypeScreen() );
	int width = mCfg->getCFG()->GetIntOfKey("RESX", "GFX", "Setup");
	int height = mCfg->getCFG()->GetIntOfKey("RESY", "GFX", "Setup");
	input->initialize(_hInstance, width, height);
	return true;
}

void AppMain::Update()
{
	mScreenManager->GetSM()->Update();
	input->frame();
	int test = input->getMousePos()->x;
}