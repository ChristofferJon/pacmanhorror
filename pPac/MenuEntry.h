#ifndef __MENUENTRY__
#define __MENUENTRY__

#include <string>
#include "Sprite.h"
#include <math.h>
#include "GameTimer.h"
#include "event.h"

#include "Screen.h"

using std::string;

class MenuEntry
{
public:
	MenuEntry( string _text, Sprite* _sprite, int _sfxId );
	~MenuEntry();
	void Initialize( int _indX, int _indY );

public:
	Sprite*			mSprite;
	const string	mName;
	float			mSelectionFade;
	int				mSFXid;
	D3DXCOLOR		mColor;
	string			mText;

public:
	void		Update(float dt, bool _isSelected);
	void		Draw(LPD3DX10FONT _mFont);
	RECT		mRec;
	void		setColor();

	Event<Screen*> Selected;
	Event<Screen*> Idle;
};

#endif