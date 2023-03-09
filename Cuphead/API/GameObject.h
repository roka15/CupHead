#pragma once
#include "Engine.h"
#include "Component.h"
#include "Image.h"
#include "Scene.h"
#include "SceneManager.h"
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
			//object 持失.
			//Scene* cur; //=SceneManager::GetActiveScene();
			//cur->AddGameObject(obj, _type);
			return 
		}
		template<typename T>
		static inline T* Instantiate(Vector2 _pos,ELayerType _type)
		{
			T* obj = new T();
			//object 持失.
			//Scene* cur; //=SceneManager::GetActiveScene();
			//cur->AddGameObject(obj, _type);
			//obj->GameObject::GetComponent<Transform>().SetPos(_pos);
			return
		}
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

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
	
	protected:
		HBRUSH brush;
		HPEN pen;
		bool flag;
		//Image* mImage;
		
	private:
		std::vector<Component*> mComponents;
	};
}

