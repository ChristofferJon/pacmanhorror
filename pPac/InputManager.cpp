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

bool InputManager::initialize(HINSTANCE hInstance, int _screenWidth, int _screenHeight)
{
	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;

	m_hWnd = &hWnd;

	if ( FAILED ( InitiateKeyBoard(hInstance) ) )
		return false;
	//	return dbg->fatalError(hWnd, "Keyboard failed to initiate");
	
	if ( FAILED ( InitiateMouse(hInstance) ) )
		return false;
	//	return dbg->fatalError(hWnd, "Mouse failed to initiate");
	
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

	if ( FAILED ( m_pDevice->SetCooperativeLevel(	*m_hWnd,
													DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
													return false;
	
	if ( FAILED ( m_pDevice->Acquire() ) )
		return false;

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

#pragma endregion

#pragma region Methods

bool InputManager::frame()
{
	bool resultK = readKeyboard();

	if(!resultK)
		return false;

	bool resultM = readMouse();

	if (!resultM)
		return false;
	
	GetCursorPos(&pt);
	ScreenToClient(*m_hWnd, &pt);

	return true;
}

bool InputManager::readMouse()
{
	HRESULT result = m_pDevice->GetDeviceState( sizeof( DIMOUSESTATE), (LPVOID)&m_mouseState);

	if ( FAILED (result) )
	{
		if ( result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
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
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			m_kb->Acquire();
		else
			return false;
	}

	return true;
}

#pragma endregion

#pragma region States

bool InputManager::isEsc()
{
	if (m_kbState[DIK_ESCAPE] & 0x80)
		return true;

	return false;
}

bool InputManager::isEnter()
{
	bool isPushed;
	bool isEnter = false;
	if (!m_kbState[DIK_RETURN] & 0x80)
		isPushed = false;
	if (m_kbState[DIK_RETURN] & 0x80 && !isPushed)
	{
		isPushed = true;
		isEnter = true;
	}
	return isEnter;
}

bool InputManager::isSpace()
{
	if (m_kbState[DIK_SPACE] & 0x80)
		return true;

	return false;
}

bool InputManager::isShift()
{
	if (m_kbState[DIK_LSHIFT] & 0x80)
		return true;
	
	return false;
}

bool InputManager::isCtrl()
{
	if (m_kbState[DIK_RSHIFT] & 0x80)
		return true;

	return false;
}

bool InputManager::isMLeftButton()
{
	if (m_mouseState.rgbButtons[0] & 0x80)
		return true;

	return false;
}

bool InputManager::isNewMLeftButton()
{
	return (m_mouseState.rgbButtons[0] & 0x80 && m_oldMouseState.rgbButtons[0] != m_mouseState.rgbButtons[0]);
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

POINT* InputManager::getMousePos()
{
	return &pt;
}

#pragma endregion