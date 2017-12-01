#include "stdafx.h"
#include "Vertex.h"

IDirect3DVertexDeclaration9* VertexPos::decl = nullptr;
IDirect3DVertexDeclaration9* VertexPosCol::decl = nullptr;

void CreateAllVertexDeclaration()
{
	// VERTEXPOS
	D3DVERTEXELEMENT9 posElements[] = { 
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};

	HR(gD3DDevice->CreateVertexDeclaration(posElements, &VertexPos::decl));

	// VERTEXPOSCOL
	D3DVERTEXELEMENT9 posColElements[] = 
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};

	HR(gD3DDevice->CreateVertexDeclaration(posColElements, &VertexPosCol::decl));

}

void DestroyAllDeclaration()
{
	ReleaseCOM(VertexPos::decl);
	ReleaseCOM(VertexPosCol::decl);
}
