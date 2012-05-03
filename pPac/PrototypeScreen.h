#ifndef __PROTOTYPESCREEN__
#define __PROTOTYPESCREEN__

#include "GameScreen.h"

class PrototypeScreen : public GameScreen
{
public:
	PrototypeScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~PrototypeScreen();

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Initialize();
	virtual void CheckForInput();
};

#endif