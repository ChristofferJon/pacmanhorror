#ifndef __SCREEN__
#define __SCREEN__

#include "Dbg.h"

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
	Screen();
	~Screen();

public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual void CheckForInput() = 0;

	bool		IsActive()const;

protected:
	Dbg*	dbg;
};

#endif