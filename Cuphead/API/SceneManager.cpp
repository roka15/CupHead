#include "SceneManager.h"
#include "PlayMapScene.h"
#include "TitleScene.h"
#include "MainMenuScene.h"
#include "MedusaScene.h"
#include "Camera.h"
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
		mScenes[(UINT)ESceneType::BossMedusa] = new MedusaScene();
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
			case ESceneType::BossMedusa:
				mActiveScene = mScenes[(UINT)ESceneType::BossMedusa];
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
		Camera::Clear();
		mActiveScene->OnExit();
		mActiveScene = mScenes[(UINT)_type];
		mActiveScene->OnEnter();
	}

	Scene* SceneManager::GetActiveScene()
	{
		return mActiveScene;
	}

	GameObject* SceneManager::FindObject(std::wstring _name)
	{
		return mActiveScene->FindObject(_name);
	}

	void SceneManager::ChagePosGameObjects(const Vector2& _offset)
	{
		mActiveScene->ChagePosGameObjects(_offset);
	}

	void SceneManager::ChangeScaleGameObjects(const Vector2& _scale)
	{
		mActiveScene->ChageScaleGameObjects(_scale);
	}

	SceneManager::~SceneManager()
	{
		
	}

}
