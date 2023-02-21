#include "Layer.h"
namespace yeram_client
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
	}
	void Layer::Initalize()
	{   
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Initalize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Render(hdc);
		}
	}
	void Layer::Release()
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Release();
			delete obj;
		}
	}
	void Layer::AddGameObject(GameObject* obj)
	{
		mObjs.push_back(obj);
	}
}