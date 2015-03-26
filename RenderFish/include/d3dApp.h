//***************************************************************************************
// d3dApp.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Simple Direct3D demo application class.  
// Make sure you link: d3d11.lib d3dx11d.lib D3DCompiler.lib D3DX11EffectsD.lib 
//                     dxerr.lib dxgi.lib dxguid.lib.
// Link d3dx11.lib and D3DX11Effects.lib for release mode builds instead
//   of d3dx11d.lib and D3DX11EffectsD.lib.
//***************************************************************************************

#ifndef D3DAPP_H
#define D3DAPP_H

#include "d3dUtil.h"
#include "GameTimer.h"
#include "Global.h"
#include <string>

class D3DApp
{
public:
	explicit D3DApp();
	explicit D3DApp(HINSTANCE hInstance);
	explicit D3DApp(void* native_wnd);
	virtual ~D3DApp();
	
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;
	
	int Run();
	void LockFPS(bool locked, int FPS = 30);

	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual bool Init();
	virtual void OnResize();
	virtual void UpdateScene(float dt)=0;
	virtual void DrawScene()=0; 
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

protected:
	bool InitMainWindow();
	bool InitExternalWindow();
	bool InitDirect3D();

	void CalculateFrameStats();

protected:

	HINSTANCE	mhAppInst;
	HWND		_mhWnd;
	bool		_external_wnd;
	HWND		mhMainWnd;
	bool		mAppPaused;
	bool		mMinimized;
	bool		mMaximized;
	bool		mResizing;

	RenderFish::GameTimer mTimer;
	bool mFPSLocked;
	float mTimePerFrame;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;
};

#endif // D3DAPP_H