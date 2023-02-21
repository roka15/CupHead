#include "SceneManager.h"
#include "PlayScene.h"

namespace yeram_client
{
	std::vector<Scene*> SceneManager::mScenes = {};
	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)ESceneType::MAX);
		mScenes[(UINT)ESceneType::Play] = new PlayScene();

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Initalize();
		}

	}

	void SceneManager::Update()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Update();
		}
	}

	void SceneManager::Render(HDC hdc)
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Render(hdc);
		}
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Release();
			delete scene;
			scene = nullptr;
		}
	}

	SceneManager::~SceneManager()
	{
	}

}
