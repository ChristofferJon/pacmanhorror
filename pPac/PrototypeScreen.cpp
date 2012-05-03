#include "PrototypeScreen.h"


PrototypeScreen::PrototypeScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager)
	: GameScreen(_name, _D3DManager, _inputManager)
{
}


PrototypeScreen::~PrototypeScreen()
{
}

void PrototypeScreen::Initialize()
{

}

void PrototypeScreen::CheckForInput()
{

}

void PrototypeScreen::Update(float dt)
{
	dbg->getDbg()->print("%s\n", "PROTOTYPESCREEN->UPDATE()");
}

void PrototypeScreen::Draw()
{
	dbg->getDbg()->print("%s\n", "PROTOTYPESCREEN->DRAW()");
}