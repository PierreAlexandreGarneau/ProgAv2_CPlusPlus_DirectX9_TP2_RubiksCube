#pragma once

#include "stdafx.h"
#include "D3DUtils.h"

#define MAX_LOADSTRING 100

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

class D3DApp
{
public:
	D3DApp();
	D3DApp(HINSTANCE hInstance, int nCmdShow);
	~D3DApp();

	int Run();

	virtual void Update() {}
	virtual void Draw() {}

	LRESULT MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HWND hWnd;
	D3DPRESENT_PARAMETERS d3dPP;

	virtual int InitMainWindow(int nCmdShow);
	virtual int InitDirect3D();

private:
	void OpenConsole();

	D3DDEVTYPE devType;
	HINSTANCE hInstance;
	IDirect3D9* d3dObject;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
};

extern D3DApp* gD3DApp;
extern IDirect3DDevice9* gD3DDevice;
