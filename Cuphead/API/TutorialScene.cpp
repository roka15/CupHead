#include "TutorialScene.h"
#include "Layer.h"
#include "Player.h"
#include "Ground.h"
#include "ParryingObject.h"
#include "Character.h"
#include "ObjectPool.h"
#include "ColliderManager.h"
#include "Application.h"
#include "Camera.h"
extern yeram_client::Application application;
namespace yeram_client
{
	TutorialScene::TutorialScene()
	{
		mCurType = ESceneType::BossDevil;
	}
	TutorialScene::TutorialScene(std::wstring _name)
	{
		mCurType = ESceneType::BossDevil;
		SetName(_name);
	}
	TutorialScene::~TutorialScene()
	{
	}
	void TutorialScene::Initialize()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::Monster] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		mLayers[(UINT)ELayerType::Bullet] = new Layer();
		mLayers[(UINT)ELayerType::BackColObject] = new Layer();
	}
	void TutorialScene::Update()
	{
		
		Scene::Update();
		
		Transform* tf = mPlayer->GetComponent<Transform>();
		const Vector2& pos = tf->GetPos();
		
		
		mFirstUpdate = true;
	}
	void TutorialScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TutorialScene::Release()
	{
		Scene::Release();
	}
	void TutorialScene::OnEnter()
	{
		mFirstUpdate = false;
		Vector2 size = application.GetWindowSize();

		Camera::SetHorizontalMove(false);
		Camera::SetVerticalMove(false);
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::FrontObject, true);
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::BackColObject,true);

		mStartPos = Vector2{ 200.0f,300.0f };
		for (auto obj : GetGameObjects(ELayerType::Player))
		{
			GameObject* owner = obj.get();
			mPlayer = owner;
			Player* player = owner->GetComponent<Player>();
			player->ChangeCharacter(EPlayerType::MsChalice);
			player->SetActive(true);
			Transform* tf = owner->GetComponent<Transform>();
		
			tf->SetPos(mStartPos);
			
			Character* active_ch = player->GetActiveCharacter();
			active_ch->SetAirMode(false);
			active_ch->Initialize();

			Rigidbody* rid = owner->GetComponent<Rigidbody>();
			rid->Use_Gravity(true);
			rid->SetGround(false);
			rid->SetMass(1.0f);
			//Camera::SetTarget(owner);
		}
		
		std::shared_ptr<GameObject> obj = core::ObjectPool<Ground>::Spawn();
		Collider* col = obj->GetComponent<Collider>();
		Transform* tf = obj->GetComponent<Transform>();
		tf->SetPos(Vector2{400.0f,900.0f});
		col->SetCenter(Vector2{ -800.0f, -100.0f });
		col->SetSize(Vector2{ 2100.0f,100.0f });
		AddGameObject(obj, ELayerType::FrontObject);
   
	/*	std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
		{
			background->SetName(L"tutorial_background");
			Transform* tf = background->GetComponent<Transform>();
			tf->SetPos(Vector2{ 650.0f,size.y - 50 });
			Vector2& scale = tf->GetScale();
			scale.x *= 1.28f;
			scale.y *= 1.2f;
			Animator* ani = background->AddComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\TutorialScene\\Loop", Vector2::Zero, 0.04f);
			ani->Play(L"TutorialSceneLoop", true);

			mMapLimit = ani->GetSpriteSize();
			mMapLimit = mMapLimit / 2.0f;
		
			AddGameObject(background, ELayerType::BackObject);
		}*/
		std::shared_ptr<GameObject> parry = std::make_shared<GameObject>();
		{
			parry->SetName(L"ParryObject");
			ParryingObject* po = parry->AddComponent<ParryingObject>();
			Transform* tf = parry->GetComponent<Transform>();
			tf->SetPos(Vector2{ 700.0f,800.0f });
			Animator* ani = parry->AddComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\TutorialScene\\Wheat\\C",Vector2::Zero,0.04f);
			ani->Play(L"WheatC",true);
			const Vector2& image_size =ani->GetSpriteSize();
			Collider* col = parry->AddComponent<Collider>();
			col->SetCenter(Vector2{ -(image_size.x/2.0f),-(image_size.y)});
			col->SetSize(image_size);
			AddGameObject(parry, ELayerType::BackColObject);
		}

		Scene::OnEnter();
	}
	void TutorialScene::OnExit()
	{
		Scene::OnExit();
	}
}

