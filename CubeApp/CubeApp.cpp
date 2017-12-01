#include "stdafx.h"
#include "CubeApp.h"

CubeApp::CubeApp()
{
}

CubeApp::CubeApp(HINSTANCE hInstance, int nCmdShow)
	: D3DApp(hInstance, nCmdShow)
	, currRot(0.f)
	, eyePos(0.f, 0.f, 2.f)
	, target(0.f, 0.f, 0.f)
	, up(0.f, 1.0f, 0.f)
{
	CreateAllVertexDeclaration();

	// Build Vertex Buffer
	HR(gD3DDevice->CreateVertexBuffer(
		4 * sizeof(VertexPosCol), 0, 0, D3DPOOL_MANAGED, &mVB, 0));

	VertexPosCol* vertices;

	HR(mVB->Lock(0, 0, (void**)&vertices, 0));

	// Local de mes vertices
	vertices[0] = VertexPosCol(-0.5f, 0.5f, 0.f, 0xFFFFFFFF);
	vertices[1] = VertexPosCol(-0.5f, -0.5f, 0.f, 0xFF000000);
	vertices[2] = VertexPosCol(0.5f, -0.5f, 0.f, 0x00FF0000);
	vertices[3] = VertexPosCol(0.5f, 0.5f, 0.f, 0x0000FF00);

	HR(mVB->Unlock());

	// Build Index Buffer
	HR(gD3DDevice->CreateIndexBuffer(
		6 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0));

	WORD* k;

	HR(mIB->Lock(0, 0, (void**)&k, 0));

	k[0] = 0; k[1] = 1; k[2] = 2;
	k[3] = 2; k[4] = 3; k[5] = 0;

	HR(mIB->Unlock());

	HR(D3DXCreateEffectFromFileW(
		gD3DDevice, L"Transform.fx", 0, 0, D3DXSHADER_DEBUG, 0, &mFx, &mErrors));

	if (mErrors)
	{
		MessageBoxW(0, (LPCWSTR)mErrors->GetBufferPointer(), 0, 0);
	}

	mhTech = mFx->GetTechniqueByName("FogTech");
	mFx->SetTechnique(mhTech);

	mhWVP = mFx->GetParameterByName(0, "gWVP");
	mhEyePos = mFx->GetParameterByName(0, "gEyePos");
	mhFogColor = mFx->GetParameterByName(0, "gFogColor");
	mhFogStart = mFx->GetParameterByName(0, "gFogStart");
	mhFogRange = mFx->GetParameterByName(0, "gFogRange");

	HR(mFx->SetVector(mhFogColor, &D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f)));
	HR(mFx->SetFloat(mhFogStart, 5.0f));
	HR(mFx->SetFloat(mhFogRange, 25.0f));

	D3DXMatrixLookAtRH(&view, &eyePos, &target, &up);
	D3DXMatrixPerspectiveFovRH(&proj, D3DX_PI / 4,
		(float)d3dPP.BackBufferWidth / (float)d3dPP.BackBufferHeight, 0.01f, 1000.0f);

	// Fixed pipeline
	//HR(gD3DDevice->SetTransform(D3DTS_VIEW, &view));
	//HR(gD3DDevice->SetTransform(D3DTS_PROJECTION, &proj));
	
	//HR(gD3DDevice->SetRenderState(D3DRS_LIGHTING, false));
	//HR(gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
	//HR(gD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
}

CubeApp::~CubeApp()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);

	DestroyAllDeclaration();
}

void CubeApp::Update()
{
	currRot += 0.0001f;
}

void CubeApp::Draw()
{
	HR(gD3DDevice->Clear(0, 0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128,128, 128), 1.0f, 0));

	HR(gD3DDevice->SetStreamSource(0, mVB, 0, sizeof(VertexPosCol)));
	HR(gD3DDevice->SetVertexDeclaration(VertexPosCol::decl));
	HR(gD3DDevice->SetIndices(mIB));

	HR(mFx->SetValue(mhEyePos, &eyePos, sizeof(D3DXVECTOR3)));
	
	// Compute WVP
	
	D3DXMATRIX Ry;
	D3DXMATRIX T;

	D3DXMatrixTranslation(&T, 0.f, 0.f, -20.0f);
	D3DXMatrixRotationAxis(&Ry, &D3DXVECTOR3(0, 1, 0), currRot);

	D3DXMATRIX WVP = Ry * T * view * proj;
	mFx->SetMatrix(mhWVP, &WVP);

	// Draw 3D
	HR(gD3DDevice->BeginScene());

	UINT nbPass;
	HR(mFx->Begin(&nbPass, 0));

	for (int i = 0; i < nbPass; i++)
	{
		HR(mFx->BeginPass(i));
		
		HR(gD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2));

		HR(mFx->EndPass());
	}

	HR(mFx->End());

	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}
