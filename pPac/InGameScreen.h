#ifndef __INGAMESCREEN__
#define __INGAMESCREEN__

#include "GameScreen.h"

class InGameScreen : public GameScreen
{
public:
	InGameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~InGameScreen();

	void Initialize( ResourceHandler* _resources);
	void CheckForInput( float dt );
	void Update( float dt );
	void Draw( );
};

#endif