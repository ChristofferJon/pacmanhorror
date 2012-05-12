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
	mGFS->mInput = mInput;
	mResources = _resources;
	mGFS->mSoundManager = mSoundManager;
}

void InGameScreen::CheckForInput( float dt )
{
	GameScreen::CheckForInput( dt );

	mGFS->ChechForInput( dt );

	mInput->UpdateOldStates();
}

void InGameScreen::Update( float dt )
{
	GameScreen::Update( dt );
}

void InGameScreen::Draw( )
{
	mD3DDevice->ClearDepthStencilView( mD3DManager->mDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0 );

	// set d3d states
	mD3DDevice->IASetInputLayout( mD3DManager->mBasicLayout );
	mD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mD3DDevice->OMSetDepthStencilState( 0, 0 );

	// draw
	mGFS->Draw( 42.0 );

	GameScreen::Draw( );
}