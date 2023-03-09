#pragma once
#include "Engine.h"
#include "Component.h"
#include "Image.h"
#include "SceneManager.h"
#include "Transform.h"
namespace yeram_client
{
	class GameObject:public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		template<typename T>
		static inline T* Instantiate(ELayerType _type)
		{
			T* obj = new T();
			//object 생성.
			Scene* cur =SceneManager::GetActiveScene();
			cur->AddGameObject(obj, _type);
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(Vector2 _pos,ELayerType _type)
		{
			T* obj = new T();
			//object 생성.
			Scene* cur=SceneManager::GetActiveScene();
			cur->AddGameObject(obj, _type);
			obj->GameObject::GetComponent<Transform>()->SetPos(_pos);
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(const std::wstring _name, Vector2 _pos, ELayerType _type)
		{
			T* obj = new T();
			obj->SetName(_name);
			//object 생성.
			Scene* cur = SceneManager::GetActiveScene();
			cur->AddGameObject(obj, _type);
			obj->GameObject::GetComponent<Transform>()->SetPos(_pos);
			return obj;
		}
		static void Destroy(GameObject* _obj)
		{

		}
		static void Destroy(GameObject* _obj, float _time)
		{

		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			comp->SetOwner(this);
			mComponents[compType] = comp;
			return comp;
		}
		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				if (dynamic_cast<T*>(comp))
				{
					return dynamic_cast<T*>(comp);
				}
			}
			return nullptr;
		}
		template<typename T>
		void SetActive(bool _flag)
		{
			T* com = GetComponent<T>();
			if (com == nullptr)
				return;
			com->SetActive(_flag);
		}
		template<typename T>
		const bool& GetActive()
		{
			T* com = GetComponent<T>();
			//예외처리 안한 이유는 없는 컴포넌트일때 false 반환이 아니라 터지게 하려고 했음.

			return com->GetActive();
		}

	protected:
		HBRUSH brush;
		HPEN pen;
		bool flag;
		//Image* mImage;
		
	private:
		std::vector<Component*> mComponents;
	};
}

