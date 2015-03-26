#ifndef MESH_H
#define MESH_H

#ifndef SafeDelete
#define SafeDelete(x) { delete x; x = nullptr; }
#endif

#include <assert.h>
#include <string>
#include <memory>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RFObject.h"
#include "Debug.h"
#include "Vector.h"

using std::string;

namespace RenderFish
{
	//typedef std::vector<int>  IndexArray;
	typedef std::vector<unsigned int>  UINTArray;
	typedef std::vector<Vector3> Vector3Array;
	typedef std::vector<Vector2> Vector2Array;
	//typedef std::vector<Vector3> VertexArray;
	//typedef std::vector<Vector3> NormalArray;
	//typedef std::vector<Vector2> UVArray;

	class Mesh : public RFObject
	{
	public:
		Mesh() {};
		Mesh(const string& strPath)
		{
			LoadMeshFromFile(strPath);
		}
		virtual ~Mesh()
		{
			Destory();
		};

		void Destory()
		{
			mTriangles.clear();
			mVertices.clear();
			mNormals.clear();
			mUV.clear();
		}

		enum MeshComponent
		{
			index = 0,
			vertex,
			normal,
			uv
		};

		void SetComponent(void* array, MeshComponent comp)
		{
		}

		void SetVerticesAndIndices(Vector3Array& vertices, UINTArray& indices)
		{
			mVertices = vertices;
			mTriangles = indices;
		}

		void SetNormal(Vector3Array& normals)
		{
			mNormals = normals;
		}

		void LoadMeshFromFile(const std::string& strPath);


		// getter
		int VertexCount() const
		{
			return mVertices.size();
		}
		int IndexCount() const
		{
			return mTriangles.size();
		}
		const UINTArray& Triangles() const
		{
			return mTriangles;
		}
		const Vector3Array& Vertices()
		{
			return mVertices;
		}
		const Vector3Array& Normals() const
		{
			return mNormals;
		}
		const Vector2Array& UV() const
		{
			return mUV;
		}

	private:
		//bounds;
		//colors;
		UINTArray	mTriangles;
		Vector3Array mVertices;
		Vector3Array mNormals;
		Vector2Array mUV;
	};

	class MeshManager
	{

	};

}

#endif