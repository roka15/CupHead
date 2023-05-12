#include "SaltBakerBossScene.h"
#include "GameObject.h"
#include "ObjectPool.h"
#include "Application.h"
#include "Layer.h"
#include "MoveObject.h"
#include "ZigZagBullet.h"
#include "Ground.h"
#include "Player.h"
#include "Character.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "Time.h"
#include "SaltBaker.h"
#include "CookieBullet.h"
#include "SugarBullet.h"
#include "BerryBullet.h"
#include "LemonBullet.h"
#include "MintBullet.h"
#include "PepperBullet.h"
#include "Pepper.h"
#include "SlatPhase3.h"
#include "ResourceDeleterThread.h"

extern yeram_client::Application application;
namespace yeram_client
{
	SaltBakerBossScene::SaltBakerBossScene() :mPhase2SceneMoveSpeed(1100.0f)
	{
		mCurType = ESceneType::SaltBakerBoss;
	}

	SaltBakerBossScene::SaltBakerBossScene(const std::wstring _name) : mPhase2SceneMoveSpeed(1100.0f)
	{
		mCurType = ESceneType::SaltBakerBoss;
		SetName(_name);
	}

	SaltBakerBossScene::~SaltBakerBossScene()
	{
	}

	void SaltBakerBossScene::Initialize()
	{
		mPhase3CloseTime = 0.0;
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::BackColObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		mLayers[(UINT)ELayerType::Ground] = new Layer();
		mLayers[(UINT)ELayerType::Boss] = new Layer();
		mLayers[(UINT)ELayerType::Monster] = new Layer();
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::PlayerBullet] = new Layer();
		mLayers[(UINT)ELayerType::Bullet] = new Layer();
		mLayers[(UINT)ELayerType::MiddleObject] = new Layer();
		Scene::Initialize();
		mbTranslateFlag = false;
	}

	void SaltBakerBossScene::Update()
	{
		SaltBaker* salt = mBoss->GetComponent<SaltBaker>();
		mTime += Time::DeltaTime();
		EPhaseType phase = salt->GetPhase();
		if (salt->ChagePhase() == false)
		{
			if (phase == EPhaseType::PHASE3)
			{
				if (Camera::GetAlpha() == 1.0f)
				{
					if (mPhase3CloseTime == 0.0)
					{
						mPhase3CloseTime = mTime;
						Phase3_2Run();
					}
					else if (mTime - mPhase3CloseTime >= 10.0f)
					{
						salt->SetPhase3Intro();
						Camera::FadeIn();
					}
				}
			}
			Scene::Update();
			return;
		}
		switch (phase)
		{
		case EPhaseType::PHASE1:
			if (mbPhase1_Flag == false)
			{
				mbPhase1_Flag = true;
				Phase1_Run();
				salt->OffChagePhase();
			}
			break;
		case EPhaseType::PHASE2:
			if (mbPhase2_Flag == false)
			{
				mbPhase2_Flag = true;
				Phase2_Run();
				salt->OffChagePhase();
			}
			break;
		case EPhaseType::PHASE3:

			if (mbPhase3_Flag == false)
			{
				mbPhase3_Flag = true;
				Phase3_Run();
				salt->OffChagePhase();
			}
			break;
		}
		Scene::Update();
	}

	void SaltBakerBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SaltBakerBossScene::Release()
	{
		if (mBgObjects.size() != 0)
		{
			for (auto& map : mBgObjects)
			{
				if (map.second.size() != 0)
				{
					for (auto& vec : map.second)
					{
						vec.reset();
					}
				}
				map.second.clear();
			}
			mBgObjects.clear();
		}
		if (core::ObjectPool<SlatPhase3>::ActiveObjectPool() == true)
			core::ObjectPool<SlatPhase3>::Release();
		if (core::ObjectPool<PepperBullet>::ActiveObjectPool() == true)
			core::ObjectPool<PepperBullet>::Release();
		if (core::ObjectPool<Pepper>::ActiveObjectPool() == true)
			core::ObjectPool<Pepper>::Release();
		if (core::ObjectPool<MintBullet>::ActiveObjectPool() == true)
			core::ObjectPool<MintBullet>::Release();
		if (core::ObjectPool<LemonBullet>::ActiveObjectPool() == true)
			core::ObjectPool<LemonBullet>::Release();
		if (core::ObjectPool<BerryBullet>::ActiveObjectPool() == true)
			core::ObjectPool<BerryBullet>::Release();
		if (core::ObjectPool<SugarBullet>::ActiveObjectPool() == true)
			core::ObjectPool<SugarBullet>::Release();
		if (core::ObjectPool<CookieBullet>::ActiveObjectPool() == true)
			core::ObjectPool<CookieBullet>::Release();
		if (core::ObjectPool<SaltBaker>::ActiveObjectPool() == true)
			core::ObjectPool<SaltBaker>::Release();
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
			mPlayer = player_obj;
			SceneManager::GetActiveScene()->AddGameObject(player_obj, ELayerType::Player);
		}
		else
		{
			Player* player = player_obj->GetComponent<Player>();
			player->ChangeCharacter(EPlayerType::MsChalice);
			Transform* tf = player_obj->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f,400.0f });
			player_obj->SetActive(true);
		}

		ColliderManager::SetLayer(ELayerType::PlayerBullet, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::PlayerBullet, ELayerType::Bullet, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Player, true);
		ColliderManager::SetLayer(ELayerType::PlayerBullet, ELayerType::Boss, true);
		ColliderManager::SetLayer(ELayerType::PlayerBullet, ELayerType::Monster, true);
		ColliderManager::SetLayer(ELayerType::Monster, ELayerType::Boss, true);

		mBgObjects.insert(std::make_pair(EPhaseType::PHASE1, std::vector<std::shared_ptr<GameObject>>()));
		mBgObjects.insert(std::make_pair(EPhaseType::PHASE2, std::vector<std::shared_ptr<GameObject>>()));
		mBgObjects.insert(std::make_pair(EPhaseType::PHASE3, std::vector<std::shared_ptr<GameObject>>()));

		Phase1_Info_Register();


		//test
		{
			//Phase1_Run();
		 //Phase2_Run();
			//Phase3_Run();
		}
	}

	void SaltBakerBossScene::OnExit()
	{
		Scene::OnExit();
		mPlayer.reset();
		mBoss.reset();
		for (auto& map_itr : mBgObjects)
		{
			for (auto& vec_itr : map_itr.second)
			{
				vec_itr.reset();
			}
		}
		if (core::ObjectPool<SlatPhase3>::ActiveObjectPool() == true)
			core::ObjectPool<SlatPhase3>::Release();
		if (core::ObjectPool<PepperBullet>::ActiveObjectPool() == true)
		core::ObjectPool<PepperBullet>::Release();
		if (core::ObjectPool<Pepper>::ActiveObjectPool() == true)
		core::ObjectPool<Pepper>::Release();
		if (core::ObjectPool<MintBullet>::ActiveObjectPool() == true)
		core::ObjectPool<MintBullet>::Release();
		if (core::ObjectPool<LemonBullet>::ActiveObjectPool() == true)
		core::ObjectPool<LemonBullet>::Release();
		if (core::ObjectPool<BerryBullet>::ActiveObjectPool() == true)
		core::ObjectPool<BerryBullet>::Release();
		if (core::ObjectPool<SugarBullet>::ActiveObjectPool() == true)
		core::ObjectPool<SugarBullet>::Release();
		if (core::ObjectPool<CookieBullet>::ActiveObjectPool() == true)
		core::ObjectPool<CookieBullet>::Release();
		if (core::ObjectPool<SaltBaker>::ActiveObjectPool() == true)
		core::ObjectPool<SaltBaker>::Release();
	}
	void SaltBakerBossScene::Phase1_Info_Register()
	{
		if (core::ObjectPool<SaltBaker>::ActiveObjectPool() == false)
			core::ObjectPool<SaltBaker>::Initialize(1);
		if (core::ObjectPool<CookieBullet>::ActiveObjectPool() == false)
			core::ObjectPool<CookieBullet>::Initialize(50, 100);
		if (core::ObjectPool<SugarBullet>::ActiveObjectPool() == false)
			core::ObjectPool<SugarBullet>::Initialize(50, 100);
		if (core::ObjectPool<BerryBullet>::ActiveObjectPool() == false)
			core::ObjectPool<BerryBullet>::Initialize(50, 100);
		if (core::ObjectPool<LemonBullet>::ActiveObjectPool() == false)
			core::ObjectPool<LemonBullet>::Initialize(50, 100);
		Vector2 pos = application.GetWindowSize();
		std::shared_ptr<GameObject> farbg = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			farbg->SetActive(false);
			farbg->SetName(L"far_wall");
			SpriteRenderer* sprite = farbg->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_far_wall", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\08-sb_ph1_ph2_bg_far_wall.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = farbg->GetComponent<Transform>();
			tf->SetPos(Vector2{ pos.x / 3.0f,0.0f });

			MoveObject* mv = farbg->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);

			mBgObjects[EPhaseType::PHASE1].push_back(farbg);
			AddGameObject(farbg, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg->SetActive(false);
			bg->SetName(L"bg_main");
			SpriteRenderer* sprite = bg->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_main", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\07-sb_ph1_ph2_bg_main_kitchen.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = bg->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,-220.0f });
			tf->SetSize(Vector2{ pos.x + 100.0f,pos.y / 2.0f + pos.y / 3.0f });

			MoveObject* mv = bg->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);

			mBgObjects[EPhaseType::PHASE1].push_back(bg);
			AddGameObject(bg, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> side_table = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			side_table->SetActive(false);
			side_table->SetName(L"bg_side_main");
			SpriteRenderer* sprite = side_table->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_sidemid_table", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\05-sb_ph1_ph2_mid_side_tables.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = side_table->GetComponent<Transform>();
			tf->SetPos(Vector2{ -70.0f,100.0f });
			tf->SetScale(Vector2{ 1.3f,1.0f });

			MoveObject* mv = side_table->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);
			mBgObjects[EPhaseType::PHASE1].push_back(side_table);
			AddGameObject(side_table, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> cuphead = core::ObjectPool<Animator>::Spawn();
		{
			cuphead->SetActive(false);
			cuphead->SetName(L"gost_cuphead");
			Animator* ani = cuphead->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\6", Vector2::Zero, 0.01f);
			ani->Play(L"salt_baker_boss_intro_scene6", true);
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 170.0f,310.0f });
			tf->SetScale(Vector2{ 0.5f,0.5f });

			MoveObject* mv = cuphead->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);
			mBgObjects[EPhaseType::PHASE1].push_back(cuphead);
			AddGameObject(cuphead, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> glass = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			glass->SetActive(false);
			glass->SetName(L"bg_glass");
			SpriteRenderer* sprite = glass->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_glass", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\05-sb_ph1_ph2_mid_side_tables_glass_top.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = glass->GetComponent<Transform>();
			tf->SetPos(Vector2{ 125.0f,235.0f });
			MoveObject* mv = glass->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);
			mBgObjects[EPhaseType::PHASE1].push_back(glass);
			AddGameObject(glass, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> front_obj1 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			front_obj1->SetActive(false);
			front_obj1->SetName(L"front_left_obj");
			SpriteRenderer* sprite = front_obj1->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_front_left_obj", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\03-sb_ph1_ph2_fg_objects_left.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = front_obj1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,pos.y / 2.0f + 250.0f });
			MoveObject* mv = front_obj1->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);
			mBgObjects[EPhaseType::PHASE1].push_back(front_obj1);
			AddGameObject(front_obj1, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> front_obj2 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			front_obj2->SetActive(false);
			front_obj2->SetName(L"front_right_obj");
			SpriteRenderer* sprite = front_obj2->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_front_right_obj", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\03-sb_ph1_ph2_fg_objects_right.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = front_obj2->GetComponent<Transform>();
			tf->SetPos(Vector2{ pos.x - 300.0f,pos.y / 2.0f + 220.0f });
			MoveObject* mv = front_obj2->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);
			mBgObjects[EPhaseType::PHASE1].push_back(front_obj2);
			AddGameObject(front_obj2, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> mid = core::ObjectPool<Ground>::Spawn();
		{
			mid->SetActive(false);
			mid->SetName(L"bg_main");
			SpriteRenderer* sprite = mid->AddComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_ph1_ph2_bg_mid_table", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\bg\\04-sb_ph1_ph2_mid_table.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = mid->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,500.0f });
			tf->SetScale(Vector2{ 1.3f,1.3f });
			Vector2 scale = tf->GetScale();
			Collider* col = mid->GetComponent<Collider>();
			col->SetCenter(Vector2{ 0.0f, +(sprite->GetHeight()) / 2.0f });
			col->SetSize(Vector2{ sprite->GetWidth() * scale.x,sprite->GetHeight() * scale.y / 2.0f });
			MoveObject* mv = mid->AddComponent<MoveObject>();
			mv->SetActive(false);
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,pos.y * 2.0f }, true, true);
			mBgObjects[EPhaseType::PHASE1].push_back(mid);
		}
		std::shared_ptr<GameObject> saltbaker = core::ObjectPool<SaltBaker>::Spawn();
		saltbaker->SetName(L"saltbaker");
		SaltBaker* sb = saltbaker->GetComponent<SaltBaker>();
		mBoss = saltbaker;
		AddGameObject(saltbaker, ELayerType::Boss);

		AddGameObject(mid, ELayerType::Ground);
		std::shared_ptr<GameObject> arm = sb->GetParts(SaltBaker::EParts::ARM);
		std::shared_ptr<GameObject> sugar = sb->GetParts(SaltBaker::EParts::ACC);
		std::shared_ptr<GameObject> arm2 = sb->GetParts(SaltBaker::EParts::ARM2);
		AddGameObject(arm2, ELayerType::Boss);
		AddGameObject(sugar, ELayerType::Monster);
		AddGameObject(arm, ELayerType::Monster);

	}
	void SaltBakerBossScene::Phase2_Info_Register()
	{
		core::ResourceDeleterThread::SetResourceQueueCapacity(0);
		core::ResourceDeleterThread::SetResourceQueueCapacity(3000);
		if (core::ObjectPool<MintBullet>::ActiveObjectPool() == false)
			core::ObjectPool<MintBullet>::Initialize(50, 100);
		if (core::ObjectPool<PepperBullet>::ActiveObjectPool() == false)
			core::ObjectPool<PepperBullet>::Initialize(50, 100);
		if (core::ObjectPool<Pepper>::ActiveObjectPool() == false)
			core::ObjectPool<Pepper>::Initialize(10, 100);

		Vector2 winsize = application.GetWindowSize();
		Vector2 nextpos = Vector2{ 0.0f,-(winsize.y) };
		std::shared_ptr<GameObject> bg1 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg1->SetActive(false);
			bg1->SetName(L"ph1_ph2_tlbg1");
			Transform* tf = bg1->GetComponent<Transform>();
			tf->SetSize(winsize);
			tf->SetPos(nextpos);
			MoveObject* mv = bg1->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,winsize.y * 2.0f }, true, true);
			mv->SetArriveEvent(std::bind([mv, this]()->void
				{
					GameObject* owner = mv->GetOwner();
					SceneManager::RemoveObjectRequest(owner);
					RemovePhaseObject(EPhaseType::PHASE1);
				}));
			SpriteRenderer* sprite = bg1->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg1", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\11-sb_ph1_ph2_bg_main_transition_area_low.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg1);
			AddGameObject(bg1, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> front = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			front->SetActive(false);
			front->SetName(L"ph1_ph2_tlfront");
			Transform* tf = front->GetComponent<Transform>();
			tf->SetSize(Vector2{ winsize.x,winsize.y * 2.0f });
			tf->SetPos(Vector2{ nextpos.x,nextpos.y * 2.0f });
			MoveObject* mv = front->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,winsize.y * 2.0f }, true, true);
			mv->SetArriveEvent(std::bind([]()->void
				{
				}));
			SpriteRenderer* sprite = front->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlfront", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\02-sb_ph1_ph2_fg_transition_area_pipes.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(front);
			AddGameObject(front, ELayerType::FrontObject);
		}
		nextpos.y -= winsize.y;
		std::shared_ptr<GameObject> bg2 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg2->SetActive(false);
			bg2->SetName(L"ph1_ph2_tlbg2");
			Transform* tf = bg2->GetComponent<Transform>();
			tf->SetSize(winsize);
			tf->SetPos(nextpos);
			MoveObject* mv = bg2->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,winsize.y * 2.0f }, true, true);
			mv->SetArriveEvent(std::bind([mv]()->void
				{
					GameObject* owner = mv->GetOwner();
					SceneManager::RemoveObjectRequest(owner);
				}));
			SpriteRenderer* sprite = bg2->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg2", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\10-sb_ph1_ph2_bg_main_transition_area_mid.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg2);
			AddGameObject(bg2, ELayerType::BackObject);
		}
		nextpos.y -= winsize.y;
		std::shared_ptr<GameObject> bg3 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg3->SetActive(false);
			bg3->SetName(L"ph1_ph2_tlbg3");
			Transform* tf = bg3->GetComponent<Transform>();
			tf->SetSize(winsize);
			tf->SetPos(nextpos);
			MoveObject* mv = bg3->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,winsize.y - (winsize.y / 5.0f) - 100.0f });
			mv->SetArriveEvent(std::bind([]()->void
				{
				}));
			SpriteRenderer* sprite = bg3->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg3", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\09-sb_ph1_ph2_bg_main_transition_area_high.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg3);
		}
		nextpos.y -= winsize.y;
		nextpos.y += 100.0f;
		//4~7 은 동일한 pos 줘야함.
		std::shared_ptr<GameObject> bg4 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg4->SetActive(false);
			bg4->SetName(L"ph1_ph2_tlbg4");
			Transform* tf = bg4->GetComponent<Transform>();
			tf->SetSize(winsize);
			tf->SetPos(nextpos);
			MoveObject* mv = bg4->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,-100.0f });
			mv->SetArriveEvent(std::bind([]()->void
				{
				}));
			SpriteRenderer* sprite = bg4->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg4", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\15-sb_ph1_ph2_bg_far_shadow_sky.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg4);
			AddGameObject(bg4, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg5 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg5->SetActive(false);
			bg5->SetName(L"ph1_ph2_tlbg5");
			Transform* tf = bg5->GetComponent<Transform>();
			tf->SetSize(winsize / 2);
			tf->SetPos(Vector2{ winsize.x / 2,nextpos.y });
			MoveObject* mv = bg5->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,-100.0f });
			mv->SetArriveEvent(std::bind([]()->void
				{
				}));
			SpriteRenderer* sprite = bg5->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg5", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\14-sb_ph1_ph2_bg_upper_debris.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg5);
			AddGameObject(bg5, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg6 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg6->SetActive(false);
			bg6->SetName(L"ph1_ph2_tlbg6");
			Transform* tf = bg6->GetComponent<Transform>();
			tf->SetSize(Vector2{ winsize.x + 100.0f,winsize.y });
			tf->SetPos(Vector2{ -100.0f,nextpos.y + (winsize.y / 2.0f) - 150.0f });
			MoveObject* mv = bg6->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,(winsize.y / 2.0f) - 200.0f });
			mv->SetArriveEvent(std::bind([]()->void
				{
				}));
			SpriteRenderer* sprite = bg6->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg6", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\12-sb_ph1_ph2_bg_upper_shadow.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg6);
			AddGameObject(bg6, ELayerType::BackObject);
		}
		AddGameObject(bg3, ELayerType::BackObject);
		std::shared_ptr<GameObject> bg7 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg7->SetActive(false);
			bg7->SetName(L"ph1_ph2_tlbg7");
			Transform* tf = bg7->GetComponent<Transform>();
			tf->SetSize(winsize);
			tf->SetPos(nextpos);
			MoveObject* mv = bg7->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,-100.0f });
			mv->SetArriveEvent(std::bind([]()->void
				{
				}));
			SpriteRenderer* sprite = bg7->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg7", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\13-sb_ph1_ph2_bg_upper_main.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg7);
			AddGameObject(bg7, ELayerType::BackObject);
		}
	}
	void SaltBakerBossScene::Phase3_Info_Register()
	{
		if (core::ObjectPool<SlatPhase3>::ActiveObjectPool() == false)
			core::ObjectPool<SlatPhase3>::Initialize(1, 1);
		Vector2 winsize = application.GetWindowSize();
		Vector2 center = Vector2{ winsize.x / 2.0f,winsize.y };

		int translate_obj_cnt = 0;
#pragma region translate
#pragma region mid hand
		translate_obj_cnt++;
		std::shared_ptr<GameObject> hand_mid_rock = core::ObjectPool<Animator>::Spawn();
		{
			hand_mid_rock->SetActive(false);
			hand_mid_rock->SetName(L"hand_mid_rocktype3");
			Transform* tf = hand_mid_rock->GetComponent<Transform>();
			tf->SetPos(Vector2{ 700.0f,0.0f });
			Animator* ani = hand_mid_rock->GetComponent<Animator>();
			//ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathHand\\Type3", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathHandType3", false);
			/*	ani->GetCompleteEvent(L"translate_p2_p3DeathHandType3") = std::bind([this,ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> nextrock = SceneManager::FindObject(L"hand_mid_rocktype2");
					Animator* next_ani = nextrock->GetComponent<Animator>();
					next_ani->Play(L"translate_p2_p3DeathHandType2", false);
					next_ani->SetActive(true);
					nextrock->GetComponent<MoveObject>()->SetActive(true);
				});*/
			MoveObject* mv = hand_mid_rock->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,750.0f }, false, false);
			//mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(hand_mid_rock);
			AddGameObject(hand_mid_rock, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> hand_mid_rock2 = core::ObjectPool<Animator>::Spawn();
		{
			hand_mid_rock2->SetActive(false);
			hand_mid_rock2->SetName(L"hand_mid_rocktype2");
			Transform* tf = hand_mid_rock2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1500.0f,-10.0f });
			Animator* ani = hand_mid_rock2->GetComponent<Animator>();
			ani->SetActive(true);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathHand\\Type2", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathHandType2", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathHandType2") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> nextrock = SceneManager::FindObject(L"hand_mid_rocktype1");
					Animator* ani = nextrock->GetComponent<Animator>();
					ani->Play(L"translate_p2_p3DeathHandType1", false);
					ani->SetActive(true);
					nextrock->GetComponent<MoveObject>()->SetActive(true);
				});
			MoveObject* mv = hand_mid_rock2->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,800.0f }, false, false);
			mv->SetActive(true);
			mBgObjects[EPhaseType::PHASE3].push_back(hand_mid_rock2);
			AddGameObject(hand_mid_rock2, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> hand_mid_rock3 = core::ObjectPool<Animator>::Spawn();
		{
			hand_mid_rock3->SetActive(false);
			hand_mid_rock3->SetName(L"hand_mid_rocktype1");
			Transform* tf = hand_mid_rock3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1400.0f,0.0f });
			Animator* ani = hand_mid_rock3->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathHand\\Type1", Vector2::Zero, 0.05f);
			ani->GetCompleteEvent(L"translate_p2_p3DeathHandType1") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> nextrock = SceneManager::FindObject(L"hand_mid_rocktype5");
					Animator* ani = nextrock->GetComponent<Animator>();
					ani->Play(L"translate_p2_p3DeathHandType5", false);
					ani->SetActive(true);
					nextrock->GetComponent<MoveObject>()->SetActive(true);
				});
			MoveObject* mv = hand_mid_rock3->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,750.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(hand_mid_rock3);
			AddGameObject(hand_mid_rock3, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> hand_mid_rock4 = core::ObjectPool<Animator>::Spawn();
		{
			hand_mid_rock4->SetActive(false);
			hand_mid_rock4->SetName(L"hand_mid_rocktype5");
			Transform* tf = hand_mid_rock4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 800.0f,0.0f });
			Animator* ani = hand_mid_rock4->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathHand\\Type5", Vector2::Zero, 0.05f);
			ani->GetCompleteEvent(L"translate_p2_p3DeathHandType5") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> nextmid = SceneManager::FindObject(L"p2deathmid_type1");
					nextmid->GetComponent<Animator>()->SetActive(true);
					nextmid->GetComponent<MoveObject>()->SetActive(true);

					std::shared_ptr<GameObject> nextrock = SceneManager::FindObject(L"hand_mid_rocktype6");
					Animator* ani = nextrock->GetComponent<Animator>();
					ani->Play(L"translate_p2_p3DeathHandType6", false);
					ani->SetActive(true);
					nextrock->GetComponent<MoveObject>()->SetActive(true);
				});
			MoveObject* mv = hand_mid_rock4->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,750.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(hand_mid_rock4);
			AddGameObject(hand_mid_rock4, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> hand_mid_rock5 = core::ObjectPool<Animator>::Spawn();
		{
			hand_mid_rock5->SetActive(false);
			hand_mid_rock5->SetName(L"hand_mid_rocktype6");
			Transform* tf = hand_mid_rock5->GetComponent<Transform>();
			tf->SetPos(Vector2{ 600.0f,0.0f });
			Animator* ani = hand_mid_rock5->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathHand\\Type6", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathHandType6", false);
			MoveObject* mv = hand_mid_rock5->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,900.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(hand_mid_rock5);
			AddGameObject(hand_mid_rock5, ELayerType::FrontObject);
		}

