
E:\Programmering\Github\pacmanhorror>@git.exe %*
#include "GameScreen.h"


GameScreen::GameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager) 
	: Screen(_name, _D3DManager, _inputManager)
{
	mRec.left = 10;
	mRec.right = mRec.left;
	mRec.top = 10;
	mRec.bottom = mRec.top;

	// fonts
	mFontLoader->CreateFontA("Lucida Sans", mD3DDevice, 20);
	mFont = *mFontLoader->getFont();
	mFontSprite = mFontLoader->getSpriteFont();

	FPS = 0;
	frames = 0;
	currentTime = 0;
	lastUpdateTime = 0;
	elapsedTime = 0;
}


GameScreen::~GameScreen()
{
}

void GameScreen::Draw()
{
	// temporary disable rasterizer state
	mD3DDevice->RSSetState(0);

	// draw font
	mFontSprite->Begin(D3DX10_SPRITE_SAVE_STATE);

	mFont->DrawTextA(NULL, (mName + " : pPac Prototype \nBTH 2012 - DV1435 \ndt: " + removeMe + 
							"\nfps: " + removeMeFPS + "\nCamPos: " + removeMeCamPos + "\nCamLook: " + 
							removeMeCamLook).c_str(),
							-1, &mRec, DT_NOCLIP, D3DXCOLOR(1.0, 1.0, 1.0, 0.75) );

	mFontSprite->End();

	// restore rasterizer state
	mD3DDevice->RSSetState(mD3DManager->pRS);
}

void GameScreen::Update(float dt)
{
	std::ostringstream ss;
	ss << dt;
	removeMe = ss.str();

	frames++;
	currentTime = GetTickCount();
	elapsedTime = currentTime - lastUpdateTime;

	if ( elapsedTime >= 1000 )
	{
		FPS = (UINT)(frames * 1000.0 / elapsedTime);
		frames = 0;
		lastUpdateTime = currentTime;

		std::ostringstream s;
		s << FPS;
		removeMeFPS = s.str();
	}

	std::ostringstream c;
	c << mGFS->cam->mPosition.x << ":" << mGFS->cam->mPosition.y << ":" << mGFS->cam->mPosition.z;
	removeMeCamPos = c.str();

	std::ostringstream cl;
	cl << mGFS->cam->mLook.x << ":" << mGFS->cam->mLook.y << ":" << mGFS->cam->mLook.z;
	removeMeCamLook = cl.str();
}

void GameScreen::Initialize( ResourceHandler* _resources )
{
	Screen::Initialize( _resources );
}

void GameScreen::CheckForInput( float dt )
{
	Screen::CheckForInput( dt );

	//mInput->UpdateOldStates();
}
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
