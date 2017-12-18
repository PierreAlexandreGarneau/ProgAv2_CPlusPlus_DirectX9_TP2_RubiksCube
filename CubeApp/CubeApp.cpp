#include "stdafx.h"
#include "CubeApp.h"
#include "Camera.h"
CubeApp::CubeApp()
{
}
//7.4.3 Construction

//The constructor is implemented below :
CubeApp::CubeApp(HINSTANCE hInstance, int nCmdShow)
: D3DApp(hInstance, nCmdShow)
	, currRot(0.f)
	, pEye(0.f, 0.f, 2.f)
	, pAt(0.f, 0.f, 0.f)
	, pUp(0.f, 1.0f, 0.f)
{		
	//Cube1 = new Cube(0, 0, 0);
	
	//mGfxStats = new GfxStats();

	InitAllVertexDeclarations();

	HR(gd3dDevice->CreateVertexBuffer(8 * sizeof(VertexCol), 0, 0, D3DPOOL_MANAGED, &mVB, 0));

	// Write the index data to the index buffer.

	//Observe that we have commented the hexadecimal representation of the D3DCOLORs above; if you are not already, it is a good idea to become comfortable with the
	//hexadecimal and binary number systems.

	//When we construct the cube's vertices, we just pass in one of the above colors as the color component for each vertex:
	VertexCol* v = 0;
	HR(mVB->Lock(0, 0, (void**)&v, 0));

	//for(DWORD i = 0; i< mNumVertices; ++i)
	//	v[i] = verts[i]
	v[0] = VertexCol(-1.0f, -1.0f, -1.0f, WHITE);
	v[1] = VertexCol(-1.0f, 1.0f, -1.0f, BLACK);
	v[2] = VertexCol( 1.0f, 1.0f, -1.0f, RED);
	v[3] = VertexCol( 1.0f, -1.0f, -1.0f, GREEN);
	v[4] = VertexCol(-1.0f, -1.0f, 1.0f, BLUE);
	v[5] = VertexCol(-1.0f, 1.0f, 1.0f, YELLOW);
	v[6] = VertexCol( 1.0f, 1.0f, 1.0f, CYAN);
	v[7] = VertexCol( 1.0f, -1.0f, 1.0f, MAGENTA);

	HR(mVB->Unlock());

	// Build Index Buffer
	HR(gd3dDevice->CreateIndexBuffer(36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0));

	// Write the index data to the index buffer.
	WORD* k;
	HR(mIB->Lock(0, 0, (void**)&k, 0));

	//for(DWORD i = 0; i< mNumTriangles*3; ++i)
	//	k[i] = (WORD)indices[i];
	// front side
	k[0] = 0; k[1] = 1; k[2] = 2;
	k[3] = 0; k[4] = 2; k[5] = 3;
	// back side
	k[6] = 4; k[7] = 6; k[8] = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;
	// left side
	k[12] = 4; k[13] = 5; k[14] = 1;
	k[15] = 4; k[16] = 1; k[17] = 0;
	// right side
	k[18] = 3; k[19] = 2; k[20] = 6;
	k[21] = 3; k[22] = 6; k[23] = 7;
	// top
	k[24] = 1; k[25] = 5; k[26] = 6;
	k[27] = 1; k[28] = 6; k[29] = 2;
	// bottom
	k[30] = 4; k[31] = 0; k[32] = 3;
	k[33] = 4; k[34] = 3; k[35] = 7;
	HR(mIB->Unlock());
	HR(D3DXCreateEffectFromFileW(gd3dDevice, L"Transform.fx",
		0, 0, D3DXSHADER_DEBUG, 0, &mFX, &errors));
	if (errors) {
		MessageBoxW(0, (LPCWSTR)errors->GetBufferPointer(), 0, 0);
	}


	mhTech = mFX->GetTechniqueByName("ColorTech");

	// Set up the rendering technique
	//HR(mFX->SetTechnique(mhTech));


	mhWVP = mFX->GetParameterByName(0, "gWVP");
	mhEyePos = mFX->GetParameterByName(0, "gEyePos");
	mhFogColor = mFX->GetParameterByName(0, "gFogColor");
	mhFogStart = mFX->GetParameterByName(0, "gFogStart");
	mhFogRange = mFX->GetParameterByName(0, "gFogRange");

	//8.2.5 Setting Effect Parameters

	//The ID3DXEffect interface provides methods for setting parameters of various types.Here is an abridged list; see the documentation for a complete list.

	//HRESULT ID3DXEffect::SetFloat(
	//	D3DXHANDLE hParameter,
	//	FLOAT f);
	HR(mFX->SetFloat(
		mhFogStart,
		5.0f));

	//HRESULT ID3DXEffect::SetFloat(
	//	D3DXHANDLE hParameter,
	//	FLOAT f);
	HR(mFX->SetFloat(
		mhFogRange,
		25.0f));

	//Sets a texture parameter in the effect file identified by hParameter to the value pointed to by pTexture.
	HR(mFX->SetVector(
		mhFogColor,
		&D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f)));

	//HRESULT ID3DXEffect::SetVector(
	//	D3DXHANDLE hParameter,
	//	CONST D3DXVECTOR4* pVector);

	//Note The position of the eye, in world space, is given in the buildViewMtx method, so that is the method in which we set the eye position effect parameter:
	//D3DXMatrixLookAtLH(&mView, &Pos, &target, &up);

	D3DXMatrixLookAtRH(&mView, &pEye, &pAt, &pUp);
	//6.4.4.6 D3DXMatrixPerspectiveFovLH
	//A perspective projection matrix can be built with the following D3DX function:

	//D3DXMatrixPerspectiveFovLH(&P, D3DX_PI*0.25f,
	//width/height, 1.0f, 5000.0f);
	D3DXMatrixPerspectiveFovRH(&mProj, D3DX_PI / 4,
		(float)md3dPP.BackBufferWidth / (float)md3dPP.BackBufferHeight, 0.01f, 1000.0f);

	// Fixed pipeline


	//HR(gd3dDevice->SetTransform(D3DTS_WORLD, &W));
	HR(gd3dDevice->SetTransform(D3DTS_VIEW, &mView));
	HR(gd3dDevice->SetTransform(D3DTS_PROJECTION, &mProj));
	
}


