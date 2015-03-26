#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "RFObject.h"
#include "Transform.h"
#include "Debug.h"

#ifndef GET_TYPE_NAME
#define GET_TYPE_ 
#endif

namespace RenderFish
{
	class RFMaterial : public RFObject
	{
	public:
		//Color color;
		//mainTexture;
		//Shader shader;
	};

	class GameObject;

	class Component : public RFObject
	{
		friend class GameObject;
	public:
		Component()
		{

		}

		virtual ~Component()
		{

		}

	public:
		GameObject* gameObject;
		std::string tag;
		Transform transtrom;

	public:
		virtual std::string TypeName() const
		{
			//return _typeName;
			return std::string(typeid(*this).name());	// TODO
		}

	private:
		//const static std::string _typeName;
	};
	

	class MeshRender;
	class MeshFilter;
	class RenderObject;

	class GameObject : public RFObject
	{
	public:
		GameObject()
		{

		}
		virtual ~GameObject()
		{

		}

		// ========== getter && setter
		bool Active()
		{
			return _active;
		}
		void SetActive(bool value)
		{
			_active = value;
		}

		Transform& transform()
		{
			return _transform;
		}

		// =========== Component

		template<typename T>
		void AddComponent(T *component)
		{
			const auto typeName = std::string(typeid(T).name());
			for (unsigned int i = 0; i < _components.size(); ++i)
			{
				auto& comp = _components[i];
				if (comp->TypeName() == typeName)	// if the same type of Component exists, then replace it
				{
					comp->gameObject = nullptr;
					comp->Destroy();
					_components[i] = component;
					return;
				}
			}
			// add new Component;
			component->gameObject = this;
			_components.push_back(component);
		}

		template<typename T>
		T* GetComponent()
		{
			auto typeName = std::string(typeid(T).name());
			for (auto comp : _components)
			{
				if (comp->TypeName() == typeName)
				{
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}

		void Destroy();

	public:
		void _Init();
		virtual void Update()
		{
			for (auto comp : _components)
			{
			}
		}
		void Draw();



	protected:

	private:
		bool _RenderAble()
		{
			return (nullptr != GetComponent<MeshFilter>());
		}

		


	private:
		std::string _tag = "";
		unsigned int _layer = 0;
		bool _active = true;
		Transform _transform;

		std::vector <Component*>  _components;

		//bool _renderable;
		RenderObject*  _renderObject = nullptr;
	};

	class Mesh;

	class MeshFilter : public Component
	{
	public:
		MeshFilter(Mesh* mesh) : pMesh(mesh)
		{

		}

		Mesh* pMesh;
		//RFMesh sharedMesh;
	};

	// Behaviours are Components that can be enabled or disabled.
	class Behaviour : public Component
	{
	public:
		bool enabled = true;
		bool isActiveAndEnabled = true;
	};

	// MonoBehaviour is the base class every script derives from.
	class MonoBehaviour : public Behaviour
	{
	public:
		virtual void OnEnable();
		virtual void Update();
		virtual void Draw();
	};

	class Render : public Component
	{
	public:
		RFMaterial mateial;
	};


	// The Mesh Renderer takes the geometry from the Mesh Filter and renders it at the position defined by the object¡¯s Transform component
	class MeshRender : public Render
	{
	public:
		bool renderable{ true };
		
		void OnEnable()
		{
			
		}

		void Draw()
		{
			auto meshFilter = gameObject->GetComponent<MeshFilter>();

		}
	};
}
#endif //GAMEOBJECT_H
