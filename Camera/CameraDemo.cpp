//***************************************************************************************
// CameraDemo.cpp by Frank Luna (C) 2011 All Rights Reserved.
//
// Demonstrates first person camera.
//
// Controls:
//		Hold the left mouse button down and move the mouse to rotate.
//      Hold the right mouse button down to zoom in and out.
//      Press '1', '2', '3' for 1, 2, or 3 lights enabled.
//
//***************************************************************************************

#include "CameraDemo.h"
#include "Global.h"

using namespace RenderFish;

CameraApp::CameraApp(HINSTANCE hInstance)
: D3DApp(hInstance)
{
	mMainWndCaption = L"D3D11 Demo";
	
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;
}

CameraApp::~CameraApp()
{

	Effects::DestroyAll();
	InputLayouts::DestroyAll(); 
}

bool CameraApp::Init()
{
	if(!D3DApp::Init())
		return false;

	LockFPS(true, 60);

	// Must init Effects first since InputLayouts depend on shader signatures.
	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);

	auto dragonObj = new RenderObject(new Mesh(Global::ModelDir + "Dragon.obj"));
	dragonObj->transform().SetScale(4, 4, 4);
	dragonObj->transform().SetPosition(0, 0, 0);
	mScene.AddRenderObject(dragonObj);

	mScene.Init(md3dDevice);

	return true;
}

void CameraApp::OnResize()
{
	D3DApp::OnResize();

	Scene::MainCamera.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}

void CameraApp::UpdateScene(float dt)
{
	mScene.Update(dt);
}

void CameraApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Silver));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mScene.Draw(md3dDevice, md3dImmediateContext);

	HR(mSwapChain->Present(0, 0));
}

void CameraApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void CameraApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void CameraApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if( (btnState & MK_LBUTTON) != 0 )
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		Scene::MainCamera.Pitch(dy);
		Scene::MainCamera.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}