#pragma endregion
#pragma region mid 
		translate_obj_cnt++;
		std::shared_ptr<GameObject> mid = core::ObjectPool<Animator>::Spawn();
		{
			mid->SetActive(false);
			mid->SetName(L"p2deathmid_type1");
			Transform* tf = mid->GetComponent<Transform>();
			tf->SetPos(Vector2{ 800.0f,0.0f });
			Animator* ani = mid->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3Deathmid\\Type1", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathmidType1", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathmidType1") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathmid_type2");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);

					std::shared_ptr<GameObject> next2 = SceneManager::FindObject(L"p2deathmid_type4intro");
					next_ani = next2->GetComponent<Animator>();
					next_ani->SetActive(true);
					next2->GetComponent<MoveObject>()->SetActive(true);
				});
			MoveObject* mv = mid->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,1500.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(mid);
			AddGameObject(mid, ELayerType::MiddleObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> mid2 = core::ObjectPool<Animator>::Spawn();
		{
			mid2->SetActive(false);
			mid2->SetName(L"p2deathmid_type2");
			Transform* tf = mid2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 800.0f,0.0f });
			Animator* ani = mid2->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3Deathmid\\Type2", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathmidType2", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathmidType2") = std::bind([this, ani]()->void
				{
					/*if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> nextrock = SceneManager::FindObject(L"hand_mid_rocktype1");
					Animator* ani = nextrock->GetComponent<Animator>();
					ani->Play(L"translate_p2_p3DeathHandType1", false);
					ani->SetActive(true);
					nextrock->GetComponent<MoveObject>()->SetActive(true);*/
				});
			MoveObject* mv = mid2->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,1500.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(mid2);
			AddGameObject(mid2, ELayerType::MiddleObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> mid3 = core::ObjectPool<Animator>::Spawn();
		{
			mid3->SetActive(false);
			mid3->SetName(L"p2deathmid_type4intro");
			Transform* tf = mid3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 700.0f,0.0f });
			Animator* ani = mid3->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3Deathmid\\Type4intro", Vector2::Zero, 0.05f);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3Deathmid\\Type4idle", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathmidType4intro", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathmidType4intro") = std::bind([this, ani]()->void
				{
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathleftback_type4intro");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);

					ani->Play(L"translate_p2_p3DeathmidType4idle", true);
				});
			MoveObject* mv = mid3->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,710.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(mid3);
			AddGameObject(mid3, ELayerType::MiddleObject);
		}

