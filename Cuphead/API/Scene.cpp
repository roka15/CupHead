#include "Scene.h"
#include "Application.h"
extern yeram_client::Application application;
namespace yeram_client
{
	void Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Initialize();
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
			layer = nullptr;
		}
		mLayers.clear();
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{

	}

	void Scene::AddGameObject(GameObject* obj, ELayerType layer)
	{
		mLayers[(UINT)layer]->AddGameObject(obj);
	}

	Scene::Scene()
	{
		mLayers.resize((UINT)ELayerType::MAX);
	}

	Scene::~Scene()
	{
	}
}