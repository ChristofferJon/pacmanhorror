#ifndef __MAINMENUSCREEN__
#define __MAINMENUSCREEN__

#include "MenuScreen.h"
#include "CreditScreen.h"
#include "InGameScreen.h"

class MainMenuScreen : public MenuScreen
{
public:
	MainMenuScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~MainMenuScreen();

	void OnNewGame(MainMenuScreen* _me);
	void OnExit(MainMenuScreen* _me);

	void OnCredits( MainMenuScreen* _me );
};

#endif