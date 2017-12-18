//#pragma once
//
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
//				D3DXVECTOR3& target,
//
//				D3DXVECTOR3& up);
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