#include "CreditScreen.h"

void BackSelected(Screen* _screen)
{
	CreditScreen* me = (CreditScreen*)_screen;
	me->OnExit(me);
}


CreditScreen::CreditScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager)
	: MenuScreen( _name, _D3DManager, _inputManager )
{
	ResourceHandler* rm = new ResourceHandler(mD3DManager);
	mSprite = rm->getSprite( 110 );

	// entries & events
	MenuEntry* credJ = new MenuEntry("Christoffer", NULL, 110);
	MenuEntry* credP = new MenuEntry("Christopher", NULL, 110);
	MenuEntry* credH = new MenuEntry("Penk H", NULL, 110);
	MenuEntry* credL = new MenuEntry("Brony J", NULL, 110);
	MenuEntry* credS = new MenuEntry("Emperor V", NULL, 110);
	MenuEntry* back = new MenuEntry("Back", NULL, 110);

	back->Selected.add( BackSelected );

	mMenuEntries.push_back( credJ );
	mMenuEntries.push_back( credP );
	mMenuEntries.push_back( credH );
	mMenuEntries.push_back( credL );
	mMenuEntries.push_back( credS );
	mMenuEntries.push_back( back );

	int oX = 50;
	int oY = 100;

	for each (MenuEntry* m in mMenuEntries)
	{
		m->Initialize( oX, oY );
		oY += 50;
	}
}


CreditScreen::~CreditScreen()
{
}


void CreditScreen::OnExit(CreditScreen* _me)
{
	exit ( 0 );
}