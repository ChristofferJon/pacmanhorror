#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	
}

ScreenManager::ScreenManager(D3DManager* _D3DManager)
{
	mD3DManager = _D3DManager;
	mD3DDevice = _D3DManager->mD3DDevice;
}

ScreenManager::~ScreenManager()
{
	while ( mScreens.size() > 0 )
	{
		mScreens[ mScreens.size() - 1 ]->~Screen();
		mScreens.pop_back();
	}
}

void ScreenManager::Initialize()
{
	mSoundManager = new SoundManager();
	mResources = new ResourceHandler( mD3DManager );
}

void ScreenManager::AddScreen(Screen* _screen)
{
	mScreens.push_back(_screen);
	_screen->mScreenMediator = new ScreenMediator( this );
	_screen->mSoundManager = mSoundManager;
	_screen->Initialize( mResources );
}

void ScreenManager::RemoveScreen(Screen* _screen)
{
	for (int i = 0; i < mScreens.size(); i++)
		if (mScreens[i] == _screen)
		{
			mScreens.erase(mScreens.begin() + i);
			mScreens.shrink_to_fit();
		}

		for (int i = 0; i < mScreensToUpdate.size(); i++)
			if (mScreensToUpdate[i] == _screen)
			{
				mScreensToUpdate.erase(mScreensToUpdate.begin() + i);
				mScreensToUpdate.shrink_to_fit();
			}

	if (_screen != NULL)
		_screen->~Screen();
}

void ScreenManager::ClearAllScreens()
{
	for each (Screen* s in mScreens)
		s->~Screen();

	mScreens.clear();
}

void ScreenManager::Update(float deltaTime)
{
	// make a copy of the mScreens instead of
	// directly working with the master list
	mScreensToUpdate.clear();

	for each (Screen* screen in mScreens)
		mScreensToUpdate.push_back(screen);

	// ensures that only the original topmost screen
	// handles input
	bool otherScreenHasFocus = false;

	// iterate through all screens
	while ( mScreensToUpdate.size() > 0)
	{
		// process and then pop the topmost screen
		// in the temporary screen list
		Screen* screen = mScreensToUpdate[mScreensToUpdate.size() - 1];
		mScreensToUpdate.erase(mScreensToUpdate.end()- 1);

		// update
		screen->Update( deltaTime );

		if ( screen->mScreenState == screen->SS_TRANSITION_ON ||
			 screen->mScreenState == screen->SS_ACTIVE )
		{	
			// handle input for the first active screen only
			if ( !otherScreenHasFocus )
			{
				screen->CheckForInput( deltaTime );
				otherScreenHasFocus = true;
			}
		}
	}
}

void ScreenManager::Draw(float deltaTime)
{
	// clear for each tick
	mD3DDevice->ClearRenderTargetView( mD3DManager->mRenderTargetView, D3DXCOLOR( 0.0, 0.0, 0.0, 0.0 ) );

	// draw every screen (the one in focus will always be placed on top
	for each (Screen* screen in mScreens)
		screen->Draw();

	// set state and chain
	//mD3DDevice->RSSetState(mD3DManager->pRS);
	mD3DManager->mSwapChain->Present(0,0);		// no lock on fps
}