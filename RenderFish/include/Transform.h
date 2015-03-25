#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"
#include "Matrix.h"

namespace RenderFish
{
	class Transform
	{
	public:
		Transform() : mPosition(0, 0, 0), mScale(1, 1, 1), mRotation(0, 0, 0)
		{
		}

		void SetPosition(float x, float y, float z)
		{
			mPosition.x = x; mPosition.y = y; mPosition.z = z;
			isDirty;
		}
		void SetPosition(const Vector3& v)
		{
			mPosition = v;
			isDirty = true;
		}
		void SetScale(float x, float y, float z)
		{
			mScale.x = x; mScale.y = y; mScale.z = z;
			isDirty;
		}
		void SetScale(const Vector3& v)
		{
			mScale = v;
			isDirty = true;
		}
		void SetRotation(const Vector3& v)
		{
			mRotation = v;
			isDirty = true;
		}

		const Vector3& Position() const
		{
			return mPosition;
		}
		const Vector3& Scale() const
		{
			return mScale;
		}
		const Vector3& Rotation() const
		{
			return mRotation;
		}

		const Matrix4x4& GetWorldMatrix()
		{
			if (isDirty)
			{
				Matrix4x4 scaleMat = Matrix4x4::MatrixScaling(mScale.x, mScale.y, mScale.z);
				Matrix4x4 offsetMat = Matrix4x4::MatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
				mWorld = scaleMat * offsetMat;
			}
			return mWorld;
		}

	private:
		bool isDirty = true; // if world matrix needs to be rebuilt
		Matrix4x4 mWorld;	// TODO, why not use XMMATRIX

		Vector3 mPosition;
		Vector3 mScale;
		Vector3 mRotation;	// Quaternion
	};
}

#endif // !TRANSFORM_H
