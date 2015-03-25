#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstring>
#include <cmath>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <d3dUtil.h>
#include "Vector.h"
#include "Debug.h"

namespace RenderFish
{

	struct Matrix3x3
	{
	private:
		float m[3][3];

	public:
		Matrix3x3() {}
		Matrix3x3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33)
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33;
		}
		Matrix3x3(float* array)
		{
			memcpy(m, array, sizeof(float) * 9);
			//for (int idx = 0; idx < 9; ++idx)
			//{
			//	m[idx / 3][idx % 3] = array[idx];
			//}
		}
		~Matrix3x3() {}

		float det()
		{
			return m[0][0] * m[1][1] * m[2][2]
				+ m[0][1] * m[1][2] * m[2][0] 
				+ m[0][2] * m[1][0] * m[2][1]
				- m[0][0] * m[1][2] * m[2][1] 
				- m[0][1] * m[1][0] * m[2][2] 
				- m[0][2] * m[1][1] * m[2][0];
		}

		void transpose()
		{

		}

		void inverse()
		{

		}

		float* operator[](int index)
		{
			return m[index];
		}

	public:
		static Matrix3x3 Identity;
	};


	struct Matrix4x4
	{
		union
		{
			//struct  // VS not support this feature, http://stackoverflow.com/questions/21968635/invalid-union-member
			//{
			//	Vector4 r[4];
			//};
			//
			//struct
			//{
			//	float _11, _12, _13, _14;
			//	float _21, _22, _23, _24;
			//	float _31, _32, _33, _34;
			//	float _41, _42, _43, _44;
			//};
			float m[4][4];
			float mArray[16];
		};
		

	public:
		Matrix4x4() { ZeroMemory(this, sizeof(*this)); }
		Matrix4x4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
			m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
		}
		Matrix4x4(float* floatArray/*float[16]*/)
		{
			memcpy(m, floatArray, sizeof(float) * 16);
		}
		Matrix4x4(const XMMATRIX& mat)
		{
			memcpy(m, &mat, sizeof(float) * 16);
		}
		~Matrix4x4() {}

		float det()
		{
			return m[0][0] * m[1][1] * m[2][2] * m[3][3] 
				+ m[0][1] * m[1][2] * m[2][3] * m[3][0]
				+ m[0][2] * m[1][3] * m[2][0] * m[3][1]
				+ m[0][3] * m[1][0] * m[2][1] * m[3][2]
				- m[0][0] * m[1][3] * m[2][2] * m[3][1]
				- m[0][1] * m[1][0] * m[2][3] * m[3][2]
				- m[0][2] * m[1][1] * m[2][0] * m[3][3]
				- m[0][3] * m[1][2] * m[2][1] * m[3][0];
		}
		void transpose()
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = i + 1; j < 4; j++)
				{
					float temp = m[i][j];
					m[i][j] = m[j][i];
					m[j][i] = temp;
				}
			}
		}
		void inverse()
		{
			auto adjMat = this->adjointMatrix();
			float det = this->det();
			(*this) = adjMat / det;
		}

		Matrix4x4 adjointMatrix()
		{
			Matrix4x4 result;
			float f[9];

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int idx = 0;
					int k = 0;
					while (idx < 16)  
					{
						if (idx / 4 != i && idx % 4 != j)
						{
							//f[k++] = m[idx / 4][idx % 4];
							f[k++] = mArray[idx];
						}
						idx++;
					}
					auto Aij = Matrix3x3(f);
					result[j][i] = Aij.det();
					if ((i + j) & 1)
					{
						result[j][i] *= -1;		// note! transpose!
					}
				}
			}
			return result;
		}

		float* operator[](int idx)
		{
			return m[idx];
		}
		const float* operator[](int idx) const
		{
			return m[idx];
		}
		float operator()(int row, int col) const
		{
			assert(row >= 0 && row < 4 && col >= 0 && col < 4);
			return m[row][col];
		}
		float& operator()(int row, int col)
		{
			assert(row >= 0 && row < 4 && col >= 0 && col < 4);
			return m[row][col];
		}
		//FLOAT       operator() (UINT Row, UINT Column) CONST{ return m[Row][Column]; }
		//FLOAT&      operator() (UINT Row, UINT Column) { return m[Row][Column]; }
		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4 mat)
		{
			os << "[ ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					os << mat.m[i][j] << ", ";
				}
				os << "| ";
			}
			os << "]";
			return os;
		}
		friend const Matrix4x4 operator/(const Matrix4x4& mat, float k)
		{
			Matrix4x4 result;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					result[i][j] = mat[i][j] / k;
				}
			}
			return result;
		}
		friend const Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
		{
			Matrix4x4 result;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					result[i][j] = 0;
					for (int k = 0; k < 4; k++)
					{
						result[i][j] += lhs[i][k] * rhs[k][j];
					}
				}
			}
			return result;
		}

		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Matrix[";
			for (int i = 0; i < 15; i++)
			{
				ss << mArray[i] << ",";
				if (i % 4 == 3)
				{
					ss << " ";
				}
			}
			ss << mArray[15];
			ss << "]";
			return ss.str();
		}

	public:
		//static Matrix4x4 Zero;
		static Matrix4x4 Identity;
		static Matrix4x4 MatrixScaling(const Vector3& v)
		{
			return MatrixScaling(v.x, v.y, v.z);
		}
		static Matrix4x4 MatrixScaling(float x, float y, float z)
		{
			return Matrix4x4(
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1
				);
		}

		static Matrix4x4 MatrixTranslation(const Vector3&  v)
		{
			return MatrixTranslation(v.x, v.y, v.z);
		}
		static Matrix4x4 MatrixTranslation(float x, float y, float z)
		{
			return Matrix4x4(
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1);
		}

		static Matrix4x4 Inverse(const Matrix4x4& mat)
		{
			Matrix4x4 retMat = mat;
			retMat.inverse();
			return retMat;
		}

		static Matrix4x4 Transpose(const Matrix4x4& mat)
		{
			Matrix4x4 retMat = mat;
			retMat.transpose();
			return retMat;
		}
		static Matrix4x4 InverseTranspose(const Matrix4x4& mat)
		{
			// Inverse-transpose is just applied to normals.  So zero out 
			// translation row so that it doesn't get into our inverse-transpose
			// calculation--we don't want the inverse-transpose of the translation.
			Matrix4x4 retMat = mat;
			retMat(3, 0) = 0;
			retMat(3, 1) = 0;
			retMat(3, 2) = 0;
			retMat(3, 3) = 1;
			retMat.inverse();
			retMat.transpose();
			return retMat;
		}

		static Matrix4x4 PerspectiveFovLH(FLOAT FovAngleY, FLOAT AspectRatio, FLOAT NearZ, FLOAT FarZ)
		{
			Matrix4x4 proj;
			
			float t = tan(FovAngleY * 0.5f);
			proj[0][0] = 1 / (t * AspectRatio);
			proj[1][1] = 1 / t;
			proj[2][2] = FarZ / (FarZ - NearZ);
			proj[2][3] = 1.0f;
			proj[3][2] = NearZ * FarZ / (NearZ - FarZ);
			
			return proj;
		}
		static Matrix4x4 LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
		{
			Vector3 d = (at - eye).Normalize();
			Vector3 r = Vector3::Cross(up, d).Normalize();
			Vector3 u = Vector3::Cross(d, r).Normalize();

			float x = -Vector3::Dot(eye, r);
			float y = -Vector3::Dot(eye, u);
			float z = -Vector3::Dot(eye, d);

			Matrix4x4 mat;
			mat[0][0] = r.x;
			mat[1][0] = r.y;
			mat[2][0] = r.z;
			mat[3][0] = x;

			mat[0][1] = u.x;
			mat[1][1] = u.y;
			mat[2][1] = u.z;
			mat[3][1] = y;

			mat[0][2] = d.x;
			mat[1][2] = d.y;
			mat[2][2] = d.z;
			mat[3][2] = z;

			mat[0][3] = 0;
			mat[1][3] = 0;
			mat[2][3] = 0;
			mat[3][3] = 1;

			return mat;
		}
		static Matrix4x4 RotationAxis(const Vector3& axis, float angle)	// TODO
		{
			//auto& a = axis;
			//float s = sinf(angle);
			//float c = cosf(angle);
			//return Matrix4x4(
			//	c + a.x*a.x*(1 - c), a.x*a.y*(1 - c) - a.z*s, a.x*a.z*(1 - c) + a.y*s, 0,
			//	a.x*a.y*(1 - c) + a.z*s, c + a.y*a.y*(1 - c), a.y*a.z*(1 - c) - a.x*s, 0,
			//	a.x*a.z*(1 - c) - a.y*s, a.y*a.z*(1 - c) + a.x*s, c + a.z*a.z*(1-c), 0,
			//	0, 0, 0, 1);
			return Matrix4x4(XMMatrixRotationAxis(axis.ToXMVector(true), angle));
		}
		static Matrix4x4 RotationX(const float angle)
		{
			float fSinAngle = sinf(angle);
			float fCosAngle = cosf(angle);
			return Matrix4x4(
				1, 0, 0, 0,
				0, fCosAngle, -fSinAngle, 0,
				0, -fSinAngle, fCosAngle, 0,
				0, 0, 0, 1);
		}
		static Matrix4x4 RotationY(const float angle)
		{
			float fSinAngle = sinf(angle);
			float fCosAngle = cosf(angle);
			return Matrix4x4(
				fCosAngle, 0, -fSinAngle, 0,
				0, 1, 0, 0,
				fSinAngle, 0, fCosAngle, 0,
				0, 0, 0, 1);
		}
		static Matrix4x4 RotationZ(const float angle)
		{
			float fSinAngle = sinf(angle);
			float fCosAngle = cosf(angle);
			return Matrix4x4(
				fCosAngle, fSinAngle, 0, 0,
				-fSinAngle, fCosAngle, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
	};

}

#endif