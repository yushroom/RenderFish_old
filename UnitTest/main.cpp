#include "RfCore.h"

using namespace std;
using namespace RenderFish;

void printXMat(const XMMATRIX& xmat)
{
	cout << "[info]XMatrix[";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << xmat(i, j) << ",";
		}
		cout << " ";
	}
	cout << "]\n";
}
bool equalMatrix(const Matrix4x4& m, const XMMATRIX& xm)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (abs(m[i][j] - xm(i, j)) > 0.0001)
			{
				return false;
			}
		}
	}

	return true;
}
void diffMatrix(const Matrix4x4& m, const XMMATRIX& xm)
{
	if (!equalMatrix(m, xm))
	{
		cout << m.ToString() << endl;
		printXMat(xm);
	}
}
void testMatrix()
{
	float f[] = {
		1, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 4, 0,
		1, 2, 3, 1 };
	float f2[] = {
		1, 3, 5, 7,
		2, 4, 6, 8,
		11, 13, 15, 17,
		10, 12, 14, 16, 18
	};
	Matrix4x4 A(f);
	Matrix4x4 B(f2);
	XMMATRIX xA(f);
	XMMATRIX xB(f2);

	auto C = A * B;
	auto xC = xA * xB;

	auto D = Matrix4x4::Transpose(A);
	auto xD = XMMatrixTranspose(xA);
	diffMatrix(D, xD);

	//diffMatrix(C, xC);

	auto det = A.det();
	auto E = Matrix4x4::Inverse(A);

	auto xdet = XMMatrixDeterminant(xA);
	auto xE = XMMatrixInverse(&xdet, xA);

	cout << det << endl;
	diffMatrix(E, xE);

	auto F = Matrix4x4::InverseTranspose(A);
	auto xF = MathHelper::InverseTranspose(xA);
	diffMatrix(F, xF);


	auto P = Matrix4x4::PerspectiveFovLH(0.25f*3.1415926f, 45, 1, 100);
	auto xP = XMMatrixPerspectiveFovLH(0.25f*3.1415926f, 45, 1, 100);
	diffMatrix(P, xP);

	auto L = Matrix4x4::LookAtLH(Vector3(0, 0, 10), Vector3::Zero, Vector3::Up);
	auto xL = XMMatrixLookAtLH(XMVectorSet(0, 0, 10, 1), XMVectorZero(), XMVectorSet(0, 1, 0, 0));
	diffMatrix(L, xL);


	auto R = Matrix4x4::RotationAxis(Vector3(1, 1, 1), .23f);
	auto xR = XMMatrixRotationAxis(XMVectorSet(1, 1, 1, 0), .23f);
	diffMatrix(R, xR);
}

void testGameObject()
{
	GameObject go;
	Render comp;
	comp.name = "Test Component";
	go.AddComponent<Render>(&comp);

	Component* p = go.GetComponent<Render>();
	cout << p->name << endl;
	cout << p->TypeName() << endl;
}

int main()
{
	//testMatrix();
	testGameObject();

	system("pause");
	return 0;
}




