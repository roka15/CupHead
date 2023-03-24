#pragma once
#include "Component.h"
#include "Image.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Collider.h"

namespace yeram_client
{
	class GameObject :public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


		template<typename T>
		static inline T* Instantiate(GameObject* _parent = nullptr)
		{
			T* obj = new T();
			obj->SetParent(_parent);
			GameObject* obj_parent = obj->GetParent();
			if (obj_parent != nullptr)
			{
				obj_parent->AddChild(std::shared_ptr<T>(obj));
			}
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(Vector2 _pos, GameObject* _parent = nullptr)
		{
			T* obj = new T();
			obj->SetParent(_parent);
			GameObject* obj_parent = obj->GetParent();
			if (obj_parent != nullptr)
			{
				obj_parent->AddChild(std::shared_ptr<T>(obj));
			}
			obj->GameObject::GetComponent<Transform>()->SetPos(_pos);
			return obj;
		}
		template<typename T>
		static inline T* Instantiate(const std::wstring _name, Vector2 _pos, GameObject* _parent = nullptr)
		{
			T* obj = new T();
			obj->SetName(_name);
			GameObject* obj_parent = obj->GetParent();
			if (obj_parent != nullptr)
			{
				obj_parent->AddChild(std::shared_ptr<T>(obj));
			}
			obj->GameObject::GetComponent<Transform>()->SetPos(_pos);
			return obj;
		}
		static inline std::shared_ptr<GameObject> Find(std::wstring _name)
		{
			Scene* cur = SceneManager::GetActiveScene();

			return cur->FindObject(_name);
		}
		static void Destroy(GameObject* _obj)
		{
			if (_obj == nullptr)
				return;
			Scene* scene = SceneManager::GetActiveScene();
			std::vector<std::shared_ptr<GameObject>>& objs = scene->GetGameObjects(_obj->GetLayerType());
			for (std::vector<std::shared_ptr<GameObject>>::iterator itr = objs.begin(); itr != objs.end(); itr++)
			{
				if ((*itr).get() == _obj)
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

		virtual void InitComponent();

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

			for (std::shared_ptr<GameObject> child : mChilds)
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
		std::shared_ptr<GameObject> FindChild(std::wstring _name);
		std::shared_ptr<GameObject> FindChild(UINT _index);
		void SetLayerType(ELayerType _type) { mLayerType = _type; }
		ELayerType GetLayerType() { return mLayerType; }

		void AddChild(std::shared_ptr<GameObject> _child);
		UINT GetChildCount() { return mChilds.size(); }
		void RemoveChild(std::shared_ptr<GameObject> _child);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void MoveObjectSetting(float _speed, EDirType _dir_type = EDirType::LEFT);
		//자식도 같이 move
		//void MoveChild(const Vector2& _offset);
	protected:
		std::vector<Component*>& GetComponents() { return mComponents; }

	protected:
		HBRUSH brush;
		HPEN pen;
		bool flag;
		//Image* mImage;

	private:
		std::vector<Component*> mComponents;
		std::vector<std::shared_ptr<GameObject>> mChilds;
		GameObject* mParent;
		bool mbActive;

		ELayerType mLayerType;
	};
}

