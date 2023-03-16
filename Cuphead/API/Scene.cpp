#include "Scene.h"
#include "Application.h"
#include "Layer.h"

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
			if (layer->GetActive() == false)
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
		Layer* cur_layer = mLayers[(UINT)ELayerType::Player];
		if (cur_layer != nullptr)
		{
			Scene* active = SceneManager::GetActiveScene();
			Layer* active_layer = active->mLayers[(UINT)ELayerType::Player];
			std::vector<GameObject*>& recv_obj = active_layer->GetGameObjectList();
			if (recv_obj.size() == 0)
			{
				std::vector<GameObject*>& send_obj = cur_layer->GetGameObjectList();
				for (auto player_obj : send_obj)
				{
					recv_obj.push_back(player_obj);
				}
				send_obj.clear();
			}
		}
	}

	void Scene::ChagePosGameObjects(const Vector2& _offset)
	{
		for (auto layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->ChagePosGameObjects(_offset);
		}
	}

	void Scene::ChageScaleGameObjects(const Vector2& _scale)
	{
		for (auto layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->ChageScaleGameObjects(_scale);
		}
	}

	GameObject* Scene::FindObject(std::wstring _name)
	{
		for (auto layer : mLayers)
		{
			GameObject* obj=layer->FindObject(_name);
			if (obj != nullptr)
				return obj;
		}
		return nullptr;
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