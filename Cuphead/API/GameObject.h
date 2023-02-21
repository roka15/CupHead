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
		void AddComponent(Component* _component);
		void DeleteComponent(Component* _component);
	protected:
		Vector2 mPos;
		HBRUSH brush;
		HPEN pen;
		bool flag;
	private:
		std::vector<Component*> mComponents;
	};
}

