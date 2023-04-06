#include "SceneManager.h"
#include "PlayMapScene.h"
#include "TitleScene.h"
#include "MainMenuScene.h"
#include "MedusaScene.h"
#include "TutorialScene.h"
#include "Camera.h"
#include "Rectangle.h"
#include "UI.h"
#include "Player.h"
#include "Ground.h"
#include "Animator.h"
#include "Time.h"
#include "ObjectPool.h"
#include "Bullet.h"
namespace yeram_client
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	GameObject* SceneManager::mLoadingScreen = nullptr;
	bool SceneManager::mbLoadScreenFlag;

	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)ESceneType::MAX);
		mScenes[(UINT)ESceneType::Title] = new TitleScene(L"Title");
		mScenes[(UINT)ESceneType::MainMenu] = new MainMenuScene(L"Main");
		mScenes[(UINT)ESceneType::PlayMap] = new PlayMapScene(L"Play");
		mScenes[(UINT)ESceneType::BossMedusa] = new MedusaScene(L"Medusa");
		mScenes[(UINT)ESceneType::BossDevil] = new TutorialScene(L"Devil");
		

		//애니 재생으로만 쓸 pool
		core::ObjectPool<Animator>::Initialize(300);
		core::ObjectPool<SpriteRenderer>::Initialize(300);
		//core::ObjectPool<UI>::Initialize(200);
		core::ObjectPool<Player>::Initialize(1, 1);
		//core::ObjectPool<Ground>::Initialize(100, 100);
		core::ObjectPool<Ground>::Initialize(1, 1);
		
		core::ObjectPool<Bullet>::Initialize(300);
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
		mActiveScene->OnEnter();


		mLoadingScreen = new GameObject();
		mLoadingScreen->GetComponent<Transform>()->SetPos(Vector2{ 800,900 });
		mLoadingScreen->SetName(L"LoadScreen");
		Animator* ani = mLoadingScreen->AddComponent<Animator>();
		std::wstring key
			= ani->CreateAnimations(L"..\\Resources\\Menu_Screen\\Loading\\Open", Vector2::Zero, 0.1f, true);
		
		ani->GetCompleteEvent(key) = std::bind
		(
			[]()->void
		{
			CloseLodingScreen();
		});

		key = ani->CreateAnimations(L"..\\Resources\\Menu_Screen\\Loading\\Close", Vector2::Zero, 0.1f, true);
		//ani->Play(key, false);

		ani->GetCompleteEvent(key) = std::bind
		(
			[]()->void
		{
			mLoadingScreen->SetActive(false);
			mbLoadScreenFlag = false;
		});

		mbLoadScreenFlag = false;
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	
		if (mbLoadScreenFlag == true)
		{
			mLoadingScreen->Update();
		}
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	
		if (mbLoadScreenFlag == true)
		{
			mLoadingScreen->Render(hdc);
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

		core::ObjectPool<Bullet>::Release();
		core::ObjectPool<Animator>::Release();
		core::ObjectPool<SpriteRenderer>::Release();
		//core::ObjectPool<UI>::Release();
		core::ObjectPool<Ground>::Release();
		core::ObjectPool<Player>::Release();
		//core::ObjectPool<Ground>::Release();

		mLoadingScreen->Release();
		delete mLoadingScreen;
	}

	void SceneManager::LoadScene(ESceneType _type)
	{
		Camera::Clear();
		std::queue<GameObject*> temp_queue;
		Scene* cur = mActiveScene;
		mActiveScene = mScenes[(UINT)_type];
		cur->OnExit();
		mActiveScene->OnEnter();
	}

	Scene* SceneManager::GetActiveScene()
	{
		return mActiveScene;
	}

	std::shared_ptr<GameObject> SceneManager::FindObject(std::wstring _name)
	{
		return mActiveScene->FindObject(_name);
	}

	void SceneManager::RemoveObject(GameObject* _obj)
	{
		mActiveScene->RemoveGameObject(_obj);
	}

	void SceneManager::ChagePosGameObjects(const Vector2& _offset)
	{
		mActiveScene->ChagePosGameObjects(_offset);
	}

	void SceneManager::ChangeScaleGameObjects(const Vector2& _scale)
	{
		mActiveScene->ChageScaleGameObjects(_scale);
	}

	void SceneManager::OpenLodingScreen()
	{
		mLoadingScreen->SetActive(true);
		mbLoadScreenFlag = true;
		Animator* ani = mLoadingScreen->GetComponent<Animator>();
		ani->Play(L"LoadingOpen", false);
	}

	void SceneManager::CloseLodingScreen()
	{
		Animator* ani = mLoadingScreen->GetComponent<Animator>();
		ani->Play(L"LoadingClose", false);
	}

	SceneManager::~SceneManager()
	{
	}

}
