#ifndef __CREDITSCREEN__
#define __CREDITSCREEN__

#include "MenuScreen.h"
#include "MainMenuScreen.h"

class CreditScreen : public MenuScreen
{
public:
	CreditScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~CreditScreen();

	void OnBack(CreditScreen* _me);
};

#endif