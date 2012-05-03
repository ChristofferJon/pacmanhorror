#include "InputManager.h"

#pragma region Initialization

InputManager::InputManager()
{
	m_directInput = 0;
	m_kb = 0;
	m_ms = 0;

	dbg->getDbg()->print("%s\n", "Hello input");

	m_pDevice = NULL;
	ZeroMemory(&m_mouseState, sizeof( DIMOUSESTATE));
}

InputManager::~InputManager()
{
	shutDown();
}

bool InputManager::Initialize(HWND _hWnd, HINSTANCE hInstance, int _screenWidth, int _screenHeight)
{
	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;

	hWnd = _hWnd;

	if ( FAILED ( InitiateKeyBoard(hInstance) ) )
		return false;
	//	return dbg->fatalError(hWnd, "Keyboard failed to initiate");
	
	if ( FAILED ( InitiateMouse(hInstance) ) )
		return false;
	//	return dbg->fatalError(hWnd, "Mouse failed to initiate");

	ClearKeys();
	
	return true; 
}

bool InputManager::InitiateKeyBoard(HINSTANCE hInstance)
{
	HRESULT hResult;

	hResult = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if ( FAILED( hResult) )
		return false;

	hResult = m_directInput->CreateDevice(GUID_SysKeyboard, &m_kb, NULL);
	if ( FAILED( hResult) )
		return false;

	hResult = m_kb->SetDataFormat(&c_dfDIKeyboard);
	if ( FAILED( hResult) )
		return false;

	hResult = m_kb->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if ( FAILED ( hResult) )
		return false;

	hResult = m_kb->Acquire();
	if ( FAILED ( hResult) )
		return false;

	return true;
}

bool InputManager::InitiateMouse(HINSTANCE hInstance)
{
	if ( FAILED (m_directInput->CreateDevice(	GUID_SysMouse,
												&m_pDevice,
												NULL) ) )
												return false;


	if ( FAILED ( m_pDevice->SetDataFormat(&c_dfDIMouse) ) )
		return false;

	if ( FAILED ( m_pDevice->SetCooperativeLevel(	hWnd,
													DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
													return false;
	
	if ( FAILED ( m_pDevice->Acquire() ) )
		return false;

	//ShowCursor( TRUE );

	m_oldMouseState = m_mouseState;

	return true;
}

void InputManager::shutDown()
{
	if (m_kb)
	{
		m_kb->Unacquire();
		m_kb->Release();
		m_kb = 0;
	}
	if (m_ms)
	{
		m_ms->Unacquire();
		m_ms->Release();
		m_ms = NULL;
	}
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}
}

void InputManager::ClearKeys()
{
	for (int i = 0; i < 256; i++)
	{
		m_kbState[i] = 0;
		m_oldKbState[i] = 0;
	}
}

#pragma endregion

#pragma region Methods

bool InputManager::frame()
{
	if ( FAILED ( readKeyboard() ) )	// we've failed to contact the keyboard
		return false;

	if ( FAILED ( readMouse() ) )		// we've failed to contact the mouse
		return false;
	
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	return true;
}

bool InputManager::readMouse()
{
	HRESULT result = m_pDevice->GetDeviceState( sizeof( DIMOUSESTATE), (LPVOID)&m_mouseState);

	if ( FAILED (result) )
	{
		if ( result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)	//acquire if dierr_notacquired can lead to infinite loop?
		{
			m_pDevice->Acquire();
		}
		else
			return false;
	}

	return true;
}

bool InputManager::readKeyboard()
{
	HRESULT result;

	result = m_kb->GetDeviceState(sizeof(m_kbState), (LPVOID)&m_kbState);

	if ( FAILED (result) )
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))	//acquire if dierr_notacquired can lead to infinite loop?
			m_kb->Acquire();
		else
			return false;
	}

	return true;
}

#pragma endregion

#pragma region States

bool InputManager::isMLeftButton()
{
	if (m_mouseState.rgbButtons[0] & 0x80)
		return true;

	return false;
}

bool InputManager::isNewMLeftButton()
{
	return (m_mouseState.rgbButtons[0] & 0x80 
			&& m_oldMouseState.rgbButtons[0] != m_mouseState.rgbButtons[0]);
}

bool InputManager::isMRightButton()
{
	if (m_mouseState.rgbButtons[1] & 0x80)
		return true;

	return false;
}

DIMOUSESTATE InputManager::getMouseState()const
{
	return m_mouseState;
}

POINT* InputManager::getOldMousePos()
{
	return &mOldMousePos;
}

POINT* InputManager::getMousePos()
{
	return &pt;
}

// update old values to the current values
void InputManager::UpdateOldStates()
{
	// set old keyboard to equal the current keyboard
	memcpy(m_oldKbState, m_kbState, sizeof(m_kbState));

	// set old mouse to equal the current mouse
	m_oldMouseState = m_mouseState;
	mOldMousePos = pt;
}

// compare current with old state and only confirm if
// they don't match (meaning we need to let go of the
// key to be able to register a new press
bool InputManager::IsNewKeyPress(unsigned char _key)
{
	return (m_kbState[_key] & 0x80) 
			&& !(m_oldKbState[_key] & 0x80);
}

// we only want to know if a key press has occured, so
// we dont bother to compare current with old state
bool InputManager::IsContinousKeyPress(unsigned char _key)
{
	return (m_kbState[_key] & 0x80) 
			&& (m_oldKbState[_key] & 0x80);
}

bool InputManager::IsMouseIdle()
{
	if ( mOldMousePos.x == pt.x &&
		 mOldMousePos.y == pt.y )
		return true;

	return false;
}

#pragma endregion