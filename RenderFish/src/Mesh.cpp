#include "Mesh.h"
#include <io.h>

using namespace std;
using namespace RenderFish;

void RenderFish::Mesh::LoadMeshFromFile(const std::string& strPath)
{
	Destory();

	if (_access(strPath.c_str(), 0) == -1)
	{
		Debug::LogError("Model File " + strPath + " not exists");
		return;
	}

	Assimp::Importer importer;
	const char* path = strPath.c_str();
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenNormals);

	if (!scene) {
		Debug::LogError("can not open model " + strPath);
		exit(1); // TODO
	}

	// get each mesh
	int nvertices = 0;
	int ntriangles = 0;

	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		nvertices += mesh->mNumVertices;
		ntriangles += mesh->mNumFaces;
	}

	mVertices.reserve(nvertices);
	mNormals.reserve(nvertices);
	mTriangles.resize(ntriangles * 3);	// TODO, *3?
	int idx = 0;
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
			aiVector3D& v = mesh->mVertices[j];
			aiVector3D& n = mesh->mNormals[j];
			mVertices.push_back(Vector3(v.x, v.y, v.z));
			mNormals.push_back(Vector3(n.x, n.y, n.z));
			//aabb.expand(glm::vec3(v.x, v.y, v.z));
		}
		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			const aiFace& Face = mesh->mFaces[j];
			assert(Face.mNumIndices == 3);
			mTriangles[idx++] = Face.mIndices[0];
			mTriangles[idx++] = Face.mIndices[1];
			mTriangles[idx++] = Face.mIndices[2];
		}
	}
}