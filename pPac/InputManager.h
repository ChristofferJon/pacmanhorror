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

	int	m_screenHeight;
	int m_screenWidth;

	bool readKeyboard();
	bool readMouse();

	bool InitiateKeyBoard(HINSTANCE hInstance);
	bool InitiateMouse(HINSTANCE hInstance);

	unsigned char m_oldKbState[256];
	unsigned char m_kbState[256];

	void ClearKeys();

public:
	InputManager();
	~InputManager();

	bool Initialize(HWND _hWnd, HINSTANCE, int _screenWidth, int _screenHeight);
	void shutDown();
	bool frame();

	bool isMLeftButton();
	bool isNewMLeftButton();
	bool isMRightButton();

	POINT pt;
	POINT mOldMousePos;
	POINT* getMousePos();
	POINT* getOldMousePos();

	DIMOUSESTATE m_oldMouseState;
	DIMOUSESTATE getMouseState()const;

	void UpdateOldStates();
	bool IsNewKeyPress(unsigned char _key);
	bool IsContinousKeyPress(unsigned char _key);
	bool IsMouseIdle();
};


#endif