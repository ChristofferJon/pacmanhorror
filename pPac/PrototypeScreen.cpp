#include "PrototypeScreen.h"


PrototypeScreen::PrototypeScreen() : GameScreen()
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

void PrototypeScreen::Update()
{
	dbg->getDbg()->print("%s\n", "PROTOTYPESCREEN->UPDATE()");
}

void PrototypeScreen::Draw()
{
	dbg->getDbg()->print("%s\n", "PROTOTYPESCREEN->DRAW()");
}