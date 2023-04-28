#include "SaltBakerBossScene.h"
#include "GameObject.h"
#include "ObjectPool.h"
#include "Application.h"
#include "Layer.h"
#include "MoveObject.h"
#include "ZigZagBullet.h"
#include "SaltBaker.h"
#include "Ground.h"
#include "Player.h"
#include "Character.h"
#include "ColliderManager.h"


extern yeram_client::Application application;
namespace yeram_client
{
	SaltBakerBossScene::SaltBakerBossScene()
	{
		mCurType = ESceneType::SaltBakerBoss;
	}

	SaltBakerBossScene::SaltBakerBossScene(const std::wstring _name)
	{
		mCurType = ESceneType::SaltBakerBoss;
		SetName(_name);
	}

	SaltBakerBossScene::~SaltBakerBossScene()
	{
	}

	void SaltBakerBossScene::Initialize()
	{
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::BackColObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		mLayers[(UINT)ELayerType::Ground] = new Layer();
		mLayers[(UINT)ELayerType::Boss] = new Layer();
		mLayers[(UINT)ELayerType::Monster] = new Layer();
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::Bullet] = new Layer();
		Scene::Initialize();
	}

	void SaltBakerBossScene::Update()
	{
		Scene::Update();
	}

	void SaltBakerBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SaltBakerBossScene::Release()
	{
		Scene::Release();
	}

	void SaltBakerBossScene::OnEnter()
	{
		Scene::OnEnter();
		std::shared_ptr<GameObject> player_obj = FindObject(L"Player");
		if (player_obj == nullptr)
		{
			std::shared_ptr<GameObject> player_obj = core::ObjectPool<Player>::Spawn();
			player_obj->SetName(L"Player");
			Transform* tf = player_obj->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f,400.0f });


			std::shared_ptr<GameObject> player_reg = core::ObjectPool<Animator>::Spawn();
			player_reg->SetName(L"Reg");
			player_obj->AddChild(player_reg);
			std::shared_ptr<GameObject> player_head = core::ObjectPool<Animator>::Spawn();
			player_head->SetName(L"Head");
			player_obj->AddChild(player_head);

			std::shared_ptr<GameObject> player_shooter = core::ObjectPool<Animator>::Spawn();
			player_shooter->SetName(L"Shooter");
			player_obj->AddChild(player_shooter);

			Player* player = player_obj->GetComponent<Player>();
			player->CreateCharacter(EPlayerType::MsChalice);
			player->CreateCharacter(EPlayerType::Cuphead);
			player->ChangeCharacter(EPlayerType::MsChalice);
			player->GetActiveCharacter()->Initialize();

			Rigidbody* rigd = player_obj->GetComponent<Rigidbody>();
			rigd->Use_Gravity(true);
			rigd->SetGround(false);
			rigd->SetMass(1.0f);

			player_obj->SetActive(true);
			SceneManager::GetActiveScene()->AddGameObject(player_obj, ELayerType::Player);
		}
		else
		{
			player_obj->SetActive(true);
		}
	
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Bullet, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Player, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Boss, true);
		Phase1_Info_Register();
		Phase2_Info_Register();
		Phase3_Info_Register();
		
	}

	void SaltBakerBossScene::OnExit()
	{
		Scene::OnExit();
	}
	void SaltBakerBossScene::Phase1_Info_Register()
	{
		Vector2 pos = application.GetWindowSize();
		std::shared_ptr<GameObject> farbg = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			farbg->SetName(L"far_wall");
			SpriteRenderer* sprite = farbg->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_far_wall", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\08-sb_ph1_ph2_bg_far_wall.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = farbg->GetComponent<Transform>();
			tf->SetPos(Vector2{ pos.x / 3.0f,0.0f });
			AddGameObject(farbg, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg->SetName(L"bg_main");
			SpriteRenderer* sprite = bg->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_main", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\07-sb_ph1_ph2_bg_main_kitchen.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = bg->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,-220.0f });
			tf->SetSize(Vector2{ pos.x + 100.0f,pos.y / 2.0f + pos.y / 3.0f });
			AddGameObject(bg, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> side_table = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			side_table->SetName(L"bg_side_main");
			SpriteRenderer* sprite = side_table->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_sidemid_table", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\05-sb_ph1_ph2_mid_side_tables.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = side_table->GetComponent<Transform>();
			tf->SetPos(Vector2{ -70.0f,100.0f });
			tf->SetScale(Vector2{ 1.3f,1.0f });
			AddGameObject(side_table, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> cuphead = core::ObjectPool<Animator>::Spawn();
		{
			cuphead->SetName(L"gost_cuphead");
			Animator* ani = cuphead->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\6", Vector2::Zero, 0.01f);
			ani->Play(L"salt_baker_boss_intro_scene6", true);
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 170.0f,310.0f });
			tf->SetScale(Vector2{ 0.5f,0.5f });
			AddGameObject(cuphead, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> glass = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			glass->SetName(L"bg_glass");
			SpriteRenderer* sprite = glass->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_glass", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\05-sb_ph1_ph2_mid_side_tables_glass_top.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = glass->GetComponent<Transform>();
			tf->SetPos(Vector2{ 125.0f,235.0f });
			AddGameObject(glass, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> front_obj1 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			front_obj1->SetName(L"front_left_obj");
			SpriteRenderer* sprite = front_obj1->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_front_left_obj", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\03-sb_ph1_ph2_fg_objects_left.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = front_obj1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,pos.y / 2.0f + 250.0f });
			AddGameObject(front_obj1, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> front_obj2 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			front_obj2->SetName(L"front_right_obj");
			SpriteRenderer* sprite = front_obj2->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_front_right_obj", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\03-sb_ph1_ph2_fg_objects_right.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = front_obj2->GetComponent<Transform>();
			tf->SetPos(Vector2{ pos.x - 300.0f,pos.y / 2.0f + 220.0f });
			AddGameObject(front_obj2, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> mid = core::ObjectPool<Ground>::Spawn();
		{
			mid->SetName(L"bg_main");
			SpriteRenderer* sprite = mid->AddComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_mid_table", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\04-sb_ph1_ph2_mid_table.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = mid->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,500.0f });
			tf->SetScale(Vector2{ 1.3f,1.3f });
			Vector2 scale = tf->GetScale();
			Collider* col = mid->GetComponent<Collider>();
			col->SetCenter(Vector2{ 0.0f, +(sprite->GetHeight())/2.0f });
			col->SetSize(Vector2{ sprite->GetWidth()*scale.x,sprite->GetHeight()*scale.y /2.0f});
		}
		std::shared_ptr<GameObject> saltbaker = core::ObjectPool<SaltBaker>::Spawn();
		saltbaker->SetName(L"saltbaker");
		SaltBaker* sb = saltbaker->GetComponent<SaltBaker>();
		AddGameObject(saltbaker, ELayerType::Boss);

		AddGameObject(mid, ELayerType::Ground);
		std::shared_ptr<GameObject> arm = sb->GetParts(SaltBaker::EParts::ARM);
		std::shared_ptr<GameObject> sugar = sb->GetParts(SaltBaker::EParts::ACC);
		AddGameObject(sugar, ELayerType::Monster);
		AddGameObject(arm, ELayerType::Monster);
	}
	void SaltBakerBossScene::Phase2_Info_Register()
	{
	}
	void SaltBakerBossScene::Phase3_Info_Register()
	{
	}
	void SaltBakerBossScene::Phase1_Run()
	{
	}
	void SaltBakerBossScene::Phase2_Run()
	{
	}
	void SaltBakerBossScene::Phase3_Run()
	{
	}
}
