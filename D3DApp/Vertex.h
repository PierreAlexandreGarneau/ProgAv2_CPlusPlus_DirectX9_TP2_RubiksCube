#pragma once

#include "stdafx.h"
#include "D3DApp.h"
//132
//7.4.1 Vertex Structure

//Because we are rendering in wireframe mode, the vertex structure we employ is very simple — all we need is position data:
//10.2.4.1 Vertex Structure
//The first thing we need to do is define a new vertex structure(and corresponding vertex declaration) :
struct VertexPN
{
	VertexPN()
		:pos(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f) {}
	VertexPN(float x, float y, float z,
		float nx, float ny, float nz)
		:pos(x, y, z), normal(nx, ny, nz) {}
	VertexPN(const D3DXVECTOR3& v, const D3DXVECTOR3& n)
		:pos(v),normal(n){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	static IDirect3DVertexDeclaration9* Decl;
};

//The new properties are in bold, and we have also updated Vertex.h/.cpp.
//Now our vertices have an extra color component; therefore, our vertex shader has an extra input parameter:

//9.2 Vertex Colors
//Recall that our vertex structures are flexible and we can include additional data; in particular, we can couple a color to each vertex.Then, in the rasterization stage
//of the rendering pipeline, these vertex colors are interpolated across the face of the triangle to generate pixel colors for the interior and boundary of the triangle.
//Thus, to add color, all we need to do is modify our vertex structure and the vertex and pixel shader slightly.

//Our new vertex structure, and its corresponding vertex declaration, looks like this:
struct VertexCol
{
	VertexCol(float x, float y, float z) : pos(x, y, z), col(0x00000000) {}
	VertexCol(float x, float y, float z, D3DCOLOR c)
				: pos(x, y, z), col(c) {}
	VertexCol(D3DXVECTOR3 v, D3DCOLOR col) : pos(v), col(col) {}

	D3DXVECTOR3 pos;
	D3DCOLOR col;
	static IDirect3DVertexDeclaration9* Decl;
};

void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();