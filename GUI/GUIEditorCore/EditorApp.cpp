#include "EditorApp.h"
#include "Global.h"

using namespace RenderFish;

bool EditorApp::Init()
{
	if (!D3DApp::Init())
		return false;

	LockFPS(true, 60);

	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);

	auto dragonObj = new RenderObject(new Mesh(Global::ModelDir + "dragon.obj"));
	dragonObj->transform().SetScale(4, 4, 4);
	dragonObj->transform().SetPosition(0, 0, 0);
	mScene.AddRenderObject(dragonObj);

	mScene.Init(md3dDevice);
	return true;
}

void EditorApp::OnResize(unsigned int width, unsigned int height)
{
	mClientWidth = width;
	mClientHeight = height;

	D3DApp::OnResize();

	Scene::MainCamera.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 10000.f);
}

void EditorApp::UpdateScene(float dt)
{
	mScene.Update(dt);
}

void EditorApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Silver));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mScene.Draw(md3dDevice, md3dImmediateContext);

	HR(mSwapChain->Present(0, 0));
}