#pragma endregion 
#pragma region back
		translate_obj_cnt++;
		std::shared_ptr<GameObject> leftback = core::ObjectPool<Animator>::Spawn();
		{
			leftback->SetActive(false);
			leftback->SetName(L"p2deathleftback_type4intro");
			Transform* tf = leftback->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f,0.0f });
			Animator* ani = leftback->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathLeftBack\\intro", Vector2::Zero, 0.05f);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathLeftBack\\idle", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathLeftBackintro", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathLeftBackintro") = std::bind([this, ani]()->void
				{
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathrightbackintro");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);

					ani->Play(L"translate_p2_p3DeathLeftBackidle", true);
				});
			MoveObject* mv = leftback->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,670.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(leftback);
			AddGameObject(leftback, ELayerType::MiddleObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> Rightback = core::ObjectPool<Animator>::Spawn();
		{
			Rightback->SetActive(false);
			Rightback->SetName(L"p2deathrightbackintro");
			Transform* tf = Rightback->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1300.0f,0.0f });
			Animator* ani = Rightback->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathRightBack\\intro", Vector2::Zero, 0.05f);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathRightBack\\idle", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathRightBackintro", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathRightBackintro") = std::bind([this, ani]()->void
				{
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathleftfrontintro");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);

					ani->Play(L"translate_p2_p3DeathRightBackidle", true);
				});
			MoveObject* mv = Rightback->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,670.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(Rightback);
			AddGameObject(Rightback, ELayerType::MiddleObject);
		}
