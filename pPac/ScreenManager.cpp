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


void ScreenManager::AddScreen(Screen* _screen)
{
	mScreens.push_back(_screen);
}

void ScreenManager::RemoveScreen(Screen* _screen)
{
	for (int i = 0; i < mScreens.size(); i++)
		if (mScreens[i] == _screen)
		{
			mScreens.erase(mScreens.begin() + i);
			mScreens.shrink_to_fit();
		}

	if (_screen != NULL)
		_screen->~Screen();
}

void ScreenManager::Update(float deltaTime)
{
	dbg->getDbg()->print("%f\n", deltaTime);
	mScreensToUpdate.clear();

	for each (Screen* screen in mScreens)
		mScreensToUpdate.push_back(screen);

	while ( mScreensToUpdate.size() > 0)
	{
		Screen* screen = mScreensToUpdate[mScreensToUpdate.size() - 1];
		mScreensToUpdate.erase(mScreensToUpdate.end()- 1);

		screen->Update( deltaTime );

		if ( screen->mScreenState == screen->SS_ACTIVE )
		{		
			screen->CheckForInput();
		}
	}
}

void ScreenManager::Draw(float deltaTime)
{
	// clear for each tick
	mD3DDevice->ClearRenderTargetView( mD3DManager->mRenderTargetView, D3DXCOLOR( 0.0, 0.0, 0.0, 0.0 ) );
	mD3DDevice->ClearDepthStencilView( mD3DManager->mDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0 );

	// draw every screen (the one in focus will always be placed on top
	for each (Screen* screen in mScreens)
		screen->Draw();

	// set state and chain
	mD3DDevice->RSSetState(mD3DManager->pRS);
	mD3DManager->mSwapChain->Present(0,0);		// no lock on fps
}