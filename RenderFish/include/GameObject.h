#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Transform.h"
#include "Debug.h"

#ifndef GET_TYPE_NAME
#define GET_TYPE_ 
#endif

namespace RenderFish
{
	class RFObject
	{
	public:
		bool hideFlags;
		std::string name;

		RFObject()
		{

		}
		virtual ~RFObject()
		{

		}

		virtual std::string ToString()
		{
			return name;
		}

		static void Destroy()
		{

		}
	};

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
		GameObject* GameObject;
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

	class GameObject : public RFObject
	{
	public:
		GameObject()
		{

		}
		virtual ~GameObject()
		{

		}

		bool Active()
		{
			return _active;
		}
		void SetActive(bool value)
		{
			_active = value;
		}

		template<typename T>
		void AddComponent(T *component)
		{
			const auto typeName = std::string(typeid(T).name());
			for (unsigned int i = 0; i < _components.size(); ++i)
			{
				auto& comp = _components[i];
				if (comp->TypeName() == typeName)	// if the same type of Component exists, then replace it
				{
					comp->GameObject = nullptr;
					comp->Destroy();
					_components[i] = component;
					return;
				}
			}
			// add new Component;
			component->GameObject = this;
			_components.push_back(component);
		}

		template<typename T>
		Component* GetComponent()
		{
			auto typeName = std::string(typeid(T).name());
			for (auto comp : _components)
			{
				if (comp->TypeName() == typeName)
				{
					return comp;
				}
			}
			return nullptr;
		}

	public:

	protected:

	private:
		

	private:
		std::string _tag;
		unsigned int _layer;
		bool _active = true;
		Transform _transform;

		std::vector <Component*>  _components;
	};

	//class MeshFilter : public Component
	//{
	//public:
	//	//RFMesh mesh;
	//	//RFMesh sharedMesh;
	//};

	class Render : public Component
	{
	public:
		RFMaterial mateial;
	};

	class MeshRender : public Render
	{
		
	};
}
#endif //GAMEOBJECT_H
