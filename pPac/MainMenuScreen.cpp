#include "MainMenuScreen.h"

void NewGameSelected(Screen* _screen)
{
	MainMenuScreen* me = (MainMenuScreen*)_screen;
	me->OnNewGame(me);
}

void CreditSelected( Screen* _screen)
{
	MainMenuScreen* me = (MainMenuScreen*)_screen;
	me->OnCredits(me);
}

void ExitSelected(Screen* _screen)
{
	MainMenuScreen* me = (MainMenuScreen*)_screen;
	me->OnExit(me);
}

MainMenuScreen::MainMenuScreen(string _name, D3DManager* _D3DManager, InputManager* _inputManager)
	: MenuScreen(_name, _D3DManager, _inputManager)
{
	ResourceHandler* rm = new ResourceHandler(mD3DManager);
	mSprite = rm->getSprite( 110 );



	// entries & events
	MenuEntry* newGame = new MenuEntry("New Game", NULL, 110);
	MenuEntry* options = new MenuEntry("Options", NULL, 110);
	MenuEntry* credits = new MenuEntry("Credits", NULL, 110);
	MenuEntry* exit = new MenuEntry("Exit", NULL, 110);

	newGame->Selected.add( NewGameSelected );
	//
	credits->Selected.add( CreditSelected );
	exit->Selected.add( ExitSelected );

	mMenuEntries.push_back( newGame );
	mMenuEntries.push_back( options );
	mMenuEntries.push_back( credits );
	mMenuEntries.push_back( exit );

	int oX = 50;
	int oY = 100;

	for each (MenuEntry* m in mMenuEntries)
	{
		m->Initialize( oX, oY );
		oY += 50;
	}
}


MainMenuScreen::~MainMenuScreen()
{
	MenuScreen::~MenuScreen();
}

void MainMenuScreen::OnNewGame(MainMenuScreen* _me)
{
	mScreenMediator->RemoveAll();	// not sure this actually works as intended
	mScreenMediator->AddNewScreen( new InGameScreen( "InGame", mD3DManager, mInput ) );
}

void MainMenuScreen::OnExit(MainMenuScreen* _me)
{
	exit ( 0 );
}

void MainMenuScreen::OnCredits( MainMenuScreen* _me )
{
	// we dont remove ourself here because the mainmenu acts as a hub
	// for the other menus
	mScreenMediator->AddNewScreen( new CreditScreen( "Credit Roll", mD3DManager, mInput ) );
}