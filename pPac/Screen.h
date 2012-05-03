#ifndef __SCREEN__
#define __SCREEN__

#include "Dbg.h"
#include "TEST.h"

#include "ResourceHandler.h"
#include "FontLoader.h"
#include "InputManager.h"

using std::string;

class Screen
{
public:
	enum SCREEN_STATE
	{
		SS_TRANSITION_ON,
		SS_TRANSITION_OFF,
		SS_ACTIVE,
		SS_HIDDEN
	};
	SCREEN_STATE	mScreenState;

public:
	Screen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~Screen();

public:
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Initialize() = 0;
	virtual void CheckForInput() = 0;

	bool		IsActive()const;

protected:
	Dbg*	dbg;
	TEST*	t;
	string  mName;

	ID3DX10Sprite*	mFontSprite;
	LPD3DX10FONT	mFont;
	FontLoader		mFontLoader;
	ID3D10Device*	mD3DDevice;
	D3DManager*		mD3DManager;
	InputManager*	mInput;

private:
	ResourceHandler* resources;
};

#endif