#pragma endregion
#pragma region front
		translate_obj_cnt++;
		std::shared_ptr<GameObject> leftFront = core::ObjectPool<Animator>::Spawn();
		{
			leftFront->SetActive(false);
			leftFront->SetName(L"p2deathleftfrontintro");
			Transform* tf = leftFront->GetComponent<Transform>();
			tf->SetPos(Vector2{ 100.0f,500.0f });
			tf->SetScale(Vector2{ 1.0f,1.5f });
			Animator* ani = leftFront->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathFrontGround\\translate_p2_p3DeathFrontGroundLeft\\intro", Vector2::Zero, 0.05f);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathFrontGround\\translate_p2_p3DeathFrontGroundLeft\\idle", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathFrontGroundLeftintro", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathFrontGroundLeftintro") = std::bind([this, ani]()->void
				{
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathfront_type1");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);

					ani->Play(L"translate_p2_p3DeathFrontGroundLeftidle", true);

					Camera::FadeOut();
					Camera::SetAlphaSpeed(2.0f);
				});
			MoveObject* mv = leftFront->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,900.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(leftFront);
			AddGameObject(leftFront, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> FrontType1 = core::ObjectPool<Animator>::Spawn();
		{
			FrontType1->SetActive(false);
			FrontType1->SetName(L"p2deathfront_type1");
			Transform* tf = FrontType1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f,0.0f });
			tf->SetScale(Vector2{ 1.5f,1.5f });
			Animator* ani = FrontType1->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathFrontGround\\Type1", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathFrontGroundType1", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathFrontGroundType1") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathfront_type2");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);
				});
			MoveObject* mv = FrontType1->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,1500.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(FrontType1);
			AddGameObject(FrontType1, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> FrontType2 = core::ObjectPool<Animator>::Spawn();
		{
			FrontType2->SetActive(false);
			FrontType2->SetName(L"p2deathfront_type2");
			Transform* tf = FrontType2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1300.0f,0.0f });
			tf->SetScale(Vector2{ 1.5f,1.5f });
			Animator* ani = FrontType2->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathFrontGround\\Type2", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathFrontGroundType2", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathFrontGroundType2") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
					std::shared_ptr<GameObject> next = SceneManager::FindObject(L"p2deathfront_type3");
					Animator* next_ani = next->GetComponent<Animator>();
					next_ani->SetActive(true);
					next->GetComponent<MoveObject>()->SetActive(true);
				});
			MoveObject* mv = FrontType2->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,1500.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(FrontType2);
			AddGameObject(FrontType2, ELayerType::FrontObject);
		}
		translate_obj_cnt++;
		std::shared_ptr<GameObject> FrontType3 = core::ObjectPool<Animator>::Spawn();
		{
			FrontType3->SetActive(false);
			FrontType3->SetName(L"p2deathfront_type3");
			Transform* tf = FrontType3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 800.0f,0.0f });
			tf->SetScale(Vector2{ 1.5f,1.5f });
			Animator* ani = FrontType3->GetComponent<Animator>();
			ani->SetActive(false);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\translate_p2_p3\\translate_p2_p3Death\\translate_p2_p3DeathFrontGround\\Type3", Vector2::Zero, 0.05f);
			ani->Play(L"translate_p2_p3DeathFrontGroundType3", false);
			ani->GetCompleteEvent(L"translate_p2_p3DeathFrontGroundType3") = std::bind([this, ani]()->void
				{
					if (ani->GetComEventPlayCnt() >= 1)
						return;
				});
			MoveObject* mv = FrontType3->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,2000.0f }, Vector2{ 0.0f,1.0f }, Vector2{ tf->GetPos().x,1500.0f }, false, false);
			mv->SetActive(false);
			mBgObjects[EPhaseType::PHASE3].push_back(FrontType3);
			AddGameObject(FrontType3, ELayerType::FrontObject);
		}
		mPhaseTranslateObj_Cnt = translate_obj_cnt;
