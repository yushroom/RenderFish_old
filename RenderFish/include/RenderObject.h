#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "Vector.h"
#include "Mesh.h"
#include "Transform.h"
#include "d3dUtil.h"
#include "Vertex.h"
#include "Effects.h"
#include "Camera.h"

namespace RenderFish
{
	class Scene;

	class RenderObject
	{
	public:

		RenderObject(Mesh* mesh) : mMesh(mesh)
		{
			mMaterial.Ambient = Vector4(0.4f, 0.4f, 0.4f, 1.0f);
			mMaterial.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
			mMaterial.Specular = Vector4(0.8f, 0.8f, 0.8f, 16.0f);
		}

		virtual ~RenderObject()
		{
			//if (mMesh != nullptr)
			//{
			//	delete mMesh;
			//	mMesh = nullptr;
			//}
			SafeDelete(mMesh);

			ReleaseCOM(mVB);
			ReleaseCOM(mIB);
		}

		virtual void Update(float dt)
		{

		}

		virtual void Draw(ID3D11Device* pDevice, ID3D11DeviceContext* pd3dDeviceContext, const Camera& camera)
		{
			UINT stride = sizeof(Vertex::Basic32);
			UINT offset = 0;

			auto view = camera.View();
			auto proj = camera.Proj();
			auto viewProj = camera.ViewProj();

			D3DX11_TECHNIQUE_DESC techDesc;
			mpTechnique->GetDesc(&techDesc);
			for (UINT p = 0; p < techDesc.Passes; ++p)
			{
				// Draw the dragon .
				pd3dDeviceContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
				pd3dDeviceContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);

				auto world = mTransform.GetWorldMatrix();
				auto worldInvTranspose = Matrix4x4::InverseTranspose(world);
				auto worldViewProj = world*Matrix4x4(view)*Matrix4x4(proj);

				Effects::BasicFX->SetWorld(world);
				Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
				Effects::BasicFX->SetWorldViewProj(worldViewProj);
				Effects::BasicFX->SetMaterial(mMaterial);

				mpTechnique->GetPassByIndex(p)->Apply(0, pd3dDeviceContext);
				pd3dDeviceContext->DrawIndexed(mMesh->IndexCount(), 0, 0);
			}
		}

		void BuildGeometeryBuffers(ID3D11Device* pDevice, bool forceRebuilt = false);

		void SetEffectTechnique(ID3DX11EffectTechnique* pTechnique)
		{
			mpTechnique = pTechnique;
		}

		Transform& transform()
		{
			return mTransform;
		}

	private:
		Transform mTransform;

		Mesh* mMesh;
		Material mMaterial;

		bool isBufferCreated = false;
		ID3D11Buffer* mVB;
		ID3D11Buffer* mIB;

		ID3DX11EffectTechnique* mpTechnique;
	};

}

#endif // !RENDEROBJECT_H
