
E:\Programmering\Github\pacmanhorror>@git.exe %*
#ifndef __INPUTMANAGER__
#define __INPUTMANAGER__

#include "Dbg.h"
#include <dinput.h>
#include <D3DX10.h>
#include <D3D10.h>

#pragma comment (lib, "d3d10.lib")
#pragma comment (lib, "dxguid.lib")

class InputManager
{
private:
	HWND hWnd;
	Dbg* dbg;

	LPDIRECTINPUTDEVICE8 m_pDevice;
	DIMOUSESTATE m_mouseState;

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_kb;
	IDirectInputDevice8* m_ms;
	unsigned char m_kbState[256];

	int	m_screenHeight;
	int m_screenWidth;

	bool readKeyboard();
	bool readMouse();

	bool InitiateKeyBoard(HINSTANCE hInstance);
	bool InitiateMouse(HINSTANCE hInstance);

	HWND* m_hWnd;

public:
	InputManager();
	~InputManager();

	bool initialize(HINSTANCE, int _screenWidth, int _screenHeight);
	void shutDown();
	bool frame();

	bool isEsc();
	bool isEnter();
	bool isSpace();
	bool isMLeftButton();
	bool isNewMLeftButton();
	bool isMRightButton();
	bool isShift();
	bool isCtrl();

	POINT pt;
	POINT mOldMousePos;
	POINT* getMousePos();

	DIMOUSESTATE m_oldMouseState;
	DIMOUSESTATE getMouseState()const;
};


#endif
E:\Programmering\Github\pacmanhorror>@set ErrorLevel=%ErrorLevel%

E:\Programmering\Github\pacmanhorror>@rem Restore the original console codepage.

E:\Programmering\Github\pacmanhorror>@chcp %cp_oem% > nul < nul
