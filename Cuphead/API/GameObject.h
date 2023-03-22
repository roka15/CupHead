#pragma once
#include "Engine.h"
#include "Component.h"
#include "Image.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Collider.h"
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
			obj->SetLayerType(_type);
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(Vector2 _pos, GameObject* _parent = nullptr, ELayerType _type = ELayerType::BackObject)
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
			obj->SetLayerType(_type);
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(const std::wstring _name, Vector2 _pos,GameObject* _parent = nullptr, ELayerType _type = ELayerType::BackObject)
		{
			T* obj = new T();
			obj->SetName(_name);
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
			obj->SetLayerType(_type);
			return obj;
		}
		static inline GameObject* Find(std::wstring _name)
		{
			Scene* cur = SceneManager::GetActiveScene();
			
			return cur->FindObject(_name);
		}
		static void Destroy(GameObject* _obj)
		{
			if (_obj == nullptr)
				return;
			Scene* scene = SceneManager::GetActiveScene();
			std::vector<GameObject*>& objs = scene->GetGameObjects(_obj->GetLayerType());
			for (std::vector<GameObject*>::iterator itr = objs.begin(); itr !=objs.end();itr++)
			{
				if (*itr == _obj)
					objs.erase(itr);
			}

			delete _obj;
			//object pool 완성시 pool에 반납.
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
		void SetLayerType(ELayerType _type) { mLayerType = _type; }
		ELayerType GetLayerType() { return mLayerType; }
		
		void AddChild(GameObject* _child);
		UINT GetChildCount() { return mChilds.size(); }
		void RemoveChild(GameObject* _child);
		
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void MoveObjectSetting(float _speed,EDirType _dir_type=EDirType::LEFT);
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

		ELayerType mLayerType;
	};
}

