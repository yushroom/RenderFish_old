#ifndef VECTOR_H
#define VECTOR_H

#include <d3dx11.h>
#include <xnamath.h>
#include <cmath>
#include <string>
#include <sstream>

namespace RenderFish
{
	struct Matrix4x4;

	struct Vector2
	{
		float x;
		float y;

		Vector2() : Vector2(0, 0) {}
		Vector2(float x, float y) : x(x), y(y) {}
		//Vector2(const Vector2& v) : Vector2(v.x, v.y) {}
	};

	struct Vector4;

	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3() : Vector3(0, 0, 0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		Vector3(const float* a) : Vector3(a[0], a[1], a[2]) {}
		//Vector3(const Vector3& v) : Vector3(v.x, v.y, v.z) {}

		void operator+=(const Vector3& v)
		{
			x += v.x; y += v.y; z += v.z;
		}
		void operator-=(const Vector3& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
		}
		const Vector3 friend operator+(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
		}
		const Vector3 friend operator-(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
		}
		//float friend operator*(const Vector3& lhs, const Vector3& rhs)	// == Dot
		//{
		//	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		//}
		const Vector3 friend operator*(const Vector3& v, const float scale)	// scale
		{
			return Vector3(v.x * scale, v.y * scale, v.z * scale);
		}
		const Vector3 friend operator*(const float scale, const Vector3& v)	// scale
		{
			return Vector3(v.x * scale, v.y * scale, v.z * scale);
		}
		//float friend operator*(const float scale, const Vector3& v)	// == Dot
		//{
		//	return Vector3(v.x * scale, v.y * scale, v.z * scale);
		//}
		const Vector3 Normalize() const
		{
			float l = sqrt(x*x + y*y + z*z);
			return Vector3(x/l, y/l, z/l);
		}

		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Vector3 [" << x << ", " << y << ", " << z << "]";
			return ss.str();
		}

		XMVECTOR ToXMVector(bool isVector = false) const
		{
			if (isVector)
				return XMVectorSet(x, y, z, 0);
			else
				return XMVectorSet(x, y, z, 1);
		}

	public:
		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 Back;
		const static Vector3 Down;
		const static Vector3 forward;
		const static Vector3 Left;
		const static Vector3 Right;
		const static Vector3 Up;
		
		static float Dot(const Vector3& lhs, const Vector3& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y +lhs.z * rhs.z;
		}
		static const Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
		}
		static Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);	// todo
	};


	struct Vector4
	{
		union
		{
			//float vector4_f32[4];
			//unsigned int vector4_u32[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float v[4];
			//unsigned int u[4];
		};

		Vector4() : Vector4(0, 0, 0, 0) {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		Vector4(const float* a) : Vector4(a[0], a[1], a[2], a[3]) {}
		//Vector4(const Vector4& v) : Vector4(v.x, v.y, v.z, v.w) {}

#pragma region Helper
		static Vector4 TransformNormal(const Vector4& v, const Matrix4x4& m);	// TODO

#pragma endregion

#pragma region Method
		void operator= (const Vector4& v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void operator+=(const Vector4& v)
		{
			x += v.x; y += v.y; z += v.z; w += v.w;
		}

		const Vector4 friend operator+(const Vector4& lhs, const Vector4& rhs)
		{
			return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
		}
		const Vector4 friend operator-(const Vector4& lhs, const Vector4& rhs)
		{
			return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
		}
		//float friend operator*(const Vector4& lhs, const Vector4& rhs)	// == Dot
		//{
		//	return Vector4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
		//}
		const Vector4 friend operator*(const Vector4& v, const float scale)	// scale
		{
			return Vector4(v.x * scale, v.y * scale, v.z * scale, v.w * scale);
		}
		//float friend operator*(const float scale, const Vector4& v)	// == Dot
		//{
		//	return Vector4(v.x * scale, v.y * scale, v.z * scale, v.w * scale);
		//}
		//const Vector4 Normalize() const
		//{
		//	float l = sqrt(x*x + y*y + z*z);
		//	return Vector4(x / l, y / l, z / l, w / l);
		//}
		//const Vector4 operator*(const Matrix4x4& mat)
		//{

		//}

	public:
		static float Dot(const Vector4& lhs, const Vector4& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		//static const Vector4 Cross(const Vector4& lhs, const Vector4& rhs)
		//{
		//	return Vector4(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
		//}
#pragma endregion
	};
}

#endif
