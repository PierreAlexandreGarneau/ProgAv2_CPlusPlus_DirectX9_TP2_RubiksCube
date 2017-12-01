#include "stdafx.h"
#include "RubikCubeApp.h"

RubikCubeApp::RubikCubeApp()
{
}

RubikCubeApp::RubikCubeApp(HINSTANCE hInstance, int nCmdShow)
	: D3DApp(hInstance, nCmdShow)
	, currRot(0.f)
	, eyePos(0.f, 0.f, 2.f)
	, target(0.f, 0.f, 0.f)
	, up(0.f, 1.0f, 0.f)
{
	cube = new Cube(0x0);
}

RubikCubeApp::~RubikCubeApp()
{
	delete cube;
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
	DestroyAllDeclaration();

}

void RubikCubeApp::Update()
{
}

void RubikCubeApp::Draw()
{
	cube->Draw();
}
