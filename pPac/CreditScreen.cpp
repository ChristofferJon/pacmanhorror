#include "CreditScreen.h"

void BackSelected(Screen* _screen)
{
	CreditScreen* me = (CreditScreen*)_screen;
	me->OnBack(me);
}

void Selected(Screen* _screen)
{
	CreditScreen* me = (CreditScreen*)_screen;
	me->OnSelect();
}

CreditScreen::CreditScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager)
	: MenuScreen( _name, _D3DManager, _inputManager )
{

}


CreditScreen::~CreditScreen()
{
	MenuScreen::~MenuScreen();
}

void CreditScreen::Initialize( ResourceHandler* _resources )
{
	MenuScreen::Initialize( _resources );

	mSprite = mResources->getSprite( 700 );
	mRP = mResources->getRenderPackage( 901 );

	// entries & events
	MenuEntry* credJ = new MenuEntry("Christoffer", NULL,	606);
	MenuEntry* credP = new MenuEntry("Christopher", NULL,	602);
	MenuEntry* credH = new MenuEntry("Penkman",		NULL,	603);
	MenuEntry* credL = new MenuEntry("Brony J",		NULL,	604);
	MenuEntry* credS = new MenuEntry("Emperor V",	NULL,	605);
	MenuEntry* back = new MenuEntry("Back",			NULL,	601);

	back->Selected.add( BackSelected );
	credJ->Selected.add( Selected );
	credP->Selected.add( Selected );
	credH->Selected.add( Selected );
	credL->Selected.add( Selected );
	credS->Selected.add( Selected );

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

void CreditScreen::OnBack(CreditScreen* _me)
{
	mSoundManager->PlaySound ( mMenuEntries[selectedEntry]->mSFXid );
	mScreenMediator->RemoveMe( this );
}

void CreditScreen::OnSelect()
{
	for ( int i = 0; i < mMenuEntries.size(); i++)
		mMenuEntries[i]->mText = "";

	string resp[] = { "DOA", "SNAFU", "TBD", "MIA", "AWOL" };
	mMenuEntries[selectedEntry]->mText += " : " + resp[selectedEntry];
}