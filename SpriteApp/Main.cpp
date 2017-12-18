#include "stdafx.h"

#include "resource.h"

#include "SpriteApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE prevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	gd3dApp = new CubeApp(hInstance, nCmdShow);

	return gd3dApp->Run();
}