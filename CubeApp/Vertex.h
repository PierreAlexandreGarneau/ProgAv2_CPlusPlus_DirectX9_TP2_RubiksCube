#pragma once

#include "stdafx.h"
#include "D3DApp.h"

struct VertexPos
{
	VertexPos(float x, float y, float z)
		: pos(x, y, z) { }
	explicit VertexPos(D3DXVECTOR3 v)
		: pos(v) {}

	D3DXVECTOR3 pos;

	static IDirect3DVertexDeclaration9* decl;
};

struct VertexPosCol
{
	VertexPosCol(float x, float y, float z) 
		: pos(x,y,z), col(0xcccccccc)  {}
	VertexPosCol(float x, float y, float z, D3DCOLOR col)
		: pos(x, y, z), col(col)  {}
	VertexPosCol(D3DXVECTOR3 v, D3DCOLOR col)
		: pos(v), col(col) {}

	D3DXVECTOR3 pos;
	D3DCOLOR col;

	static IDirect3DVertexDeclaration9* decl;
};

void CreateAllVertexDeclaration();
void DestroyAllDeclaration();