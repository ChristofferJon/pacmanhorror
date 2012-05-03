#include "Screen.h"

Screen::Screen(string _name, D3DManager* _D3DManager, InputManager* _inputManager)
{
	mScreenState = SS_ACTIVE;
	t = new TEST(this);
	mName = _name;

	mD3DManager = _D3DManager;
	mD3DDevice = mD3DManager->mD3DDevice;
	mFontLoader = FontLoader();
	mInput = _inputManager;
}

Screen::~Screen()
{

}

void Screen::Update(float dt)
{
	//CheckForInput();
	//dbg->getDbg()->print("%s\n", mName.c_str());
}

void Screen::CheckForInput()
{
	mInput->frame();
}

bool Screen::IsActive()const
{
	return ( mScreenState == SS_TRANSITION_ON || mScreenState == SS_ACTIVE );
}