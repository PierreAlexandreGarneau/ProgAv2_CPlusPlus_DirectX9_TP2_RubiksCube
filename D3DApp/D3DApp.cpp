#include "stdafx.h"
#include "resource.h"

#include "D3DApp.h"

extern D3DApp* gd3dApp = nullptr;
extern IDirect3DDevice9* gd3dDevice = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (gd3dApp != nullptr)
	{
		return gd3dApp->msgProc(message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

D3DApp::D3DApp()
	: mhMainWnd(nullptr)
	, devType(D3DDEVTYPE_HAL)
	, hInstance(nullptr)
	, d3dObject(nullptr)
{
}

D3DApp::D3DApp(HINSTANCE hInstance, int nCmdShow)
	: mhMainWnd(nullptr)
	, devType(D3DDEVTYPE_HAL)
	, hInstance(hInstance)
	, d3dObject(nullptr)
{
	// Initialise captions
	// Initialise les chaînes globales
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_D3DAPP, szWindowClass, MAX_LOADSTRING);

	OpenConsole();

	initMainWindow(nCmdShow);
	initDirect3D();

	//if (!initMainWindow(nCmdShow))
	//{
	//	MessageBox(0, L"InitMainWindow - Failed", 0, 0);
	//	PostQuitMessage(0);
	//}
	//
	//if (!initDirect3D())
	//{
	//	MessageBox(0, L"InitDirect3D - Failed", 0, 0);
	//	PostQuitMessage(0);
	//}
}

D3DApp::~D3DApp()
{
}

int D3DApp::run()
{
	MSG msg;
	msg.message = WM_NULL;
	ZeroMemory(&msg, (sizeof(MSG)));

	HACCEL hAccelTable =
		LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DAPP));

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else 
		{
			updateScene(0.0f);
			drawScene();
		}
	}
	return (int)msg.wParam;
}

LRESULT D3DApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Analyse les sélections de menu :
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), mhMainWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(mhMainWnd);
					break;
				default:
					return DefWindowProc(mhMainWnd, msg, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(mhMainWnd, &ps);
			// TODO: ajoutez le code de dessin qui utilise hdc ici...
			EndPaint(mhMainWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(mhMainWnd, msg, wParam, lParam);
	}
	return 0;
}

void D3DApp::initMainWindow(int nCmdShow)
{
	// Register class
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mhAppInst;
	wcex.hIcon = LoadIcon(mhAppInst, MAKEINTRESOURCE(IDI_D3DAPP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_D3DAPP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassExW(&wcex))
	{
		return;
	}

	//RECT r = { 0, 0, 800, 600 };
	// Create the window
	mhMainWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			800, 
			600, 
			nullptr,nullptr, 
			mhAppInst, 
			nullptr);
	//mhMainWnd = CreateWindowW(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,
	//	r.left,
	//	r.top,
	//	r.right,
	//	r.bottom,
	//	0, 0,
	//	mhAppInst,
	//	0);

	if (!mhMainWnd)
	{
		return;
	}

	ShowWindow(mhMainWnd, nCmdShow);
	UpdateWindow(mhMainWnd);

	return;
}

void D3DApp::initDirect3D()
{
	// Step 1
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3dObject)
		return;

	// Step 2
	D3DDISPLAYMODE mode;
	HR(d3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode));
	HR(d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, devType, mode.Format, mode.Format, true));
	HR(d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, devType, mode.Format, mode.Format, false));

	// Step 3
	D3DCAPS9 caps;
	HR(d3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, devType, &caps));

	DWORD devBehaviourFlags = 0;
	devBehaviourFlags |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		? D3DCREATE_HARDWARE_VERTEXPROCESSING
		: D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if ((caps.DevCaps & D3DDEVCAPS_PUREDEVICE) && 
		(devBehaviourFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING))
	{
		devBehaviourFlags |= D3DCREATE_PUREDEVICE;
	}

	// Step 4
	md3dPP.BackBufferWidth = 0;
	md3dPP.BackBufferHeight = 0;
	md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	md3dPP.BackBufferCount = 1;
	md3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	md3dPP.MultiSampleQuality = 0;
	md3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	md3dPP.hDeviceWindow = mhMainWnd;
	md3dPP.Windowed = true;
	md3dPP.EnableAutoDepthStencil = true;
	md3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	md3dPP.Flags = 0;
	md3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	md3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 5
	HR(d3dObject->CreateDevice(D3DADAPTER_DEFAULT, devType, nullptr, devBehaviourFlags, &md3dPP, &gd3dDevice));

}

void D3DApp::OpenConsole()
{
	//standard input/ output/ error file pointers
	FILE *fpStdIn, *fpStdOut, *fpStdErr;

	// Enable run-time memory check for debug build
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (AllocConsole())
	{
		//Assign the stdin/ stdout/ stderr streams to the newly created console
		_tfreopen_s(&fpStdIn, _T("CONIN$"), _T("r"), stdin);
		_tfreopen_s(&fpStdOut, _T("CONOUT$"), _T("w"), stdout);
		_tfreopen_s(&fpStdErr, _T("CONOUT$"), _T("w"), stderr);
	}
#endif
}
