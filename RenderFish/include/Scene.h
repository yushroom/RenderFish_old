#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Vertex.h"	// TODO
#include "Effects.h"
#include "RenderObject.h"
#include "GameObject.h"

namespace RenderFish
{
	class Scene
	{
	public:
		//static Scene* GetInstance()
		//{
		//	if (instance == nullptr)
		//	{
		//		instance = new Scene();
		//	}
		//	return instance;
		//}
		Scene()
		{
			MainCamera.SetPosition(0, 0, -10);

			mDirLights[0].Ambient = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
			mDirLights[0].Diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
			mDirLights[0].Specular = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
			mDirLights[0].Direction = Vector3(0.57735f, -0.57735f, 0.57735f);

			mDirLights[1].Ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
			mDirLights[1].Diffuse = Vector4(0.20f, 0.20f, 0.20f, 1.0f);
			mDirLights[1].Specular = Vector4(0.25f, 0.25f, 0.25f, 1.0f);
			mDirLights[1].Direction = Vector3(-0.57735f, -0.57735f, 0.57735f);

			mDirLights[2].Ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
			mDirLights[2].Diffuse = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
			mDirLights[2].Specular = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
			mDirLights[2].Direction = Vector3(0.0f, -0.707f, -0.707f);
		}

		virtual ~Scene() 
		{
			// delete
			for (auto obj : mGameObjects)
			{
				SafeDelete(obj);
			}

			mGameObjects.clear();
		}

		virtual void Init()
		{
			//MainCamera.SetPosition(0.0f, 2.0f, -15.0f);

			//for (auto obj : mRenderObjects)
			//{
			//	obj->BuildGeometeryBuffers(pDevice);
			//}

			for (auto obj : mGameObjects)
			{
				obj->_Init();
			}
		}

		virtual void Update(float dt)
		{
			//
			// Control the camera.
			//
			if (GetAsyncKeyState('W') & 0x8000)
				MainCamera.Walk(10.0f*dt);

			if (GetAsyncKeyState('S') & 0x8000)
				MainCamera.Walk(-10.0f*dt);

			if (GetAsyncKeyState('A') & 0x8000)
				MainCamera.Strafe(-10.0f*dt);

			if (GetAsyncKeyState('D') & 0x8000)
				MainCamera.Strafe(10.0f*dt);

			//
			// Switch the number of lights based on key presses.
			//
			if (GetAsyncKeyState('0') & 0x8000)
				mLightCount = 0;

			if (GetAsyncKeyState('1') & 0x8000)
				mLightCount = 1;

			if (GetAsyncKeyState('2') & 0x8000)
				mLightCount = 2;

			if (GetAsyncKeyState('3') & 0x8000)
				mLightCount = 3;

			// update RenderObjects
			//for (auto obj : mRenderObjects)
			//{
			//	obj->Update(dt);
			//}
		}

		virtual void Draw()
		{
			auto pDevice = RenderContext::Device();
			auto pd3dDeviceContext = RenderContext::DeviceContext();

			MainCamera.UpdateViewMatrix();
			RenderContext::SetCamera(&MainCamera);

			//Matrix4x4 view = MainCamera.View();
			//Matrix4x4 proj = MainCamera.Proj();
			//Matrix4x4 viewProj = MainCamera.ViewProj();

			// Set per frame constants.
			Effects::BasicFX->SetDirLights(mDirLights);
			Effects::BasicFX->SetEyePosW(MainCamera.GetPosition());

			// Figure out which technique to use.  Skull does not have texture coordinates,
			// so we need a separate technique for it.
			ID3DX11EffectTechnique* activeTexTech = Effects::BasicFX->Light1TexTech;
			ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light1Tech;
			switch (mLightCount)
			{
			case 1:
				activeTexTech = Effects::BasicFX->Light1TexTech;
				activeTech = Effects::BasicFX->Light1Tech;
				break;
			case 2:
				activeTexTech = Effects::BasicFX->Light2TexTech;
				activeTech = Effects::BasicFX->Light2Tech;
				break;
			case 3:
				activeTexTech = Effects::BasicFX->Light3TexTech;
				activeTech = Effects::BasicFX->Light3Tech;
				break;
			}

			RenderContext::SetTechnique(activeTech);

			for (auto obj : mGameObjects)
			{
				obj->Draw();
			}
		}

		void AddGameObjects(GameObject* object)
		{
			mGameObjects.push_back(object);
		}

	public:
		static Camera MainCamera; // TODO private

	protected:

	private:


	private:
		//static Scene* instance;
		std::vector<GameObject*> mGameObjects;
		
		UINT mLightCount = 3;
		DirectionalLight mDirLights[3];
	};
}


#endif