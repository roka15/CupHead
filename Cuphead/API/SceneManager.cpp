#include "SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "MainMenuScene.h"
namespace yeram_client
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)ESceneType::MAX);
		mScenes[(UINT)ESceneType::Title] = new TitleScene();
		mScenes[(UINT)ESceneType::MainMenu] = new MainMenuScene();
		mScenes[(UINT)ESceneType::Play] = new PlayScene();
		

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
		mActiveScene->Update();
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
		mActiveScene->Initialize();
	}

	SceneManager::~SceneManager()
	{
	}

}
