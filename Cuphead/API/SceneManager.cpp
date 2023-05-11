#include "SceneManager.h"
#include "PlayMapScene.h"
#include "TitleScene.h"
#include "MainMenuScene.h"
#include "TutorialScene.h"
#include "WorldMoveIntroScene.h"
#include "InWorldIntroScene.h"
#include "SaltBakeryShopScene.h"
#include "SaltBakerIntroScene.h"
#include "SaltBakerBossScene.h"
#include "Camera.h"
#include "Rectangle.h"
#include "UI.h"
#include "Player.h"
#include "PixelCrash.h"

#include "WorldMapObject.h"
#include "Ground.h"
#include "PlayerBullet.h"
#include "Animator.h"
#include "Time.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "MoveObject.h"
#include "CutScenePlayAnimation.h"
#include "Loading.h"

namespace yeram_client
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	GameObject* SceneManager::mLoadingScreen = nullptr;
	bool SceneManager::mbLoadScreenFlag;
	HANDLE SceneManager::mHThread;
	ESceneType SceneManager::mLoadSceneType;
	SceneManager::ELoadingState SceneManager::mLoadState;
	bool SceneManager::mbCompleteLoad;
	std::function<void()> SceneManager::mLoadMessageEvent;
	bool SceneManager::mbUseUI;
	std::queue<SceneManager::RemoveObjectInfo> SceneManager::mRemoveRequestObjs;

	void SceneManager::Initalize()
	{
		core::Loading::Initialize();
		mHThread = CreateThread(NULL, 0, core::Loading::LoadingFunc, nullptr, 0, NULL);
		if (mHThread == NULL) exit(1);


		mScenes.resize((UINT)ESceneType::MAX);
		mScenes[(UINT)ESceneType::Title] = new TitleScene(L"Title");
		mScenes[(UINT)ESceneType::MainMenu] = new MainMenuScene(L"Main");
		mScenes[(UINT)ESceneType::PlayMap] = new PlayMapScene(L"Play");
		mScenes[(UINT)ESceneType::Tutorial] = new TutorialScene(L"Tutorial");
		mScenes[(UINT)ESceneType::MoveWorldIntro] = new WorldMoveIntroScene(L"WorldMoveIntro");
		mScenes[(UINT)ESceneType::InWorldIntro] = new InWorldIntroScene(L"InWorldIntro");
		mScenes[(UINT)ESceneType::SaltBakeryShop] = new SaltBakeryShopScene(L"SaltBakerShop");
		mScenes[(UINT)ESceneType::SaltBakerBossIntro] = new SaltBakerIntroScene(L"SaltBakerIntro");
		mScenes[(UINT)ESceneType::SaltBakerBoss] = new SaltBakerBossScene(L"SaltBakerBoss");
		//애니 재생으로만 쓸 pool
		core::ObjectPool<Animator>::Initialize(100,200);
		core::ObjectPool<SpriteRenderer>::Initialize(100,200);
		core::ObjectPool<Collider>::Initialize(10);
		//core::ObjectPool<UI>::Initialize(200);
		core::ObjectPool<Player>::Initialize(1, 1);
		//core::ObjectPool<Ground>::Initialize(100, 100);
		core::ObjectPool<Ground>::Initialize(100);
		core::ObjectPool<MoveObject>::Initialize(100,200);
		core::ObjectPool<CutScenePlayAnimation>::Initialize(10);
		core::ObjectPool<PixelCrash>::Initialize(10);
		core::ObjectPool<WorldMapObject>::Initialize(10);
		core::ObjectPool<PlayerBullet>::Initialize(100,200);
		
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}



		mLoadingScreen = new GameObject();
		mLoadingScreen->GetComponent<Transform>()->SetPos(Vector2{ 800,900 });
		mLoadingScreen->SetName(L"LoadScreen");
		Animator* ani = mLoadingScreen->AddComponent<Animator>();
		std::wstring key
			= ani->CreateAnimations(L"..\\Resources\\Menu_Screen\\Loading\\Open", Vector2::Zero, 0.1f, true);

		ani->GetCompleteEvent(key) = std::bind
		(
			[ani]()->void
		{
			//fade out 재생 끝난 후 wakeup event
			core::Loading::WakeUpEvent();
			mLoadState = ELoadingState::LOADING;
			//loading screen 재생
			ani->Play(L"LoadingLoading", true);
		});

		key = ani->CreateAnimations(L"..\\Resources\\Menu_Screen\\Loading\\Close", Vector2::Zero, 0.1f, true);
		//ani->Play(key, false);

		ani->GetCompleteEvent(key) = std::bind
		(
			[]()->void
		{
			mLoadingScreen->SetActive(false);
			mLoadState = ELoadingState::NONE;
		});

		key = ani->CreateAnimations(L"..\\Resources\\Menu_Screen\\Loading\\Loading", Vector2::Zero, 0.1f, false);
		ani->GetEndEvent(key) = std::bind
		(
			[ani]()->void
		{
			mLoadState = ELoadingState::FADE_IN;
			CloseLodingScreen();
		});
		mbLoadScreenFlag = false;


		LoadScene(ESceneType::Title);
	}

	void SceneManager::Update()
	{
		switch (mLoadState)
		{
		case ELoadingState::NONE:
			mActiveScene->Update();
			break;
		case ELoadingState::FADE_OUT:
		case ELoadingState::FADE_IN:
		case ELoadingState::LOADING:
			if (mbCompleteLoad == true)
			{
				mLoadingScreen->GetComponent<Animator>()->Stop();
				core::Loading::WakeUpEvent();
				mbCompleteLoad = false;
			}
			mLoadingScreen->Update();
			break;
		}

		if (mLoadMessageEvent != nullptr)
		{
			mLoadMessageEvent();
			mLoadMessageEvent = nullptr;
		}
		RemoveObjectRequestRelease();
	}

	void SceneManager::Render(HDC hdc)
	{
		switch (mLoadState)
		{
		case ELoadingState::NONE:
			mActiveScene->Render(hdc);
			break;
		case ELoadingState::FADE_OUT:
		case ELoadingState::FADE_IN:
		case ELoadingState::LOADING:
			//mActiveScene->Render(hdc);
			mLoadingScreen->Render(hdc);
			break;
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
	
		core::ObjectPool<PixelCrash>::Release();
		
		//core::ObjectPool<UI>::Release();
		core::ObjectPool<Ground>::Release();
		core::ObjectPool<Player>::Release();
		
		core::ObjectPool<CutScenePlayAnimation>::Release();
		core::ObjectPool<WorldMapObject>::Release();
		core::ObjectPool<PlayerBullet>::Release();
        
		core::ObjectPool<MoveObject>::Release();
		core::ObjectPool<Animator>::Release();
		core::ObjectPool<SpriteRenderer>::Release();
		core::ObjectPool<Collider>::Release();
		core::Loading::Release();
		//core::ObjectPool<Ground>::Release();

		mLoadingScreen->Release();
		delete mLoadingScreen;
		CloseHandle(mHThread);
	}

	void SceneManager::LoadScene(ESceneType _type)
	{
		bool flag = false;
		mLoadSceneType = _type;
		switch (_type)
		{
		default:
			SetActivScene();
			flag = true;
			break;
		}
		if (flag == true)
			return;

		//로딩화면 띄우는건데 지금 문제 있어서 안하는중
		mLoadState = ELoadingState::FADE_OUT;
		//fade out 재생
		OpenLodingScreen();

		//loading 화면 재생
		//loading 끝나면 fade in 재생


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

	void SceneManager::RemoveObject(GameObject* _obj, ELayerType _type)
	{
		mActiveScene->RemoveGameObject(_obj, _type);
	}

	void SceneManager::RemoveObject(ELayerType _type)
	{
		mActiveScene->RemoveGameObject(_type);
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

	void SceneManager::SetActivScene()
	{
		yeram_client::Scene* cur = yeram_client::SceneManager::GetActiveScene();
		mActiveScene = mScenes[(UINT)mLoadSceneType];
		if (cur != nullptr)
			cur->OnExit();
		mActiveScene->OnEnter();
	}

	void SceneManager::ChageLayer(GameObject* _obj, ELayerType _add)
	{
		std::shared_ptr<GameObject> obj = mActiveScene->FindObject(_obj->GetName());
		RemoveObjectRequest(obj.get(),obj->GetLayerType());
		mActiveScene->AddGameObject(obj, _add);
	}

	

	void SceneManager::RemoveObjectRequestRelease()
	{
		while (mRemoveRequestObjs.empty() == false)
		{
			RemoveObjectInfo remove = mRemoveRequestObjs.front();
			mRemoveRequestObjs.pop();
			if (remove.mtype == ELayerType::NONE)
			{
				RemoveObject(remove.mobj);
			}
			else if (remove.mobj == nullptr)
			{
				RemoveObject(remove.mtype);
			}
			else
			{
				RemoveObject(remove.mobj, remove.mtype);
			}
			
		}
	}

	SceneManager::~SceneManager()
	{
		CloseHandle(mHThread);
	}

}
