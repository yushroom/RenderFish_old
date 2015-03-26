#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include "d3dUtil.h"


namespace RenderFish
{
	class Camera;

	class Global
	{
	public:
		const static std::string ModelDir;
		const static std::string ShaderDir;

	private:
		Global()
		{

		}
	};

	// RenderContext
	class RenderContext
	{
	public:

		static void Destroy()
		{
			ReleaseCOM(mRenderTargetView);
			ReleaseCOM(mDepthStencilView);
			ReleaseCOM(mSwapChain);
			ReleaseCOM(mDepthStencilBuffer);

			// Restore all default settings.
			if (md3dImmediateContext)
				md3dImmediateContext->ClearState();

			ReleaseCOM(md3dImmediateContext);
			ReleaseCOM(md3dDevice);
		}

		static ID3D11Device* Device()
		{
			return md3dDevice;
		}

		static ID3D11DeviceContext* DeviceContext()
		{
			return md3dImmediateContext;
		}

		static IDXGISwapChain* SwapChain()
		{
			return mSwapChain;
		}

		static ID3D11Texture2D* DepthStencilBuffer()
		{
			return mDepthStencilBuffer;
		}

		static ID3D11RenderTargetView* RenderTargetView()
		{
			return mRenderTargetView;
		}

		static ID3D11DepthStencilView* DepthStencilView()
		{
			return mDepthStencilView;
		}

		static bool InitD3D11(HWND hWnd)
		{
			//Debug::LogInfo("RenderContext::InitD3D11");

			// Create the device and device context.

			UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			ZeroMemory(&mScreenViewport, sizeof(D3D11_VIEWPORT));

			D3D_FEATURE_LEVEL featureLevel;
			HRESULT hr = D3D11CreateDevice(
				0,                 // default adapter
				md3dDriverType,
				0,                 // no software device
				createDeviceFlags,
				0, 0,              // default feature level array
				D3D11_SDK_VERSION,
				&md3dDevice,
				&featureLevel,
				&md3dImmediateContext);

			if (FAILED(hr))
			{
				MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
				return false;
			}

			if (featureLevel != D3D_FEATURE_LEVEL_11_0)
			{
				MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
				return false;
			}

			// Check 4X MSAA quality support for our back buffer format.
			// All Direct3D 11 capable devices support 4X MSAA for all render 
			// target formats, so we only need to check quality support.

			HR(md3dDevice->CheckMultisampleQualityLevels(
				DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality));
			assert(m4xMsaaQuality > 0);

			// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

			DXGI_SWAP_CHAIN_DESC sd;
			sd.BufferDesc.Width = mClientWidth;
			sd.BufferDesc.Height = mClientHeight;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			// Use 4X MSAA? 
			if (mEnable4xMsaa)
			{
				sd.SampleDesc.Count = 4;
				sd.SampleDesc.Quality = m4xMsaaQuality - 1;
			}
			// No MSAA
			else
			{
				sd.SampleDesc.Count = 1;
				sd.SampleDesc.Quality = 0;
			}

			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;
			sd.OutputWindow = hWnd;
			sd.Windowed = true;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = 0;

			// To correctly create the swap chain, we must use the IDXGIFactory that was
			// used to create the device.  If we tried to use a different IDXGIFactory instance
			// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
			// This function is being called with a device from a different IDXGIFactory."

			IDXGIDevice* dxgiDevice = 0;
			HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

			IDXGIAdapter* dxgiAdapter = 0;
			HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

			IDXGIFactory* dxgiFactory = 0;
			HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

			HR(dxgiFactory->CreateSwapChain(md3dDevice, &sd, &mSwapChain));
			//HR(dxgiFactory->MakeWindowAssociation(mhMainWnd, DXGI_MWA_NO_WINDOW_CHANGES));	// disable Alt+Enter to fullScreen

			ReleaseCOM(dxgiDevice);
			ReleaseCOM(dxgiAdapter);
			ReleaseCOM(dxgiFactory);

			// The remaining steps that need to be carried out for d3d creation
			// also need to be executed every time the window is resized.  So
			// just call the OnResize method here to avoid code duplication.

			OnResize(mClientWidth, mClientHeight);

			return true;
		}

		static void OnResize(int width, int height)
		{
			//if (mClientHeight == height && mClientWidth == width)
			//	return;

			assert(md3dImmediateContext);
			assert(md3dDevice);
			assert(mSwapChain);

			// Release the old views, as they hold references to the buffers we
			// will be destroying.  Also release the old depth/stencil buffer.

			ReleaseCOM(mRenderTargetView);
			ReleaseCOM(mDepthStencilView);
			ReleaseCOM(mDepthStencilBuffer);


			// Resize the swap chain and recreate the render target view.

			HR(mSwapChain->ResizeBuffers(1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
			ID3D11Texture2D* backBuffer;
			HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
			HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
			ReleaseCOM(backBuffer);

			// Create the depth/stencil buffer and view.

			D3D11_TEXTURE2D_DESC depthStencilDesc;

			depthStencilDesc.Width = mClientWidth;
			depthStencilDesc.Height = mClientHeight;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

			// Use 4X MSAA? --must match swap chain MSAA values.
			if (mEnable4xMsaa)
			{
				depthStencilDesc.SampleDesc.Count = 4;
				depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
			}
			// No MSAA
			else
			{
				depthStencilDesc.SampleDesc.Count = 1;
				depthStencilDesc.SampleDesc.Quality = 0;
			}

			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;

			HR(md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
			HR(md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));


			// Bind the render target view and depth/stencil view to the pipeline.

			md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);


			// Set the viewport transform.

			mScreenViewport.TopLeftX = 0;
			mScreenViewport.TopLeftY = 0;
			mScreenViewport.Width = static_cast<float>(mClientWidth);
			mScreenViewport.Height = static_cast<float>(mClientHeight);
			mScreenViewport.MinDepth = 0.0f;
			mScreenViewport.MaxDepth = 1.0f;

			md3dImmediateContext->RSSetViewports(1, &mScreenViewport);
		}

		static void SetCamera(Camera* pCamera)
		{
			mCamera = pCamera;
		}
		static Camera* CurrentCamera()
		{
			return mCamera;
		}

		static void SetTechnique(ID3DX11EffectTechnique* pTech)
		{
			mpTechnique = pTech;
		}
		static ID3DX11EffectTechnique* Technique()
		{
			return mpTechnique;
		}

	private:
		RenderContext() {}	// make abstract

	private:
		static ID3D11Device* md3dDevice;
		static ID3D11DeviceContext* md3dImmediateContext;
		static IDXGISwapChain* mSwapChain;
		static ID3D11Texture2D* mDepthStencilBuffer;
		static ID3D11RenderTargetView* mRenderTargetView;
		static ID3D11DepthStencilView* mDepthStencilView;
		static D3D11_VIEWPORT mScreenViewport;
		
		static UINT      m4xMsaaQuality;
		static D3D_DRIVER_TYPE md3dDriverType;
		static int mClientWidth;
		static int mClientHeight;
		static bool mEnable4xMsaa;

		static Camera* mCamera;

		static ID3DX11EffectTechnique* mpTechnique;
	};
}

#endif	//GLOBAL_H