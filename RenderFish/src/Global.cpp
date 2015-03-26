#include "Global.h"

using namespace RenderFish;

const std::string Global::ModelDir{ "D:/program/github/RenderFish/Media/Models/" };
const std::string Global::ShaderDir{ "D:/program/github/RenderFish/HLSL/" };

ID3D11Device* RenderContext::md3dDevice = nullptr;
ID3D11DeviceContext* RenderContext::md3dImmediateContext = nullptr;
IDXGISwapChain* RenderContext::mSwapChain = nullptr;
ID3D11Texture2D* RenderContext::mDepthStencilBuffer = nullptr;
ID3D11RenderTargetView* RenderContext::mRenderTargetView = nullptr;
ID3D11DepthStencilView* RenderContext::mDepthStencilView = nullptr;
D3D11_VIEWPORT RenderContext::mScreenViewport;

UINT      RenderContext::m4xMsaaQuality = 0;
D3D_DRIVER_TYPE RenderContext::md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
int RenderContext::mClientWidth = 800;
int RenderContext::mClientHeight = 600;
bool RenderContext::mEnable4xMsaa = false;

Camera* RenderContext::mCamera = nullptr;

ID3DX11EffectTechnique* RenderContext::mpTechnique = nullptr;