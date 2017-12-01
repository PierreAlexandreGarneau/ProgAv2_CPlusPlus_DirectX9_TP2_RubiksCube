#include "stdafx.h"
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

	D3DXCreateFontIndirectW(gD3DDevice, &fontDesc, &mFont);
}

void FontApp::Update()
{
}

void FontApp::Draw()
{
	HR(gD3DDevice->Clear(0, 0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0));

	RECT formatRect;
	GetClientRect(hWnd, &formatRect);

	HR(gD3DDevice->BeginScene());

	HR(mFont->DrawTextW(0, L"Hello World!", -1, 
		&formatRect, DT_CENTER | DT_VCENTER, 
		D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256)));

	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}
