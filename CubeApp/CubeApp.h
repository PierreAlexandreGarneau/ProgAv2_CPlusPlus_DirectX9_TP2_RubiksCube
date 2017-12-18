#pragma once

#include "D3DApp.h"
#include "Vertex.h"

class CubeApp
	: public D3DApp
{

public:
	CubeApp();
	CubeApp(HINSTANCE hInstance, int nCmdShow);
	~CubeApp();

	void updateScene(float dt);
	void drawScene();
	void CreateCube(IDirect3DVertexBuffer9* vb, IDirect3DIndexBuffer9* ib, float x);

	
private:
	float currRot;

	
	ID3DXEffect* mFX;
	ID3DXBuffer* errors;

	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;
	D3DXHANDLE mhEyePos;
	D3DXHANDLE mhFogColor;
	D3DXHANDLE mhFogStart;
	D3DXHANDLE mhFogRange;

	//7.4.2 CubeDemo Class Data Membe rs

	//In this section, we outline the data members of our CubeDemo class.

	//mVB: Pointer to an IDirectSDVertexBuffer9 interface and is used to store the cube vertices.
	IDirect3DVertexBuffer9* mVB;
	//mIB: Pointer to an IDirect3DIndexBuffer9 interface and is used to store the index information defining the triangles of the cube.
	IDirect3DIndexBuffer9* mIB;
	//mVB: Pointer to an IDirectSDVertexBuffer9 interface and is used to store the cube vertices.
	IDirect3DVertexBuffer9* mVB2;
	//mIB: Pointer to an IDirect3DIndexBuffer9 interface and is used to store the index information defining the triangles of the cube.
	IDirect3DIndexBuffer9* mIB2;

			//mView: A D3DXMATRIX that stores the view matrix.
	D3DXMATRIX mView;
			//mProj: A D3DXMATRIX that stores the projection matrix.
	D3DXMATRIX mProj;
	
	D3DXVECTOR3 pEye;
	D3DXVECTOR3 pAt;
	D3DXVECTOR3 pUp;


	//9.3 Color Cube Demo

	//Figure 9.3 shows a screenshot for this demo, which is a colored cube. The source code for this demo is almost the same as the Cube demo from Chapter 7, except
	//we use color.fx and the color vertex structure.

	//Figure 9.3: Screenshot of the Color Cube demo.

	//First we define the following constants:
	const D3DCOLOR WHITE = D3DCOLOR_XRGB(255, 255, 255); // 0xffffffff
	const D3DCOLOR BLACK = D3DCOLOR_XRGB(0, 0, 0); // 0xff000000
	const D3DCOLOR RED = D3DCOLOR_XRGB(255, 0, 0); // 0xffff0000
	const D3DCOLOR GREEN = D3DCOLOR_XRGB(0, 255, 0); // 0xff00ff00
	const D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255); // 0xff0000ff
	const D3DCOLOR YELLOW = D3DCOLOR_XRGB(255, 255, 0); // 0xffffff00
	const D3DCOLOR CYAN = D3DCOLOR_XRGB(0, 255, 255); // 0xff00ffff
	const D3DCOLOR MAGENTA = D3DCOLOR_XRGB(255, 0, 255); // 0xffff00ff

};

//#include "D3DApp.h"
//#include "Vertex.h"
//#include "Input.h"
//#include "Camera.h"
//#include "D3DUtils.h"
//
////17.4.3 The Camera Class
//class Camera
//{
//public:
//	// By default, the camera starts out with its basis vectors
//	// aligned with the world space axes, and its origin positioned
//	// at the world space origin.
//	Camera();
//
//	// Read only accessor functions.
//	const D3DXMATRIX& view() const;
//	const D3DXMATRIX& proj() const;
//	const D3DXMATRIX& viewProj() const;
//
//	const D3DXVECTOR3& right() const;
//	const D3DXVECTOR3& up() const;
//	const D3DXVECTOR3& look() const;
//
//	// Read/write access to the camera position.
//	D3DXVECTOR3& pos();
//
//	// Our implementation of D3DXMatrixLookAtLH
//	void lookAt(D3DXVECTOR3& pos,
//		D3DXVECTOR3& target,
//
//		D3DXVECTOR3& up);
//
//	// Perspective projection parameters.
//	void setLens(float fov, float aspect, float nearZ, float farZ);
//
//	// Sets the camera speed.
//	void setSpeed(float s);
//	// Updates the camera's basis vectors and origin, relative to
//	// the world space, based on user input.
//	void update(float dt);
//protected:
//	// Constructs the view matrix based on the camera's basis
//	// vectors and origin, relative to the world space.
//	void buildView();
//protected:
//	// Save camera-related matrices.
//	D3DXMATRIX mView;
//	D3DXMATRIX mProj;
//	D3DXMATRIX mViewProj;
//
//	// Camera coordinate system relative to world space.
//	D3DXVECTOR3 mPosW;
//	D3DXVECTOR3 mRightW;
//	D3DXVECTOR3 mUpW;
//	D3DXVECTOR3 mLookW;
//
//	// Camera speed.
//	float mSpeed;
//};
//
//extern Camera* gCamera;