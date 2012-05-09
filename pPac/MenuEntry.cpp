#include "MenuEntry.h"


MenuEntry::MenuEntry(string _text, Sprite* _sprite, int _sfxId) 
	: mName(_text), mSprite(_sprite), mSFXid(_sfxId)
{
	mSelectionFade = 0.75f;
	mText = "";
	mSFXid = _sfxId;
}


MenuEntry::~MenuEntry()
{
	delete mSprite;
}

void MenuEntry::Initialize( int _indX, int _indY )
{
	mRec.left = _indX;
	mRec.right = mRec.left + 200;
	mRec.top = _indY;
	mRec.bottom = mRec.top + 50;
}

void MenuEntry::setColor()
{
	float mf = mSelectionFade;
	mColor = D3DXCOLOR( 1.0f * mf, 1.0f * mf, 1.0f * mf, 0.85f * mf );
}

void MenuEntry::Update(float dt, bool _isSelected)
{
	if ( _isSelected )
		mSelectionFade = min( mSelectionFade + dt, 1.0f );
	else
		mSelectionFade = max( mSelectionFade - dt, 0.65f );
}

void MenuEntry::Draw(LPD3DX10FONT _mFont)
{
	setColor();

	_mFont->DrawTextA(NULL, (mName + mText).c_str(), -1, &mRec, DT_NOCLIP, mColor);

}