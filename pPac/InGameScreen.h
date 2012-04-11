#ifndef __INGAMESCREEN__
#define __INGAMESCREEN__

#include "GameScreen.h"

class InGameScreen : public GameScreen
{
public:
	InGameScreen();
	~InGameScreen();

	virtual void Render();
	virtual void Update();
	virtual void Initialize();
	virtual void CheckForInput();
};

#endif