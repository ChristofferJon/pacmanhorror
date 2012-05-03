#include "InGameScreen.h"


InGameScreen::InGameScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager) 
	: GameScreen(_name, _D3DManager, _inputManager)
{
}


InGameScreen::~InGameScreen()
{
}

void InGameScreen::Initialize()
{

}

void InGameScreen::CheckForInput()
{

}

void InGameScreen::Update(float dt)
{
	dbg->getDbg()->print("%s\n", "INGAMESCREEN->UPDATE()");
}

void InGameScreen::Draw()
{
	dbg->getDbg()->print("%s\n", "INGAMESCREEN->DRAW()");
}