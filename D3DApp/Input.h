//=============================================================================
// DirectInput.h by Frank Luna (C) 2005 All Rights Reserved.
//
// Wraps initialization of immediate mode Direct Input, and provides 
// information for querying the state of the keyboard and mouse.
//=============================================================================


#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H

//#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "D3DUtils.h"



//5.2 Direct Input Primer
class Input
{
public:
	Input(HINSTANCE instance, HWND mainWindow, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	~Input();

	void poll();
	bool keyDown(unsigned char key);
	bool keyPressed(unsigned char key);
	bool keyReleased(unsigned char key);
	bool mouseButtonDown(int button);
	bool mouseButtonPressed(int button);
	bool mouseButtonReleased(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();


	float mouseX, mouseY, mouseZ;

private:
	// Make private to prevent copying of members of this class.
	Input(const Input& rhs);
	Input& operator=(const Input& rhs);

private:
	IDirectInput8* mDInput;

	IDirectInputDevice8*	mKeyboard;
	char					mKeyboardState[256];
	char					mLastKeyboardState[256];

	IDirectInputDevice8*	mMouse;
	DIMOUSESTATE2			mMouseState;
	BYTE					mlastMouseButtons[8];
	POINT					mMousePos;

	//Remembering window sent on construction, might need to change method
	//HWND window;
};

//The methods and data members will become evident as you work through this section.
//Note that this class is designed to be instantiated only once.For convenient access, we declare the following global variable in DirectInput h :
extern Input* gDInput;

#endif // DIRECT_INPUT_H