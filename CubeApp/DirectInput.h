//=============================================================================
// DirectInput.h by Frank Luna (C) 2005 All Rights Reserved.
//
// Wraps initialization of immediate mode Direct Input, and provides 
// information for querying the state of the keyboard and mouse.
//=============================================================================


#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H

#include "stdafx.h"

//#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include "D3DUtils.h"
#include "D3DApp.h"


//5.2 Direct Input Primer
class DirectInput
{
public:
	DirectInput(DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	~DirectInput();
	void poll();
	bool keyDown(char key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();
private:
	// Make private to prevent copying of members of this class.
	DirectInput(const DirectInput& rhs);
	DirectInput& operator=(const DirectInput& rhs);
private:
	IDirectInput8* mDInput;

	IDirectInputDevice8* mKeyboard;
	char mKeyboardState[256];

	IDirectInputDevice8* mMouse;
	DIMOUSESTATE2 mMouseState;

	//Remembering window sent on construction, might need to change method
	HWND				 window;
};

//The methods and data members will become evident as you work through this section.
//Note that this class is designed to be instantiated only once.For convenient access, we declare the following global variable in DirectInput h :
extern DirectInput* gDInput;


#endif // DIRECT_INPUT_H