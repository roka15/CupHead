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
		GameObject* FindObject(std::wstring _name);
		std::vector<GameObject*>& GetGameObjectList();
		void ChagePosGameObjects(const Vector2& _offset);
		void ChageScaleGameObjects(const Vector2& _scale);
		void AddGameObject(GameObject* obj);
		void SetActive(const bool _flag) { mbActive = _flag; }
		const bool& GetActive() { return mbActive; }
 	private:
		std::vector<GameObject*> mObjs;
		bool mbActive;
	};
}


