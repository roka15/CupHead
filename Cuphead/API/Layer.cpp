#include "Layer.h"
namespace yeram_client
{
	Layer::Layer()
	{
		mbActive = true;
	}
	Layer::~Layer()
	{
	
	}
	void Layer::Initialize()
	{   
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Initialize();
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
			obj = nullptr;
		}
	}
	void Layer::AddGameObject(GameObject* obj )
	{
		mObjs.push_back(obj);
	}
}