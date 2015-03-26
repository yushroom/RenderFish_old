#include "RenderObject.h"

using namespace RenderFish;

void RenderObject::BuildGeometeryBuffers(bool forceRebuilt /*= false*/)
{
	auto pDevice = RenderContext::Device();

	if (isBufferCreated && !forceRebuilt)
	{
		return;
	}

	UINT vcount = mMesh->VertexCount();
	UINT tcount = mMesh->IndexCount();

	std::vector<Vertex::Basic32> vertices(vcount);
	auto& vs = mMesh->Vertices();
	auto& ns = mMesh->Normals();
	for (UINT i = 0; i < vcount; ++i)
	{
		auto& v = vertices[i];
		v.Pos.x = vs[i].x;
		v.Pos.y = vs[i].y;
		v.Pos.z = vs[i].z;
		v.Normal.x = ns[i].x;
		v.Normal.y = ns[i].y;
		v.Normal.z = ns[i].z;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::Basic32) * vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(pDevice->CreateBuffer(&vbd, &vinitData, &mVB));

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * tcount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &mMesh->Triangles()[0];
	HR(pDevice->CreateBuffer(&ibd, &iinitData, &mIB));

	isBufferCreated = true;
}