#pragma once
#include "Entity.h"
#include "Layer.h"
namespace yeram_client
{
	class Scene :public Entity
	{
	public:
		Scene();
		virtual ~Scene();

	   virtual void Initalize();
	   virtual void Update();
	   virtual void Render(HDC hdc);
	   virtual void Release();
	   void AddGameObject(GameObject* obj, ELayerType layer);
	private:
		std::vector<Layer*> mLayers;
	};

}

