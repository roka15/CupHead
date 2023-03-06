#pragma once
#include "CommonInclude.h"
#include "GameObject.h"
namespace yeram_client
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		void AddGameObject(GameObject* obj);
	private:
		std::vector<GameObject*> mObjs;
	};
}


