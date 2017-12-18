#include "stdafx.h"
#include "Vertex.h"

IDirect3DVertexDeclaration9* VertexPN::Decl = nullptr;
IDirect3DVertexDeclaration9* VertexCol::Decl = nullptr;

//The structure has some convenience constructors, and note also that we include a static vertex declaration.We only need one vertex declaration per structure, so it
//is nice to couple it to the vertex structure as a static data member.

//The vertex declaration is described and created with the following code :
//9.2 Vertex Colors
void InitAllVertexDeclarations()
{
	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{ 
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
								D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};
	HR(gd3dDevice->CreateVertexDeclaration(VertexPosElements,
											&VertexPN::Decl));

	D3DVERTEXELEMENT9 VertexColElements[] = 
	{
	{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
							D3DDECLUSAGE_POSITION, 0 },
	{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, 
								D3DDECLUSAGE_COLOR, 0 },
	D3DDECL_END()
	};
	HR(gd3dDevice->CreateVertexDeclaration(VertexColElements, 
										&VertexCol::Decl));

}
//132
//Recall that as we progress through this book, we add all of our vertex structure definitions to the source code file Vertex.h.The global function InitAll
//VertexDeclarations provides a global function from which we create all of our vertex declarations in one localized place.As we add new vertex structures to
//Vertex.h, we also update this function to create its corresponding vertex declaration.

//Similarly, we have a global function that destroys all vertex declarations in one localized place :
void DestroyAllVertexDeclarations()
{
	ReleaseCOM(VertexPN::Decl);
	ReleaseCOM(VertexCol::Decl);
}
