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

