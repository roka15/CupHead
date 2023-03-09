#include "SceneManager.h"
#include "PlayMapScene.h"
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
		mScenes[(UINT)ESceneType::PlayMap] = new PlayMapScene();
		
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			switch (scene->GetSceneType())
			{
			case ESceneType::Title:
				mActiveScene = mScenes[(UINT)ESceneType::Title];
				break;
			case ESceneType::MainMenu:
				mActiveScene = mScenes[(UINT)ESceneType::MainMenu];
				break;
			case ESceneType::PlayMap:
				mActiveScene = mScenes[(UINT)ESceneType::PlayMap];
				break;
			case ESceneType::PlayStage:
				mActiveScene = mScenes[(UINT)ESceneType::PlayStage];
				break;
			case ESceneType::Ending:
				mActiveScene = mScenes[(UINT)ESceneType::Ending];
				break;
			}
			scene->Initialize();
		}
		mActiveScene = mScenes[(UINT)ESceneType::Title];
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
		mActiveScene->OnExit();
		mActiveScene = mScenes[(UINT)_type];
		mActiveScene->OnEnter();
	}

	Scene* SceneManager::GetActiveScene()
	{
		return mActiveScene;
	}

	SceneManager::~SceneManager()
	{
	}

}
