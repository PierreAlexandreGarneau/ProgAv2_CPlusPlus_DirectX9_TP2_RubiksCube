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

	HWND getMainWnd() { return mhMainWnd; }
	HINSTANCE getAppInst() { return mhAppInst; }

	virtual bool checkDeviceCaps() { return true; }
	virtual void onLostDevice() {}

	virtual void updateScene(float dt) {}
	virtual void drawScene() {}

	virtual void initMainWindow() {}
	virtual void initMainWindow(int nCmdShow);
	virtual void initDirect3D();

	virtual int run();
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void enableFullScreenMode(bool enable);
	bool isDeviceLost();

protected:

	HINSTANCE				mhAppInst;
	HWND					mhMainWnd;
	IDirect3D9*				md3dObject;
	bool					mAppPaused;
	D3DPRESENT_PARAMETERS	md3dPP;

private:
	void OpenConsole();

	D3DDEVTYPE devType;
	HINSTANCE hInstance;
	IDirect3D9* d3dObject;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
};

extern D3DApp* gd3dApp;
extern IDirect3DDevice9* gd3dDevice;
