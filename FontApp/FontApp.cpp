#/*include "stdafx.h"
#include "FontApp.h"

FontApp::FontApp()
{
}

FontApp::FontApp(HINSTANCE hInstance, int nCmdShow)
	: D3DApp(hInstance, nCmdShow)
{
	D3DXFONT_DESCW fontDesc;
	fontDesc.Height = 80;
	fontDesc.Width = 40;
	fontDesc.Weight = FW_BOLD;
	fontDesc.MipLevels = 0;
	fontDesc.Italic = true;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(fontDesc.FaceName, L"Times New Roman");

	D3DXCreateFontIndirectW(gd3dDevice, &fontDesc, &mFont);
}*/

//void FontApp::updateScene(float dt)
//{
//}

//void FontApp::drawScene()
//{
//	HR(gd3dDevice->Clear(0, 0,
//		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
//		D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0));
//
//	RECT formatRect;
//	GetClientRect(mhMainWnd, &formatBRect);
//
//	HR(gd3dDevice->BeginScene());
//
//	HR(mFont->DrawTextW(0, L"Hello World!", -1, 
//		&formatRect, DT_CENTER | DT_VCENTER, 
//		D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256)));
//
//	HR(gd3dDevice->EndScene());
//
//	HR(gd3dDevice->Present(0, 0, 0, 0));
//}
