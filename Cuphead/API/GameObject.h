#pragma once
#include "Engine.h"
#include "Component.h"
#include "Image.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Rigidbody.h"
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
		static inline T* Instantiate(GameObject* _parent = nullptr,ELayerType _type=ELayerType::BackObject)
		{
			T* obj = new T();
			obj->SetParent(_parent);
			GameObject* obj_parent = obj->GetParent();
			if (obj_parent != nullptr)
			{
				obj_parent->AddChild(obj);
			}
			else // 부모가 없으면 레이어가 관리해줘야 하는 객체이므로 layer에 등록.
			{
				Scene* cur = SceneManager::GetActiveScene();
				cur->AddGameObject(obj, _type);
			}
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(Vector2 _pos, GameObject* _parent = nullptr, ELayerType _type = ELayerType::NONE)
		{
			T* obj = new T();
			obj->SetParent(_parent);
			GameObject* obj_parent = obj->GetParent();
			if (obj_parent != nullptr)
			{
				obj_parent->AddChild(obj);
			}
			else
			{
				Scene* cur = SceneManager::GetActiveScene();
				cur->AddGameObject(obj, _type);
			}
			obj->GameObject::GetComponent<Transform>()->SetPos(_pos);
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(const std::wstring _name, Vector2 _pos,GameObject* _parent = nullptr, ELayerType _type = ELayerType::NONE)
		{
			T* obj = new T();
			obj->SetName(_name);
			obj->SetParent(_parent);
			GameObject* obj_parent = obj->GetParent();
			if (obj_parent != nullptr)
			{
				obj_parent->AddChild(obj);
			}
			else
			{
				Scene* cur = SceneManager::GetActiveScene();
				cur->AddGameObject(obj, _type);
			}
			obj->GameObject::GetComponent<Transform>()->SetPos(_pos);
			return obj;
		}
		static inline GameObject* Find(std::wstring _name)
		{
			Scene* cur = SceneManager::GetActiveScene();
			
			return cur->FindObject(_name);
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
		void SetActive(bool _flag)
		{
			mbActive = _flag;

			for (GameObject* child : mChilds)
			{
				if (child == nullptr)
					continue;
				child->SetActive(_flag);
			}
		}
		const bool& GetActive()
		{
			return mbActive;
		}
		void SetParent(GameObject* _obj) { mParent = _obj; }
		GameObject* GetParent() { return mParent; }
		GameObject* FindChild(std::wstring _name);
		GameObject* FindChild(UINT _index);
		
		void AddChild(GameObject* _child);
		UINT GetChildCount() { return mChilds.size(); }
		void RemoveChild(GameObject* _child);
		
		//자식도 같이 move
		//void MoveChild(const Vector2& _offset);
	protected:
		HBRUSH brush;
		HPEN pen;
		bool flag;
		//Image* mImage;
		
	private:
		std::vector<Component*> mComponents;
		std::vector<GameObject*> mChilds;
		GameObject* mParent;
		bool mbActive;
	};
}

