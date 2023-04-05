#include "DevilScene.h"
#include "Layer.h"
#include "Player.h"
#include "Ground.h"
#include "Character.h"
#include "ObjectPool.h"
#include "ColliderManager.h"
#include "Application.h"
extern yeram_client::Application application;
namespace yeram_client
{
	DevilScene::DevilScene()
	{
		mCurType = ESceneType::BossDevil;
	}
	DevilScene::DevilScene(std::wstring _name)
	{
		mCurType = ESceneType::BossDevil;
		SetName(_name);
	}
	DevilScene::~DevilScene()
	{
	}
	void DevilScene::Initialize()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::Monster] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		mLayers[(UINT)ELayerType::Bullet] = new Layer();
		
	}
	void DevilScene::Update()
	{
		Scene::Update();
	}
	void DevilScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void DevilScene::Release()
	{
		Scene::Release();
	}
	void DevilScene::OnEnter()
	{
		Vector2 size = application.GetWindowSize();
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::FrontObject, true);
		for (auto obj : GetGameObjects(ELayerType::Player))
		{
			GameObject* owner = obj.get();
			Player* player = owner->GetComponent<Player>();
			player->SetActive(true);
			Transform* tf = owner->GetComponent<Transform>();
			tf->SetPos(Vector2{ 200.0f,300.0f });

			Character* active_ch = player->GetActiveCharacter();
			active_ch->SetAirMode(false);
			active_ch->Initialize();

			Rigidbody* rid = owner->GetComponent<Rigidbody>();
			rid->Use_Gravity(true);
			rid->SetGround(false);
			rid->SetMass(1.0f);
		}
		
		std::shared_ptr<GameObject> obj = core::ObjectPool<Ground>::Spawn();
		Collider* col = obj->GetComponent<Collider>();
		Transform* tf = obj->GetComponent<Transform>();
		tf->SetPos(Vector2{800.0f,900.0f});
		col->SetCenter(Vector2{ -800.0f, -100.0f });
		col->SetSize(Vector2{ 1600.0f,100.0f });
		AddGameObject(obj, ELayerType::FrontObject);
   
		/*std::shared_ptr<GameObject> obj = core::ObjectPool<SpriteRenderer>::Spawn();
		Transform* tf = obj->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x,(long)size.y });
		SpriteRenderer* sprite = obj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"DevilBackground1", L"..\\Resources\\Devil\\devil_bg_volcanos.bmp");
		
		sprite->SetRenderType(ERenderType::StretchBlt);
		obj->SetName(L"DevilBackground1");

		AddGameObject(obj, ELayerType::BackObject);

		obj = core::ObjectPool<SpriteRenderer>::Spawn();
		tf = obj->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x,(long)size.y+100l });
		sprite = obj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"DevilBackground2", L"..\\Resources\\Devil\\devil_bg_ph_1_pillars.bmp");

		sprite->SetRenderType(ERenderType::TransParentBlt);
		obj->SetName(L"DevilBackground2");
		AddGameObject(obj, ELayerType::BackObject);

		obj = core::ObjectPool<SpriteRenderer>::Spawn();
		tf = obj->GetComponent<Transform>();
		tf->SetPos(Vector2{ -500.0f,0.0f });
		tf->SetSize(Vector2{ (long)size.x+1000l,(long)size.y});
		sprite = obj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"DevilBackground3", L"..\\Resources\\Devil\\devil_bg_ph_1_foreground.bmp");

		sprite->SetRenderType(ERenderType::TransParentBlt);
		obj->SetName(L"DevilBackground3");
		AddGameObject(obj, ELayerType::FrontObject);

		obj = core::ObjectPool<SpriteRenderer>::Spawn();
		tf = obj->GetComponent<Transform>();
		Vector2& pos = tf->GetPos();
		pos.x+=560.0f;
		pos.y += 70.0f;
		sprite = obj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"DevilChair", L"..\\Resources\\Devil\\devil_bg_ph_1_chair_big.bmp");

		sprite->SetRenderType(ERenderType::TransParentBlt);
		obj->SetName(L"DevilChair");
		AddGameObject(obj, ELayerType::BackObject);


		obj = core::ObjectPool<SpriteRenderer>::Spawn();
		tf = obj->GetComponent<Transform>();
		Vector2& pos2 = tf->GetPos();
		pos2.x += 560.0f;
		pos2.y += 70.0f;
		sprite = obj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"DevilBoss", L"..\\Resources\\Devil\\Idle\\devil_idle_0024.bmp");

		sprite->SetRenderType(ERenderType::TransParentBlt);
		obj->SetName(L"DevilBoss");
		AddGameObject(obj, ELayerType::BackObject);*/
		//Camera::PlayLoad();
		Scene::OnEnter();
	}
	void DevilScene::OnExit()
	{
		Scene::OnExit();
	}
}

