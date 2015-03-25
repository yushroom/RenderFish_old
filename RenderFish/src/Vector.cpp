#include "Vector.h"
#include "Matrix.h"
using namespace RenderFish;

const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
const Vector3 Vector3::One(1.f, 1.f, 1.f);
const Vector3 Vector3::Back{ 0.f, 0.f, -1.f };
const Vector3 Vector3::Down{ 0, -1, 0 };
const Vector3 Vector3::forward{ 0, 0, 1 };
const Vector3 Vector3::Left{ -1, 0, 0 };
const Vector3 Vector3::Right{ 1, 0, 0 };
const Vector3 Vector3::Up{ 0, 1, 0 };

Vector3 RenderFish::Vector3::TransformNormal(const Vector3& v, const Matrix4x4& m)
{
	return Vector3(m[2]) * v.z + Vector3(m[1]) * v.y + Vector3(m[0]) * v.x;
}

Vector4 RenderFish::Vector4::TransformNormal(const Vector4& v, const Matrix4x4& m)
{
	return Vector4(m[2]) * v.z + Vector4(m[1]) * v.y + Vector4(m[0]) * v.x;
}