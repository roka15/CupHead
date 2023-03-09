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
		void SetActive(const bool _flag) { mbActive = _flag; }
		const bool& GetActive() { return mbActive; }
 	private:
		std::vector<GameObject*> mObjs;
		bool mbActive;
	};
}


