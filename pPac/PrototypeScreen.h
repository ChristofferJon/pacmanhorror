#ifndef __PROTOTYPESCREEN__
#define __PROTOTYPESCREEN__

#include "GameScreen.h"

class PrototypeScreen : public GameScreen
{
public:
	PrototypeScreen();
	~PrototypeScreen();

	virtual void Render();
	virtual void Update();
	virtual void Initialize();
	virtual void CheckForInput();
};

#endif