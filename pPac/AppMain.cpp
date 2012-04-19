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

bool AppMain::Initialize()
{

	//mD3DManager = new D3DManager(	mParser->getIntOfKey("resx"), 
	//								mParser->getIntOfKey("resy"));
	mScreenManager->GetSM()->AddScreen( new InGameScreen() );
	mScreenManager->GetSM()->AddScreen( new PrototypeScreen() );
	return true;
}

void AppMain::Update()
{
	mScreenManager->GetSM()->Update();
}