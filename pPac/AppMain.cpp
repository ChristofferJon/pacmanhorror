#include "AppMain.h"

AppMain::AppMain()
{
	mCfg->getCFG();
}


AppMain::~AppMain()
{
	if( mD3DManager ) mD3DManager->~D3DManager();
	if ( mCfg ) mCfg->~CFG();
}

bool AppMain::Initialize()
{

	//mD3DManager = new D3DManager(	mParser->getIntOfKey("resx"), 
	//								mParser->getIntOfKey("resy"));
	return true;
}

void AppMain::Update()
{

}