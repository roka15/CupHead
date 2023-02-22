#include "SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
namespace yeram_client
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)ESceneType::MAX);
		mScenes[(UINT)ESceneType::Play] = new PlayScene();
		mScenes[(UINT)ESceneType::Title] = new TitleScene();

		mActiveScene = mScenes[(UINT)ESceneType::Title];
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Initialize();
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
		mActiveScene->Render(hdc);
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

	void SceneManager::LoadScene(ESceneType _type)
	{
		mActiveScene = mScenes[(UINT)_type];
	}

	SceneManager::~SceneManager()
	{
	}

}
