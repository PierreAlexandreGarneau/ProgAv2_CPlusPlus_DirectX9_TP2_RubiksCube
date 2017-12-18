//=============================================================================
// DirectInput.cpp by Frank Luna (C) 2005 All Rights Reserved.
//=============================================================================

#include "stdafx.h"
#include "Input.h"

extern Input* gDInput = 0;

Input::Input(HINSTANCE instance, HWND mainWindow, DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));

	HR(DirectInput8Create(instance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&mDInput, 0));

	HR(mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0));
	HR(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
	HR(mKeyboard->SetCooperativeLevel(mainWindow,
		keyboardCoopFlags));

	HR(mKeyboard->Acquire());

	HR(mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0));
	HR(mMouse->SetDataFormat(&c_dfDIMouse2));
	HR(mMouse->SetCooperativeLevel(mainWindow,mouseCoopFlags));

	HR(mMouse->Acquire());
}

//5.2.3 Cleanup
//To clean up Direct Input, we simply unacquire the devices and release the COM interfaces.
Input::~Input()
{
	ReleaseCOM(mDInput);
	mKeyboard->Unacquire();
	mMouse->Unacquire();
	ReleaseCOM(mKeyboard);
	ReleaseCOM(mMouse);
}

void Input::poll()
{
	// Poll keyboard.
	HRESULT hr = mKeyboard->GetDeviceState(sizeof(mKeyboardState),(void**)&mKeyboardState);
	if (FAILED(hr))
	{
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

		// Try to acquire for next time we poll.
		hr = mKeyboard->Acquire();
	}

	// Poll mouse.
	hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2),(void**)&mMouseState);
	if (FAILED(hr))
	{
		memcpy(mlastMouseButtons, mMouseState.rgbButtons, sizeof(mlastMouseButtons));

		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&mMouseState, sizeof(mMouseState));

		// Try to acquire for next time we poll.
		hr = mMouse->Acquire();
	}
}

bool Input::keyDown(unsigned char key)
{
	return (mKeyboardState[key] & 0x80) != 0;
}

bool Input::keyPressed(unsigned char key)
{
	return (!(mLastKeyboardState[key] & 0x80) != 0) && (mKeyboardState[key] & 0x80) != 0;
}

bool Input::keyReleased(unsigned char key)
{
	return ((mLastKeyboardState[key] & 0x80) != 0) && !((mKeyboardState[key] & 0x80) != 0);
}

bool Input::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

bool Input::mouseButtonPressed(int button)
{
	return false;
}

bool Input::mouseButtonReleased(int button)
{
	return false;
}

float Input::mouseDX()
{
	return (float)mMouseState.lX;
}

float Input::mouseDY()
{
	return (float)mMouseState.lY;
}

float Input::mouseDZ()
{
	return (float)mMouseState.lZ;
}