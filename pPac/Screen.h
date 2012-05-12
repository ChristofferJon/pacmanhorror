#ifndef __SCREEN__
#define __SCREEN__

#include "ResourceHandler.h"
#include "FontLoader.h"
#include "InputManager.h"

#include "ScreenMediator.h"

#include "SoundManager.h"

#include "StandardCalls.h"

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
	virtual void Initialize( ResourceHandler* _resources );
	virtual void CheckForInput(float dt) = 0;

	bool			IsActive()const;
	ScreenMediator* mScreenMediator;

protected:
	Dbg*	dbg;
	const string  mName;

	ID3DX10Sprite*	mFontSprite;
	LPD3DX10FONT	mFont;
	FontLoader*		mFontLoader;
	ID3D10Device*	mD3DDevice;
	D3DManager*		mD3DManager;
	InputManager*	mInput;

	ID3D10Buffer*	mBuffer;

public:
	ResourceHandler*	mResources;
	SoundManager*		mSoundManager;
};

#endif