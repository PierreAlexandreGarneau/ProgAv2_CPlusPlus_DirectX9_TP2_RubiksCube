#pragma once

#include "D3DApp.h"

class FontApp
	: public D3DApp
{

public:
	FontApp();
	FontApp(HINSTANCE hInstance, int nCmdShow);
	~FontApp()
	{
		ReleaseCOM(mFont);
	}

	void Update();
	void Draw();

private:
	ID3DXFont* mFont;

};