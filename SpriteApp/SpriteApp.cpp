#include "stdafx.h"
#include "SpriteApp.h"

CubeApp::CubeApp()
{
}

CubeApp::CubeApp(HINSTANCE hInstance, int nCmdShow)
	: D3DApp(hInstance, nCmdShow)
	, position(-100.f, 0.f, 0.f)
	, eyePos(0.f, 0.f, -10.f)
	, target(0.f, 0.f, 0.f)
	, up(0.f, -1.0f, 0.f)
{
	HR(D3DXCreateSprite(gD3DDevice, &spriteBatch));

	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"Retro-Star-icon.png", 0, 0, 1, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 
		D3DCOLOR_XRGB(255, 255, 255), &texInfo, nullptr, &texture));

	center = D3DXVECTOR3(texInfo.Width/2, texInfo.Height/2, 0.f);

	D3DXMatrixLookAtRH(&view, &eyePos, &target, &up);
	D3DXMatrixOrthoRH(&proj, d3dPP.BackBufferWidth, d3dPP.BackBufferHeight, 0.01f, 1000.0f);

	// Fixed pipeline
	HR(gD3DDevice->SetRenderState(D3DRS_LIGHTING, false));
	HR(gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

	HR(gD3DDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gD3DDevice->SetTransform(D3DTS_PROJECTION, &proj));
}

void CubeApp::Update()
{
}

void CubeApp::Draw()
{
	HR(gD3DDevice->Clear(0, 0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0));

	HR(gD3DDevice->BeginScene());
	
	HR(spriteBatch->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_DONOTMODIFY_RENDERSTATE));

	// Draw here
	HR(spriteBatch->Draw(texture, 0, &center, &position, D3DCOLOR_XRGB(255, 255, 255)));
	
	// Vernissage
	HR(spriteBatch->Flush());

	HR(spriteBatch->End());

	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}
