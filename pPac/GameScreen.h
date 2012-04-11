#ifndef __GameScreen__
#define __GameScreen__

#include "Screen.h"

class GameScreen : public Screen
{
public:
	GameScreen();
	~GameScreen();

protected:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Initialize() = 0;
	virtual void CheckForInput() = 0;
};

#endif