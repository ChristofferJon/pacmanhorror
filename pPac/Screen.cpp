#include "Screen.h"

Screen::Screen(string _name, D3DManager* _D3DManager, InputManager* _inputManager)
	: mName(_name)
{
	mScreenState = SS_ACTIVE;

	mD3DManager = _D3DManager;
	mD3DDevice = mD3DManager->mD3DDevice;
	mFontLoader = new FontLoader();
	mInput = _inputManager;
}

Screen::~Screen()
{
	mFontLoader->~FontLoader();
}

void Screen::Update(float dt)
{

}

void Screen::CheckForInput()
{
	mInput->frame();
}

bool Screen::IsActive()const
{
	return ( mScreenState == SS_TRANSITION_ON || mScreenState == SS_ACTIVE );
}

void Screen::Initialize( ResourceHandler* _resources )
{
	mResources = _resources;
}