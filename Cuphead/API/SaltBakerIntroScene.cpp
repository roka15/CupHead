#include "SaltBakerIntroScene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Application.h"
#include "CutScenePlayAnimation.h"
#include "ObjectPool.h"
#include "MoveObject.h"
#include "Time.h"
extern yeram_client::Application application;
namespace yeram_client
{
	SaltBakerIntroScene::SaltBakerIntroScene()
	{
		mCurType = ESceneType::SaltBakerBossIntro;
		SetName(L"SaltBakerIntro");
	}

	SaltBakerIntroScene::SaltBakerIntroScene(std::wstring _name)
	{
		mCurType = ESceneType::SaltBakerBossIntro;
		SetName(_name);
	}

	SaltBakerIntroScene::~SaltBakerIntroScene()
	{
	}

	void SaltBakerIntroScene::Initialize()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::BackColObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		mLayers[(UINT)ELayerType::UI] = new Layer();
		Scene::Initialize();
	}

	void SaltBakerIntroScene::Update()
	{
		if (mbStartTimer == true)
		{
			mTime += Time::DeltaTime();
		}
		if (mTime >= 5.0 &&mTime<10.0f)
		{
			std::shared_ptr<GameObject> cuphead = FindObject(L"sb_intro_cuphead");
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 730.0f,630.0f });
			tf->SetScale(Vector2{ 3.5f,3.5f });
			std::shared_ptr<GameObject> bg1 = FindObject(L"sb_intro_bg");
			bg1->SetActive(false);
			std::shared_ptr<GameObject> bg2 = FindObject(L"sb_intro_bg2");
			bg2->SetActive(true);
			std::shared_ptr<GameObject> glass = FindObject(L"sb_intro_glass");
			Transform* glass_tf = glass->GetComponent<Transform>();
			glass_tf->SetPos(Vector2{ 550.0f,250.0f });
			glass_tf->SetScale(Vector2{ 3.5f,3.5f });
			std::shared_ptr<GameObject> sb = FindObject(L"sb_intro_salt");
			sb->SetActive(false);
			std::shared_ptr<GameObject> knife = FindObject(L"sb_intro_knife");
			knife->SetActive(false);
			std::shared_ptr<GameObject> frontobj = FindObject(L"sb_intro_frontdesk");
			frontobj->SetActive(false);
			std::shared_ptr<GameObject> backobj = FindObject(L"sb_intro_back_desk");
			backobj->SetActive(false);
		}
		else if (mTime >= 10.0f)
		{
			std::shared_ptr<GameObject> sb = FindObject(L"sb_intro_salt");
			sb->SetActive(true);
			std::shared_ptr<GameObject> cuphead = FindObject(L"sb_intro_cuphead");
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 350.0f,450.0f });
			tf->SetScale(Vector2{ 1.0f,1.0f });
			std::shared_ptr<GameObject> bg1 = FindObject(L"sb_intro_bg");
			bg1->SetActive(true);
			std::shared_ptr<GameObject> bg2 = FindObject(L"sb_intro_bg2");
			bg2->SetActive(false);
			std::shared_ptr<GameObject> glass = FindObject(L"sb_intro_glass");
			Transform* glass_tf = glass->GetComponent<Transform>();
			glass_tf->SetPos(Vector2{ 290.0f,300.0f });
			glass_tf->SetScale(Vector2{ 1.0f,1.0f });
			std::shared_ptr<GameObject> knife = FindObject(L"sb_intro_knife");
			knife->SetActive(true);
			std::shared_ptr<GameObject> frontobj = FindObject(L"sb_intro_frontdesk");
			frontobj->SetActive(true);
			std::shared_ptr<GameObject> backobj = FindObject(L"sb_intro_back_desk");
			backobj->SetActive(true);
		}
		Scene::Update();
	}

	void SaltBakerIntroScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SaltBakerIntroScene::Release()
	{
		Scene::Release();
	}

	void SaltBakerIntroScene::OnEnter()
	{
		Scene::OnEnter();
		Vector2 WindowSize = application.GetWindowSize();
		std::shared_ptr<GameObject> player = FindObject(L"Player");
		{
			if (player != nullptr)
				player->SetActive(false);
		}
		std::shared_ptr<GameObject> bg1 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg1->SetName(L"sb_intro_bg");
			Transform* tf = bg1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,-50.0f });
			Vector2 size = WindowSize;
			size.y += 100;
			tf->SetSize(size);
			SpriteRenderer* sprite = bg1->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_intro_bg", L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\bg\\pre_last_boss_shot_1_bg.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
			AddGameObject(bg1, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg2 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg2->SetActive(false);
			bg2->SetName(L"sb_intro_bg2");
			Transform* tf = bg2->GetComponent<Transform>();
			//tf->SetPos(Vector2{ 0.0f,235.0f });
			tf->SetSize(WindowSize);
			SpriteRenderer* sprite = bg2->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_intro_bg2", L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\bg\\pre_last_boss_shot_1_cu.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
			AddGameObject(bg2, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> cuphead = core::ObjectPool<Animator>::Spawn();
		{
			cuphead->SetName(L"sb_intro_cuphead");
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 350.0f,450.0f });
			Animator* ani = cuphead->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\6", Vector2::Zero, 0.1);
			ani->Play(L"salt_baker_boss_intro_scene6", true);
			AddGameObject(cuphead, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> glass = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			glass->SetName(L"sb_intro_glass");
			Transform* tf = glass->GetComponent<Transform>();
			tf->SetPos(Vector2{ 290.0f,300.0f });
			SpriteRenderer* sprite = glass->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_intro_glass", L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\bg\\pre_last_boss_shot_1_bg_glass_highlight.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(glass, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> back_desk = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			back_desk->SetName(L"sb_intro_back_desk");
			Transform* tf = back_desk->GetComponent<Transform>();
			tf->SetPos(Vector2{ 863.0f,235.0f });
			tf->SetScale(Vector2{ 1.25f,1.55f });
			SpriteRenderer* sprite = back_desk->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_intro_back_desk", L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\bg\\pre_last_boss_shot_1_fg_right.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(back_desk, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> knife = core::ObjectPool<Animator>::Spawn();
		{
			knife->SetName(L"sb_intro_knife");
			knife->SetActive(false);
			Transform* tf = knife->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1260.0f,800.0f });
			tf->SetScale(Vector2{ 1.25f,1.55f });
			Animator* ani = knife->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\4_knife", Vector2::Zero, 0.1);
			ani->Play(L"salt_baker_boss_intro_scene4_knife", true);
			AddGameObject(knife, ELayerType::BackObject);
		}
	
		std::shared_ptr<GameObject> saltbaker = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		{
			saltbaker->SetName(L"sb_intro_salt");
			Transform* tf = saltbaker->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f,850.0f });
			tf->SetScale(Vector2{ 1.2f,1.2f });
			MoveObject* mv = saltbaker->AddComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 200.0f,200.0f }, EDirType::RIGHT, Vector2{ 680.0f,970.0f });
			mv->SetActive(false);
			Animator* ani = saltbaker->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\1", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\2", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\2_1", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\3", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\4", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\4_1", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\4_2", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\5", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\5_1", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\5_2", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\5_3", Vector2::Zero, 0.1);
			ani->GetEndEvent(L"salt_baker_boss_intro_scene1") =
				std::bind([ani]()->void
			{
				GameObject* owner = ani->GetOwner();
				owner->GetComponent<MoveObject>()->SetActive(true);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene2") =
				std::bind([this]()->void
			{
				std::shared_ptr<GameObject> arm = FindObject(L"sb_intro_arm");
				arm->SetActive(true);
				arm->GetComponent<Animator>()->Play(L"salt_baker_boss_intro_scene2_arm", false);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene3")=
				std::bind([this]()->void
			{
				std::shared_ptr<GameObject> arm = FindObject(L"sb_intro_arm");
				arm->GetComponent<Animator>()->Play(L"salt_baker_boss_intro_scene3_arm", false);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene3") =
				std::bind([this]()->void
			{
				std::shared_ptr<GameObject> arm = FindObject(L"sb_intro_arm");
				arm->GetComponent<Animator>()->Play(L"salt_baker_boss_intro_scene4_arm", false);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene4") =
				std::bind([this]()->void
			{
				std::shared_ptr<GameObject> arm = FindObject(L"sb_intro_arm");
				arm->SetActive(false);
			});
			ani->GetStartEvent(L"salt_baker_boss_intro_scene4_1") =
				std::bind([this,ani]()->void
			{
				GameObject* owner = ani->GetOwner();
				MoveObject* mv = owner->GetComponent<MoveObject>();
				Vector2 pos = owner->GetComponent<Transform>()->GetPos();
				mv->SetActive(true);
				mv->CreateInfo(Vector2{ 1.0f,200.0f }, Vector2{ 1.0f,-1.0f }, Vector2{ pos.x+50.0f,pos.y-100.0f});
				std::shared_ptr<GameObject> knife = FindObject(L"sb_intro_knife");
				knife->SetActive(true);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene4_1") =
				std::bind([this, ani]()->void
			{
				GameObject* owner = ani->GetOwner();
				MoveObject* mv = owner->GetComponent<MoveObject>();
				mv->SetActive(false);
			});
			ani->GetStartEvent(L"salt_baker_boss_intro_scene4_2") =
				std::bind([this,WindowSize]()->void
			{
				mbStartTimer = true;
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene5") =
				std::bind([this]()->void
			{
				std::shared_ptr<GameObject> arm = FindObject(L"sb_intro_arm");
				arm->SetActive(true);
				arm->GetComponent<Animator>()->Play(L"salt_baker_boss_intro_scene5_arm", false);
				Transform* tf = arm->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				pos.x += 100.0f;
				pos.y += 80.0f;
				tf->SetPos(pos);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene5_1") =
				std::bind([this]()->void
			{
				std::shared_ptr<GameObject> arm = FindObject(L"sb_intro_arm");
				arm->SetActive(true);
				arm->GetComponent<Animator>()->Play(L"salt_baker_boss_intro_scene5_arm2", true);
			});
			ani->GetEndEvent(L"salt_baker_boss_intro_scene5_3") =
				std::bind([this]()->void
			{
				SceneManager::SetLoadSceneMessage(std::bind([this]()->void {SceneManager::LoadScene(ESceneType::SaltBakerBoss); }));
			});

			CutScenePlayAnimation* cutscene = saltbaker->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene1", 5.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene2", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene2_1", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene3", 5.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene4", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene4_1", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene4_2", 10.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene5", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene5_1", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene5_2", 0.0);
			cutscene->SetAnimation(L"salt_baker_boss_intro_scene5_3", 5.0);

			AddGameObject(saltbaker, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> desk = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			desk->SetName(L"sb_intro_frontdesk");
			Transform* tf = desk->GetComponent<Transform>();
			tf->SetScale(Vector2{ 1.2f,1.0f });
			tf->SetPos(Vector2{ 0.0f,230.0f });
			SpriteRenderer* sprite = desk->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"sb_intro_frontdesk", L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\bg\\pre_last_boss_shot_1_fg_left.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(desk, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> arm = core::ObjectPool<Animator>::Spawn();
		{
			arm->SetName(L"sb_intro_arm");
			Transform* tf = arm->GetComponent<Transform>();
			tf->SetPos(Vector2{ 240.0f,780.0f });
			tf->SetScale(Vector2{ 1.3f,1.2f });
			Animator* ani = arm->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\2_arm", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\3_arm", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\4_arm", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\5_arm", Vector2::Zero, 0.1);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_boss_intro_scene\\5_arm2", Vector2::Zero, 0.1);
			
			AddGameObject(arm, ELayerType::FrontObject);
		}

	}

	void SaltBakerIntroScene::OnExit()
	{
		Scene::OnExit();
	}

}
