#include "stdafx.h"
#include "resource.h"
#include "CubeApp.h"

#include "Camera.h"
#include "DirectInput.h"
#include "D3DUtils.h"
//extern Camera* gCamera = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
				_In_opt_ HINSTANCE prevInstance,
							_In_ LPWSTR lpCmdLine,
							_In_ int nCmdShow)
{
	gd3dApp = new CubeApp(hInstance, nCmdShow);

	//Input di(hInstance, gd3dApp->getMainWnd(), DISCL_NONEXCLUSIVE |
	//			DISCL_FOREGROUND,
	//			DISCL_NONEXCLUSIVE |
	//			DISCL_FOREGROUND);
	//gDInput = &di;
	
	//Camera allo;
	//gCamera = &allo;

	return gd3dApp->run();
}
