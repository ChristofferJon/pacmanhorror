#ifndef __GameScreen__
#define __GameScreen__

#include "Screen.h"

class GameScreen : public Screen
{
public:
	GameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~GameScreen();

protected:
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Initialize() = 0;
	virtual void CheckForInput() = 0;
};

#endif