#pragma endregion
#pragma endregion
#pragma region stage 1
		std::shared_ptr<GameObject> obj = core::ObjectPool<Ground>::Spawn();
		{
			obj->SetName(L"sb_p3_ground");
			obj->SetActive(false);
			Transform* tf = obj->GetComponent<Transform>();
			tf->SetPos(Vector2{ -winsize.x,winsize.y - 150.0f });
			Collider* col = obj->GetComponent<Collider>();
			col->SetSize(Vector2{ winsize.x * 4.0f,300.0f });
			mBgObjects[EPhaseType::PHASE3].push_back(obj);
			AddGameObject(obj, ELayerType::Ground);
		}
		std::shared_ptr<GameObject> sky = core::ObjectPool<Animator>::Spawn();
		{
			sky->SetActive(false);
			sky->SetName(L"sky");
			Animator* ani = sky->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\sky", Vector2::Zero, 0.3f);
			ani->Play(L"sb_p3_bgsky", true);

			float ratio = 1.228f;
			Transform* tf = sky->GetComponent<Transform>();
			tf->SetPos(Vector2{ application.GetWindowSize().x * 0.5f, 334.0f * ratio - 50.0f });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(sky);
			AddGameObject(sky, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> far_dunes = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			far_dunes->SetActive(false);
			far_dunes->SetName(L"far_dunes");
			SpriteRenderer* sprite = far_dunes->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"far_dunes", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\far-dunes.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			float ratio = 1.183f;
			Transform* tf = far_dunes->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 200.0f });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(far_dunes);
			AddGameObject(far_dunes, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> mid_dunes_back = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mid_dunes_back->SetActive(false);
			mid_dunes_back->SetName(L"mid_dunes_back");
			SpriteRenderer* sprite = mid_dunes_back->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"mid_dunes_back", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\mid-dunes-back.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			float ratio = 1.174f;
			Transform* tf = mid_dunes_back->GetComponent<Transform>();
			tf->SetPos(Vector2{ 300.0f * ratio, 225.0f - 36.0f * ratio });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(mid_dunes_back);
			AddGameObject(mid_dunes_back, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> mid_dunes_front = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mid_dunes_front->SetActive(false);
			mid_dunes_front->SetName(L"mid_dunes_front");
			SpriteRenderer* sprite = mid_dunes_front->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"mid_dunes_front", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\mid-dunes-front.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			float ratio = 1.174f;
			Transform* tf = mid_dunes_front->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 225.0f });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(mid_dunes_front);
			AddGameObject(mid_dunes_front, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> main_bg = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			main_bg->SetActive(false);
			main_bg->SetName(L"main_bg");
			SpriteRenderer* sprite = main_bg->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"main_bg", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\main-bg.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			float ratio = 1.194f;
			Transform* tf = main_bg->GetComponent<Transform>();
			tf->SetPos(Vector2{ -25.0f * ratio, 80.0f });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(main_bg);
			AddGameObject(main_bg, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> main_ground = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			main_ground->SetActive(false);
			main_ground->SetName(L"main_ground");
			SpriteRenderer* sprite = main_ground->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"main_ground", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\main-ground.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			float ratio = 1.194f;
			Transform* tf = main_ground->GetComponent<Transform>();
			tf->SetPos(Vector2{ -25.0f * ratio, 80.0f + 465.0f * ratio });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(main_ground);
			AddGameObject(main_ground, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> fg_salt = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			fg_salt->SetActive(false);
			fg_salt->SetName(L"fg_salt");
			SpriteRenderer* sprite = fg_salt->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"fg_salt", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_bg\\fg-salt.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			float ratio = 1.187f;
			Transform* tf = fg_salt->GetComponent<Transform>();
			tf->SetPos(Vector2{ -5.0f * ratio, 680.0f });
			tf->SetScale(Vector2{ ratio, ratio });

			mBgObjects[EPhaseType::PHASE3].push_back(fg_salt);
			AddGameObject(fg_salt, ELayerType::FrontObject);
		}

#pragma endregion

	}
	void SaltBakerBossScene::Phase1_Run()
	{
		ActivePhaseObject(EPhaseType::PHASE1, true);
	}
	void SaltBakerBossScene::Phase2_Run()
	{
		Phase2_Info_Register();
		ColliderManager::SetLayer(ELayerType::PlayerBullet, ELayerType::Boss, false);
		SceneManager::RemoveObjectRequest(ELayerType::Bullet);
		for (auto& vec_itr : mBgObjects[EPhaseType::PHASE1])
		{
			vec_itr->GetComponent<MoveObject>()->SetActive(true);
		}

		ActivePhaseObject(EPhaseType::PHASE2, true);

		//특정 애니 후에 phase1 remove object
		//ActivePhaseObject(EPhaseType::PHASE1, false);
	}
	void SaltBakerBossScene::Phase3_Run()
	{
		Phase3_Info_Register();
		SceneManager::RemoveObjectRequest(ELayerType::Monster);

		for (int i = 0; i < mPhaseTranslateObj_Cnt; i++)
		{
			mBgObjects[EPhaseType::PHASE3][i]->SetActive(true);
		}
	}
	void SaltBakerBossScene::Phase3_2Run()
	{

		int size = mBgObjects[EPhaseType::PHASE3].size();
		for (int i = 0; i < size; i++)
		{
			if (i >= mPhaseTranslateObj_Cnt)
				break;
			auto itr = mBgObjects[EPhaseType::PHASE3].begin();
			if (itr == mBgObjects[EPhaseType::PHASE3].end())
				break;

			SceneManager::RemoveObjectRequest((*itr).get());
			(*itr).reset();
			mBgObjects[EPhaseType::PHASE3].erase(itr);
		}
		ActivePhaseObject(EPhaseType::PHASE3, true);
		ActivePhaseObject(EPhaseType::PHASE2, false);
		ColliderManager::SetLayer(ELayerType::Monster, ELayerType::Ground, true);
	}
	void SaltBakerBossScene::ActivePhaseObject(EPhaseType _type, bool _flag)
	{
		if (_type != EPhaseType::NONE)
		{
			for (auto& vec_itr : mBgObjects[_type])
			{
				vec_itr->SetActive(_flag);
			}
		}
	}
	void SaltBakerBossScene::RemovePhaseObject(EPhaseType _type)
	{
		for (auto& vecitr : mBgObjects[_type])
		{
			SceneManager::RemoveObjectRequest(vecitr.get());
		}
	}
}
