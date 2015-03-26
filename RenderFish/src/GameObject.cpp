#include "GameObject.h"
#include "RenderObject.h"
#include "Mesh.h"

using namespace RenderFish;

//const std::string Component::_typeName = "Component";

void RenderFish::GameObject::_Init()
{
	// add to render queue
	auto pMesh = GetComponent<MeshFilter>();
	if (pMesh != nullptr && pMesh->pMesh != nullptr)
	{
		_renderObject = new RenderObject(pMesh->pMesh);
		_renderObject->transform() = _transform;
		_renderObject->BuildGeometeryBuffers();
	}
}

void RenderFish::GameObject::Draw()
{
	for (auto comp : _components)
	{
		//comp->Draw();
	}
	if (_renderObject != nullptr)
	{
		_renderObject->Draw();
	}
}

void RenderFish::GameObject::Destroy()
{
	for (auto comp : _components)
	{
		delete comp;
	}
	_components.clear();

	delete _renderObject;
}