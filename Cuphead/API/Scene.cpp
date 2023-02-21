#include "Scene.h"
namespace yeram_client
{
	void Scene::Initalize()
	{
		mLayers.resize((UINT)ELayerType::MAX);
		mLayers[(UINT)ELayerType::Player] = new Layer();
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Initalize();
		}
	}

	void Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Update();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Render(hdc);
		}
	}

	void Scene::Release()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Release();
			delete layer;
		}
	}

	void Scene::AddGameObject(GameObject* obj, ELayerType layer)
	{
		mLayers[(UINT)layer]->AddGameObject(obj);
	}

	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{
	}
}