#pragma once

#include "D3DApp.h"
#include "Vertex.h"

class Triangle
	: public D3DApp
{

public:
	Triangle();
	Triangle(HINSTANCE hInstance, int nCmdShow);
	~Triangle();

	void Update();
	void Draw();

private:
	float currRot;

	ID3DXEffect* mFx;
	ID3DXBuffer* mErrors;

	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;
	D3DXHANDLE mhEyePos;
	D3DXHANDLE mhFogColor;
	D3DXHANDLE mhFogStart;
	D3DXHANDLE mhFogRange;

	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9* mIB;

	// Camera
	D3DXMATRIX view;
	D3DXMATRIX proj;

	D3DXVECTOR3 eyePos;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;
};