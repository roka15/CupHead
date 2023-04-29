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
	SaltBakerBossScene::SaltBakerBossScene():mPhase2SceneMoveSpeed(1100.0f)
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
		SaltBaker* salt = mBoss->GetComponent<SaltBaker>();
		//test 끝나면 풀기
		EPhaseType phase = salt->GetPhase();
		if (salt->ChagePhase() == false)
		{
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
		mPlayer.reset();
		mBoss.reset();
		for (auto& map_itr : mBgObjects)
		{
			for (auto& vec_itr : map_itr.second)
			{
				vec_itr.reset();
			}
		}
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
			player_obj->SetActive(true);
		}

		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::Ground, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Bullet, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Player, true);
		ColliderManager::SetLayer(ELayerType::Bullet, ELayerType::Boss, true);

		mBgObjects.insert(std::make_pair(EPhaseType::PHASE1, std::vector<std::shared_ptr<GameObject>>()));
		mBgObjects.insert(std::make_pair(EPhaseType::PHASE2, std::vector<std::shared_ptr<GameObject>>()));
		mBgObjects.insert(std::make_pair(EPhaseType::PHASE3, std::vector<std::shared_ptr<GameObject>>()));
		Phase1_Info_Register();
		Phase2_Info_Register();
		Phase3_Info_Register();
		//test
		{
		   //Phase1_Run();
		//Phase2_Run();
		}
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
		AddGameObject(sugar, ELayerType::Monster);
		AddGameObject(arm, ELayerType::Monster);
	}
	void SaltBakerBossScene::Phase2_Info_Register()
	{
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
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{0.0f,winsize.y*2.0f}, true, true);
			mv->SetArriveEvent(std::bind([mv,this]()->void
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
			tf->SetPos(Vector2{ nextpos.x,nextpos.y*2.0f });
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
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,winsize.y-(winsize.y/5.0f)});
			mv->SetArriveEvent(std::bind([]()->void
			{
			}));
			SpriteRenderer* sprite = bg3->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"ph1_ph2_tlbg3", L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\translate_phase2\\p1_p2_bg\\09-sb_ph1_ph2_bg_main_transition_area_high.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			mBgObjects[EPhaseType::PHASE2].push_back(bg3);
		}
		nextpos.y -= winsize.y;
		nextpos.y +=100.0f;
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
			tf->SetSize(winsize/2);
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
			tf->SetSize(Vector2{ winsize.x+100.0f,winsize.y});
			tf->SetPos(Vector2{ -100.0f,nextpos.y+(winsize.y / 2.0f)-150.0f });
			MoveObject* mv = bg6->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 0.0f,mPhase2SceneMoveSpeed }, Vector2{ 0.0f,1.0f }, Vector2{ 0.0f,(winsize.y / 2.0f)-100.0f });
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
	}
	void SaltBakerBossScene::Phase1_Run()
	{
		ActivePhaseObject(EPhaseType::PHASE1, true);
	}
	void SaltBakerBossScene::Phase2_Run()
	{
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
		ActivePhaseObject(EPhaseType::PHASE2, false);
		ActivePhaseObject(EPhaseType::PHASE3, true);
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
