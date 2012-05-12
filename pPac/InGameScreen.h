#ifndef __INGAMESCREEN__
#define __INGAMESCREEN__

#include "GameScreen.h"

class InGameScreen : public GameScreen
{
public:
	InGameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~InGameScreen();

	virtual void Initialize( ResourceHandler* _resources);
	virtual void CheckForInput( float dt );
	virtual void Update( float dt );
	virtual void Draw( );
};

#endif