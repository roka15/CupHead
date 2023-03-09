#pragma once
#include "Entity.h"

namespace yeram_client
{
	class Layer;
	class GameObject;
	class Scene :public Entity
	{
	public:
		Scene();
		virtual ~Scene();

	   virtual void Initialize();
	   virtual void Update();
	   virtual void Render(HDC hdc);
	   virtual void Release();

	   virtual void OnEnter();
	   virtual void OnExit();
	   GameObject* FindObject(std::wstring _name);
	   void AddGameObject(GameObject* obj, ELayerType layer);
	   const ESceneType& GetSceneType() { return mCurType; }
	protected:
		std::vector<Layer*> mLayers;
		ESceneType mCurType;
	};

}

