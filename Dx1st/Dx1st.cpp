#include "stdafx.h"

#include <math.h>
#include <iostream>
#include <iomanip>
#include <d3dx9.h>

// Surcharge d'opêrateur <<
std::ostream& operator<<(std::ostream& os, D3DXVECTOR3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

// Surcharge d'opêrateur <<
std::ostream& operator<<(std::ostream& os, D3DXVECTOR4& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, D3DXMATRIX& m)
{
	for (UINT8 i = 0; i < 4; i++)
	{
		for (UINT8 j = 0; j < 4; j++)
		{
			os << m(i, j) << "\t";
		}
		os << std::endl;
	}
	return os;
}

typedef short JInt, KInt;

typedef struct Coord3D 
{
	int x, y;
}
Point, Vector3, *LPVector3;

int main()
{
	FLOAT vector3[] = { 1,2,3,5,6 };
	D3DXVECTOR3 v = D3DXVECTOR3(vector3);
	D3DXVECTOR3 v2 = D3DXVECTOR3(1.f, 2.f, 3.f);
	
	// Operateur d'égalité valide
	if (v == v2)
	{
		std::cout << "OK" << std::endl;
	}
	
	// De vector3 vers tableau
	FLOAT* vector3_2 = (FLOAT*)v;
	
	std::cout << "(" <<  v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
	
	
	D3DXVECTOR3 test = { 1.0f, 0.0f, 0.0f };
	
	for (int i = 0; i < 10; i++)
	{
		test.x += 0.1f;
	}
	
	if (D3DXVec3Length(&v) != 1.0f)
	{
		D3DXVECTOR3 norm;
		if (fabs(D3DXVec3Length(
			D3DXVec3Normalize(&norm , &v)) - 1.0f) < 0.0001f)
		{
			std::cout << "Ok\n";
		}
	}

	{	// Exercice Cross product
	
		// Un triangle défini par les points: A = (0,0,0) B = (0,1,3) et C = (5,1,0)
		// Trouver un vecteur orthogonal à ce triangle
	
		D3DXVECTOR3 b;
		D3DXVECTOR3 c; 
		D3DXVECTOR3 cross;
	
		b = D3DXVECTOR3(0, 1, 3);
		c = D3DXVECTOR3(5, 1, 0);
	
		D3DXVec3Cross(&cross, &b, &c);
	
		std::cout << "Cross: " << cross << std::endl;
	}

	{
		// 4. Soit les vecteurs 
		// Determiner si l'angle est aigu, obtus, ou perpendiculaire
		// a) u = (1, 1, 1) et v= (2, 2, 2)
		// b) u = (1, 1, 0) et v= (-2, 2, 0)
		// c) u = (-1, -1, -1) v= (3, 1, 0)
	
		// 5.Trouver l'angle entre ces 2 vecteurs 
		// u=(-2,1,4 et v=(3,-4,1)
		
		// 6. Demontrez que ces enoncés sont vrais.

		// a) u dot v == v dot u
		{
			D3DXVECTOR3 u(1, 1, 0);
			D3DXVECTOR3 v(0, 1, 1);

			std::cout << "A: ";
			if (D3DXVec3Dot(&u, &v) == D3DXVec3Dot(&v, &u))
			{
				std::cout << "VRAI" << std::endl;
			}
		}

		// b) u dot (v + w) == u dot v + u dot w
		{
			D3DXVECTOR3 u(1, 1, 0);
			D3DXVECTOR3 v(0, 1, 1);
			D3DXVECTOR3 w(1, 0, 1);
			D3DXVECTOR3 vSum;

			vSum = v + w;

			std::cout << "B: ";
			if (D3DXVec3Dot(&u, &vSum) == D3DXVec3Dot(&u, &v) + D3DXVec3Dot(&u, &w))
			{
				std::cout << "VRAI" << std::endl;
			}
			else
			{
				std::cout << "FAUX" << std::endl;
			}
		}

		// c) k(u dot v) == (ku) dot v == u dot (kv)
		{
			float k = 2.f;
			D3DXVECTOR3 u(1, 1, 0);
			D3DXVECTOR3 v(0, 1, 1);
		
			std::cout << "C: ";
			float compare = k * D3DXVec3Dot(&u, &v);
			if (compare == D3DXVec3Dot(&(k*u), &v) && compare == D3DXVec3Dot(&u, &(k*v)))
			{
				std::cout << "VRAI" << std::endl;
			}
			else
			{
				std::cout << "FAUX" << std::endl;
			}
		}

		// d) v dot v == ||v||^2
		{
			D3DXVECTOR3 v(1, 1, 0);

			std::cout << "D: ";
			if (D3DXVec3Dot(&v, &v) == D3DXVec3LengthSq(&v))
			{
				std::cout << "VRAI" << std::endl;
			}
			else
			{
				std::cout << "FAUX" << std::endl;
			}
		}

		// e) 0 dot v == 0
		{
			D3DXVECTOR3 zero(0, 0, 0);
			D3DXVECTOR3 v(1, 1, 0);

			std::cout << "E: ";
			if (D3DXVec3Dot(&zero, &v) == 0)
			{
				std::cout << "VRAI" << std::endl;
			}
			else
			{
				std::cout << "FAUX" << std::endl;
			}
		}
	}

	// Matrices
	{
		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, 1, 0, 0);

		D3DXMATRIX R;
		//D3DXMatrixRotationX
		//D3DXMatrixRotationY
		//D3DXMatrixRotationZ
		//D3DXMatrixRotationAxis
		D3DXMatrixRotationYawPitchRoll(&R, 0, 0, 90 * D3DX_PI/180);
		
		D3DXMATRIX S;
		D3DXMatrixScaling(&S, 2, 2, 2);

		D3DXMATRIX TR = R * T;

		std::cout << TR << std::endl;
		std::cout << "X:" << T._41 << " Y: " << T._42 << " Z: " << T._43 << std::endl;

		D3DXVECTOR4 v(1, 0, 0, 1);
		D3DXVec4Transform(&v, &v, &T);
		std::cout << v << std::endl;

		D3DXVECTOR3 u(1,0,0);

		D3DXVec3TransformNormal(&u, &u, &T);
		std::cout << u << std::endl;

		D3DXVec3TransformCoord(&u, &u, &T);
		std::cout << u << std::endl;

	}
    return 0;
}

