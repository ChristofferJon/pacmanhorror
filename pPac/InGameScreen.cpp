#include "InGameScreen.h"


InGameScreen::InGameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager) 
	: GameScreen(_name, _D3DManager, _inputManager)
{

}


InGameScreen::~InGameScreen()
{
}

void InGameScreen::Initialize( ResourceHandler* _resources)
{
	GameScreen::Initialize( _resources );
	mGFS = new GFS( "HELLO" );
	mGFS->md3dManager = mD3DManager;
	mGFS->Initialize( _resources );
}

void InGameScreen::Draw( )
{
	mD3DDevice->ClearRenderTargetView( mD3DManager->mRenderTargetView, D3DXCOLOR(0.7, 0.2, 0.5, 0.5) );	// remove!
	mGFS->Draw( 42.0 );

	GameScreen::Draw( );
}