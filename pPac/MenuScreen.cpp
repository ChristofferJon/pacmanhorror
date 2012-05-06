#include "MenuScreen.h"


MenuScreen::MenuScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager) 
	: Screen(_name, _D3DManager, _inputManager)
{
	selectedEntry = 0;
	mRec.left = 10;
	mRec.right = mRec.left;
	mRec.top = 10;
	mRec.bottom = mRec.top;

	// background
	mSprite = NULL;

	// fonts
	mFontLoader->CreateFontA("Lucida Sans", mD3DDevice);
	mFont = *mFontLoader->getFont();
	mFontSprite = mFontLoader->getSpriteFont();
}


MenuScreen::~MenuScreen()
{
	for each (MenuEntry* m in mMenuEntries)
		m->~MenuEntry();

	Screen::~Screen();
}

void MenuScreen::Initialize()
{
}

void MenuScreen::Draw()
{
	mD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
	mD3DManager->mColorMap->SetResource( mSprite->mTexture->pSRView );

	D3D10_TECHNIQUE_DESC techDesc;
	ID3D10EffectTechnique* mTech = mRP->mTechnique;
	mTech->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0);
		mD3DDevice->Draw(1, 0);
	}

	mD3DDevice->RSSetState(0);

	mFontSprite->Begin(D3DX10_SPRITE_SAVE_STATE);

	mFont->DrawTextA(NULL, mName.c_str(), -1, &mRec, DT_NOCLIP, D3DXCOLOR(1.0, 1.0, 1.0, 1.0) );

	for each (MenuEntry* m in mMenuEntries)
		m->Draw(mFont);

	mFontSprite->End();
}

void MenuScreen::CheckForInput()
{
	Screen::CheckForInput();

		// navigate menu by mouse
	POINT* mousePos = mInput->getMousePos();

	for ( int i = 0; i < mMenuEntries.size(); i++ )
	{
		if ( Intersect( i, mousePos ) && !mInput->IsMouseIdle())
		{
			selectedEntry = i;
		}
	}

	// navigate menu by keyboard
	if ( mInput->IsNewKeyPress( DIK_UP ) || 
		mInput->IsNewKeyPress( DIK_W ) )
	{
		selectedEntry--;

		if ( selectedEntry < 0 )
			selectedEntry = mMenuEntries.size() -1;
	}
	else if ( mInput->IsNewKeyPress( DIK_DOWN ) ||
			  mInput->IsNewKeyPress( DIK_S) )
	{
		selectedEntry++;

		if ( selectedEntry > mMenuEntries.size() -1)
			selectedEntry = 0;
	}

	if ( mInput->IsNewKeyPress(DIK_RETURN) )
		OnSelectEntry(selectedEntry);

	if ( Intersect( selectedEntry, mousePos) && mInput->isNewMLeftButton() )
		OnSelectEntry( selectedEntry );

	// uodate input states
	mInput->UpdateOldStates();
}

void MenuScreen::OnSelectEntry(int _index)
{
	Screen* me = this;
	mMenuEntries[_index]->Selected( me );
}

bool MenuScreen::Intersect( int _index, POINT* _mousePos )
{
	if ( _mousePos->x > mMenuEntries[_index]->mRec.left		&&
		 _mousePos->x < mMenuEntries[_index]->mRec.right	&&
		 _mousePos->y > mMenuEntries[_index]->mRec.top		&&
		 _mousePos->y < mMenuEntries[_index]->mRec.bottom		)
		 return true;
	
	return false;
}

void MenuScreen::Update(float dt)
{
	Screen::Update(dt);

	for (int i = 0; i < mMenuEntries.size(); i++)
	{
		bool isSelected = ( i == selectedEntry );
		mMenuEntries[i]->Update( dt, isSelected );
	}
}