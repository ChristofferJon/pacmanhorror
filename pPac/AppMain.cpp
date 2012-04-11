#include "AppMain.h"

AppMain::AppMain()
{

}


AppMain::~AppMain()
{
	if( mD3DManager) mD3DManager->~D3DManager();
}

bool AppMain::Initialize(Parser* _parser)
{
	mParser = _parser;
	mParser->Load("GFX");

	mD3DManager = new D3DManager(	mParser->getIntOfKey("resx"), 
									mParser->getIntOfKey("resy"));
	return true;
}

void AppMain::Update()
{

}