#include "GameScreen.h"
#include "MainMenuScreen.h"

void Cancel( Screen* _screen )
{
	GameScreen* me = (GameScreen*)_screen;
	me->OnReturn( me );
}

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

	Return.add( Cancel );
	health = 100;
	h = 100.0f;
	pi = 0;
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
							"\nfps: " + removeMeFPS + "\nhealth:" + H + "\npills:" + pills).c_str(),
							-1, &mRec, DT_NOCLIP, D3DXCOLOR(1.0, 1.0, 1.0, 0.75) );

	RECT c;
	c.left = 550;
	c.right = mRec.left;
	c.top = 300;
	c.bottom = mRec.top;
	mFont->DrawTextA(NULL, (gameOver).c_str(),
							-1, &c, DT_NOCLIP, D3DXCOLOR(1.0, 1.0, 1.0, 0.75) );

	mFontSprite->End();

	// restore rasterizer state
	mD3DDevice->RSSetState(mD3DManager->pRS);
}

void GameScreen::Update(float dt)
{
	mGFS->Update( dt );
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

	std::ostringstream hel;
	hel << health;
	H = hel.str();

	std::ostringstream pil;
	pil << pi << "/" << pOf;
	pills = pil.str();

	if ( health <= 0)
	{
		gameOver = "Game Over";
	}
	else
		gameOver = "";
}

void GameScreen::Initialize( ResourceHandler* _resources )
{
	Screen::Initialize( _resources );
}

void GameScreen::CheckForInput( float dt )
{
	Screen::CheckForInput( dt );

	if ( mInput->IsNewKeyPress( DIK_ESCAPE ) )
		Cancel( this );

	//mInput->UpdateOldStates();
}

void GameScreen::OnReturn( GameScreen* _me )
{
	mScreenMediator->AddNewScreen( new MainMenuScreen( "Main Menu", mD3DManager, mInput ) );
	mScreenMediator->RemoveMe( _me );
}