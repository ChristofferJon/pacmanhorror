#ifndef __GameScreen__
#define __GameScreen__

#include "Screen.h"

class GameScreen : public Screen
{
public:
	GameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~GameScreen();

protected:
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Initialize();
	virtual void CheckForInput();
};

#endif