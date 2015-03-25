//***************************************************************************************
// Camera.h by Frank Luna (C) 2011 All Rights Reserved.
//   
// Simple first person style camera class that lets the viewer explore the 3D scene.
//   -It keeps track of the camera coordinate system relative to the world space
//    so that the view matrix can be constructed.  
//   -It keeps track of the viewing frustum of the camera so that the projection
//    matrix can be obtained.
//***************************************************************************************

#ifndef CAMERA_H
#define CAMERA_H

#include "d3dUtil.h"

#define USE_NYMATRIX 1

#if USE_NYMATRIX
#include "Vector.h"
#include "Matrix.h"

namespace RenderFish
{

	class Camera
	{
	public:
		Camera();
		~Camera();

		// Get/Set world camera position.
		Vector3 GetPosition()const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const Vector3& v);

		// Get camera basis vectors.
		Vector3 GetRight()const;
		Vector3 GetUp()const;
		Vector3 GetLook()const;

		// Get frustum properties.
		float GetNearZ()const;
		float GetFarZ()const;
		float GetAspect()const;
		float GetFovY()const;
		float GetFovX()const;

		// Get near and far plane dimensions in view space coordinates.
		float GetNearWindowWidth()const;
		float GetNearWindowHeight()const;
		float GetFarWindowWidth()const;
		float GetFarWindowHeight()const;

		// Set frustum.
		void SetLens(float fovY, float aspect, float zn, float zf);

		// Define camera space via LookAt parameters.
		void LookAt(const Vector3& pos, const Vector3& target, const Vector3& up);

		// Get View/Proj matrices.
		Matrix4x4 View()const;
		Matrix4x4 Proj()const;
		Matrix4x4 ViewProj()const;

		// Strafe/Walk the camera a distance d.
		void Strafe(float d);
		void Walk(float d);

		// Rotate the camera.
		void Pitch(float angle);
		void RotateY(float angle);

		// After modifying camera position/orientation, call to rebuild the view matrix.
		void UpdateViewMatrix();

	private:

		// Camera coordinate system with coordinates relative to world space.
		Vector3 mPosition;
		Vector3 mRight;
		Vector3 mUp;
		Vector3 mLook;

		// Cache frustum properties.
		float mNearZ;
		float mFarZ;
		float mAspect;
		float mFovY;
		float mNearWindowHeight;
		float mFarWindowHeight;

		// Cache View/Proj matrices.
		Matrix4x4 mView;
		Matrix4x4 mProj;
	};

}

#else
namespace RenderFish
{

	class Camera
	{
	public:
		Camera();
		~Camera();

		// Get/Set world camera position.
		XMVECTOR GetPositionXM()const;
		XMFLOAT3 GetPosition()const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const XMFLOAT3& v);

		// Get camera basis vectors.
		XMVECTOR GetRightXM()const;
		XMFLOAT3 GetRight()const;
		XMVECTOR GetUpXM()const;
		XMFLOAT3 GetUp()const;
		XMVECTOR GetLookXM()const;
		XMFLOAT3 GetLook()const;

		// Get frustum properties.
		float GetNearZ()const;
		float GetFarZ()const;
		float GetAspect()const;
		float GetFovY()const;
		float GetFovX()const;

		// Get near and far plane dimensions in view space coordinates.
		float GetNearWindowWidth()const;
		float GetNearWindowHeight()const;
		float GetFarWindowWidth()const;
		float GetFarWindowHeight()const;

		// Set frustum.
		void SetLens(float fovY, float aspect, float zn, float zf);

		// Define camera space via LookAt parameters.
		void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
		void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

		// Get View/Proj matrices.
		XMMATRIX View()const;
		XMMATRIX Proj()const;
		XMMATRIX ViewProj()const;

		// Strafe/Walk the camera a distance d.
		void Strafe(float d);
		void Walk(float d);

		// Rotate the camera.
		void Pitch(float angle);
		void RotateY(float angle);

		// After modifying camera position/orientation, call to rebuild the view matrix.
		void UpdateViewMatrix();

	private:

		// Camera coordinate system with coordinates relative to world space.
		XMFLOAT3 mPosition;
		XMFLOAT3 mRight;
		XMFLOAT3 mUp;
		XMFLOAT3 mLook;

		// Cache frustum properties.
		float mNearZ;
		float mFarZ;
		float mAspect;
		float mFovY;
		float mNearWindowHeight;
		float mFarWindowHeight;

		// Cache View/Proj matrices.
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mProj;
	};

}

#endif

#endif // CAMERA_H