//Recall that as we progress through this book, we add all of our vertex structure definitions to the source code file Vertex.h.The global function InitAll
//VertexDeclarations provides a global function from which we create all of our vertex declarations in one localized place.As we add new vertex structures to
//Vertex.h, we also update this function to create its corresponding vertex declaration.
//Similarly, we have a global function that destroys all vertex declarations in one localized place :
CubeApp::~CubeApp()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);

	DestroyAllVertexDeclarations();
}

void CubeApp::updateScene(float dt)
{
	currRot += 0.0001f;
}
//7.4.7 drawScene
//The drawScene method draws the cube.As you can see, all the drawing code is between a pair of BeginScene and EndScene calls, as required.Observe how
//we do our preliminary drawing work of hooking the vertex buffer up to a stream, setting the index buffer, and setting the vertex declaration.Next, we set the
//combined world, view, and projection matrix to the device with the SetTransform method. (Notice that the world matrix is the identity matrix, which essentially
//means the local coordinate system of the cube is the same as the world coordinate system; that is, we are actually specifying the vertices directly into world space.)
//After setting the transformation matrices to the device, we change the fill mode render state so that the cube will be drawn in wireframe mode.Finally, we draw the
//cube with the DrawIndexedPrimitive function.
void CubeApp::drawScene()
{
	// Clear the back buffer and depth buffer.
	HR(gd3dDevice->Clear(0, 0,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128,128, 128), 1.0f, 0));

	//8.3.6 Example Code

	//The following example code summarizes all the steps needed to draw some geometry with an effect :
	HR(gd3dDevice->BeginScene());
	// Let Direct3D know the vertex buffer, index buffer, and vertex
	// declaration we are using.
	HR(gd3dDevice->SetStreamSource(0, mVB, 0, sizeof(VertexCol)));
	HR(gd3dDevice->SetIndices(mIB));
	HR(gd3dDevice->SetVertexDeclaration(VertexCol::Decl));

	// Set up the rendering technique
	HR(mFX->SetTechnique(mhTech));

	HR(mFX->SetValue(mhEyePos, &pEye, sizeof(D3DXVECTOR3)));
	
	// World matrix is identity.
	D3DXMATRIX Ry;
	D3DXMATRIX T;
	//D3DXMatrixTranslation(&T, -10.0f, 3.0f, (float)z);
	D3DXMatrixTranslation(&T, 0.f, 0.f, -20.0f);

	D3DXMatrixRotationAxis(&Ry, &D3DXVECTOR3(0, 1, 0), currRot);

	//HR(mFX->SetMatrix(mhWVP, &(R*T*mView*mProj)));
	D3DXMATRIX WVP = Ry * T * mView * mProj;

	// Set effect parameters.
	//HR(mFX->SetMatrix(mhWVP, &(mView*mProj)));
	HR(mFX->SetMatrix(mhWVP, &WVP));


	//HR(gd3dDevice->BeginScene());

	// Begin passes.
	// Here is an example invocation :
	UINT numPasses;
	HR(mFX->Begin(&numPasses, 0));

	//8.3.4 Setting the Current Rendering Pass

	//Before we can render any geometry using an effect, we must specify the rendering pass to use.Recall that a technique consists of one or more rendering passes,
	//where each pass contains the device states and shaders that are to be used for that pass.The rendering passes for a technique are labeled from 0 to n - 1 for n
	//passes.Thus we can iterate through each pass using a simple for - loop and render the geometry for that pass.We begin a pass with the
	//ID3DXEffect::BeginPass method, which takes an integer parameter from 0, …, n - 1 identifying the pass, and we end a pass with ID3DXEffect::EndPass.
	//The following code snippet illustrates this:
	for (int i = 0; i < (int)numPasses; i++)
	{
		HR(mFX->BeginPass(i));

		// Execute drawing commands here. Geometry drawn here
		// will be rendered with this pass's shaders and device
		// states applied.

		HR(gd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
											0, 0, 8, 0, 12));

		HR(mFX->EndPass());
	}

	//8.3.5 Ending an Effect
	//Finally, after we have rendered the geometry for each pass, we disable or end the effect with ID3DXEffect::End:
	HR(mFX->End());

	//mGfxStats->display();
	HR(gd3dDevice->EndScene());

	// Present the back buffer.
	HR(gd3dDevice->Present(0, 0, 0, 0));
}

