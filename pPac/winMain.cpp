#pragma region Include Statements

#include <Windows.h>
#include <tchar.h>
#include "AppMain.h"
#include "Ini_Util.h"
#include "Parser.h"

#pragma endregion

#pragma region Application Globals

// window attributes
HWND				hWnd;
const LPCSTR		appName =	"Pac 0.01";

// Instances
AppMain main = AppMain();
Parser* parser;

#pragma endregion

#pragma region Procedures

LRESULT CALLBACK wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_DESTROY :	PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
}

#pragma endregion

#pragma region Initialization

bool initWindow( HWND &hWnd, HINSTANCE hInstance, int width, int height )
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof( WNDCLASSEX );
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= ( WNDPROC )wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT( "PAC" );
	wcex.hIconSm		= 0;

	RegisterClassEx( &wcex );

	// set size and adjust window
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect( &rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE );

	// create window
	hWnd = CreateWindow(	"PAC",
							appName,
							WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							rect.right - rect.left,
							rect.bottom - rect.top,
							NULL,
							NULL,
							hInstance,
							NULL );

	// handle creation failed
	if ( !hWnd )
		return false;

	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );

	return true;
}

#pragma endregion

#pragma region winMain

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// instance parser
	parser = new Parser();
	parser->Load("GFX.dat");

	// set up window
	if ( !initWindow (	hWnd, 
						hInstance, 
						parser->getIntOfKey("resx"), 
						parser->getIntOfKey("resy") ) )
		return 0;

	// intialize AppMain
	if ( main.Initialize(parser) == false )
		return 0;

	// main message loop
	MSG msg = {	0 };

	while ( WM_QUIT != msg.message )
	{
		while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) == TRUE )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}		

		main.Update();
	}

	// ShutDown
	main.~AppMain();

	return ( int )msg.wParam;
}

#pragma endregion