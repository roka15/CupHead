#pragma once
#include "Engine.h"
#include "Component.h"
namespace yeram_client
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initalize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
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
	protected:
		HBRUSH brush;
		HPEN pen;
		bool flag;
	private:
		std::vector<Component*> mComponents;
	};
}