//#include "stdafx.h"
//#include "Camera.h"


//17.4.5 Building the View Matrix
//void Camera::update(float dt)
//{
	// Find the net direction the camera is traveling (since the
	// camera could be running and strafing).
//	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
//	if (gDInput->keyDown(DIK_W))
//		dir += mLookW;
//	if (gDInput->keyDown(DIK_S))
//		dir -= mLookW;
//	if (gDInput->keyDown(DIK_D))
//		dir += mRightW;
//	if (gDInput->keyDown(DIK_A))
//		dir -= mRightW;
//	// Move at mSpeed along net direction.
//	D3DXVec3Normalize(&dir, &dir);
//	mPosW += dir*mSpeed*dt;
//	// Angle to rotate around right vector.
//	float pitch = gDInput->mouseDY() / 150.0f;
//	// Angle to rotate around world y-axis.
//	float yAngle = gDInput->mouseDX() / 150.0f;
//	// Rotate camera's look and up vectors around the
//	// camera's right vector.
//	D3DXMATRIX R;
//	D3DXMatrixRotationAxis(&R, &mRightW, pitch);
//	D3DXVec3TransformCoord(&mLookW, &mLookW, &R);
//	D3DXVec3TransformCoord(&mUpW, &mUpW, &R);
//	// Rotate camera axes about the world's y-axis.
//	D3DXMatrixRotationY(&R, yAngle);
//	D3DXVec3TransformCoord(&mRightW, &mRightW, &R);
//	D3DXVec3TransformCoord(&mUpW, &mUpW, &R);
//	D3DXVec3TransformCoord(&mLookW, &mLookW, &R);
//	// Rebuild the view matrix to reflect changes.
//	buildView();
//	mViewProj = mView * mProj;
//}

//17.4.5 Building the View Matrix
//void Camera::buildView()
//{
//	// Keep camera's axes orthogonal to each other and
//	// of unit length.
//	D3DXVec3Normalize(&mLookW, &mLookW);
//	D3DXVec3Cross(&mUpW, &mLookW, &mRightW);
//	D3DXVec3Normalize(&mUpW, &mUpW);
//	D3DXVec3Cross(&mRightW, &mUpW, &mLookW);
//	D3DXVec3Normalize(&mRightW, &mRightW);
//	// Fill in the view matrix entries.
//	float x = -D3DXVec3Dot(&mPosW, &mRightW);
//	float y = -D3DXVec3Dot(&mPosW, &mUpW);
//	float z = -D3DXVec3Dot(&mPosW, &mLookW);
//	mView(0, 0) = mRightW.x;
//	mView(1, 0) = mRightW.y;
//	mView(2, 0) = mRightW.z;
//	mView(3, 0) = x;
//	mView(0, 1) = mUpW.x;
//	mView(1, 1) = mUpW.y;
//	mView(2, 1) = mUpW.z;
//	mView(3, 1) = y;
//	mView(0, 2) = mLookW.x;
//	mView(1, 2) = mLookW.y;
//	mView(2, 2) = mLookW.z;
//	mView(3, 2) = z;
//	mView(0, 3) = 0.0f;
//	mView(1, 3) = 0.0f;
//	mView(2, 3) = 0.0f;
//	mView(3, 3) = 1.0f;
//}
