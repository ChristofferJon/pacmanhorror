#ifndef __CREDITSCREEN__
#define __CREDITSCREEN__

#include "MenuScreen.h"

class CreditScreen : public MenuScreen
{
public:
	CreditScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager);
	~CreditScreen();

	void OnExit(CreditScreen* _me);
};

#endif