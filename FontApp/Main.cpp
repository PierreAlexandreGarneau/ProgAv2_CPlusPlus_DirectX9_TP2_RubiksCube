#include "stdafx.h"

#include "resource.h"

#include "FontApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE prevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	gD3DApp = new FontApp(hInstance, nCmdShow);

	return gD3DApp->Run();
}