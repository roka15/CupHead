#include "InWorldIntroScene.h"
#include "Application.h"
#include "Layer.h"
#include "ObjectPool.h"
#include "Time.h"
#include "CutScenePlayAnimation.h"
#include "MoveObject.h"
extern yeram_client::Application application;
namespace yeram_client
{
	InWorldIntroScene::InWorldIntroScene()
	{
		mCurType = ESceneType::InWorldIntro;
	}
	InWorldIntroScene::InWorldIntroScene(std::wstring _name)
	{
		mCurType = ESceneType::InWorldIntro;
		SetName(_name);
	}
	InWorldIntroScene::~InWorldIntroScene()
	{

	}
	void InWorldIntroScene::Initialize()
	{
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		mLayers[(UINT)ELayerType::Player] = new Layer();
	}
	void InWorldIntroScene::Update()
	{
		Scene::Update();
		if (mbEndFlag == true)
			SceneManager::LoadScene(ESceneType::PlayMap);
	}
	void InWorldIntroScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void InWorldIntroScene::Release()
	{
		Scene::Release();
	}
	void InWorldIntroScene::OnEnter()
	{
		Vector2 size = application.GetWindowSize();
		std::shared_ptr<GameObject> sky = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			sky->SetName(L"inworldintro_sky");
			Transform* tf = sky->GetComponent<Transform>();
			tf->SetSize(size);
			SpriteRenderer* sprite = sky->GetComponent<SpriteRenderer>();
			sprite->SetImage(sky->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_sky.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
			AddGameObject(sky, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> cloud = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			cloud->SetName(L"inworldintro_cloud");
			Transform* tf = cloud->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 265.0f });
			tf->SetScale(Vector2{ 1.3f, 1.0f });
			SpriteRenderer* sprite = cloud->GetComponent<SpriteRenderer>();
			sprite->SetImage(cloud->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_clouds.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(cloud, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> bg1 = core::ObjectPool<MoveObject>::Spawn();
		{
			bg1->SetActive(false);
			bg1->SetName(L"inwordintro_bg1");
			MoveObject* mv = bg1->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT);
			Transform* tf = bg1->GetComponent<Transform>();
			SpriteRenderer* sprite = bg1->AddComponent<SpriteRenderer>();

			sprite->SetImage(bg1->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro4_mid.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 size;
			size.x = sprite->GetWidth();
			size.y = application.GetWindowSize().y;
			tf->SetSize(size);
		}
		std::shared_ptr<GameObject> tree1 = core::ObjectPool<MoveObject>::Spawn();
		{
			tree1->SetActive(false);
			tree1->SetName(L"inwordintro_tree1");
			MoveObject* mv = tree1->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT);
			Transform* tf = tree1->GetComponent<Transform>();
			SpriteRenderer* sprite = tree1->AddComponent<SpriteRenderer>();
			tf->SetPos(Vector2{ 0.0f,200.0f });
			sprite->SetImage(tree1->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_tree.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 size;
			size.x = bg1->GetComponent<SpriteRenderer>()->GetWidth();
			size.y = sprite->GetHeight();
			tf->SetSize(size);
		}


		AddGameObject(tree1, ELayerType::BackObject);
		AddGameObject(bg1, ELayerType::BackObject);


		std::shared_ptr<GameObject> mid = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mid->SetName(L"inworldintro_mid");
			Transform* tf = mid->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 150.0f });
			tf->SetScale(Vector2{ 1.3f, 1.0f });
			SpriteRenderer* sprite = mid->GetComponent<SpriteRenderer>();
			sprite->SetImage(mid->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_mid.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mid, ELayerType::BackObject);
		}


		std::shared_ptr<GameObject> gost = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		Animator* gost_ani = gost->GetComponent<Animator>();
		{
			gost->SetName(L"gost");
			gost->AddComponent<MoveObject>()->SetActive(false);
			Transform* tf;
			Animator* ani = gost_ani;
			Animator* head_ani = nullptr;
			Animator* mouse_ani = nullptr;
			Animator* tail_ani = nullptr;
			Animator* arm_ani = nullptr;
			Animator* eye_ani = nullptr;
			std::shared_ptr<GameObject> eye = core::ObjectPool<Animator>::Spawn();
			{
				eye->SetName(L"eye");
				eye->SetActive(false);
				eye_ani = eye->GetComponent<Animator>();
				eye_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\16eye", Vector2::Zero, 0.07f, false);
				eye_ani->Play(L"World4IntroAnichalice16eye", false);
				tf = eye->GetComponent<Transform>();
			}
			std::shared_ptr<GameObject> mouse = core::ObjectPool<Animator>::Spawn();
			{
				mouse->SetName(L"mouse");
				mouse_ani = mouse->GetComponent<Animator>();
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\1_mouse", Vector2::Zero, 0.07f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\16_mouse", Vector2::Zero, 0.07f, false);
				mouse_ani->Play(L"World4IntroAnichalice1_mouse", true);
				tf = mouse->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -90.0f,-115.0f });
			}
			std::shared_ptr<GameObject> tail = core::ObjectPool<Animator>::Spawn();
			{
				tail->SetName(L"tail");
				tail_ani = tail->GetComponent<Animator>();
				tail_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\tail", Vector2::Zero, 0.07f, false);
				tail_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\tail2", Vector2::Zero, 0.07f, false);
				tail_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\10_tail", Vector2::Zero, 0.07f, false);
				tail_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\tail3", Vector2::Zero, 0.07f, false);
				tail_ani->Play(L"World4IntroAnichalicetail", true);
				tf = tail->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 1.0f,1.0f });
			}
			std::shared_ptr<GameObject> arm = core::ObjectPool<Animator>::Spawn();
			{
				arm->SetName(L"arm");
				arm_ani = arm->GetComponent<Animator>();
				arm_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\2_arm", Vector2::Zero, 0.07f, false);
				arm_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\3_arm", Vector2::Zero, 0.07f, false);
				arm_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\7_8arm", Vector2::Zero, 0.07f, false);
				arm_ani->Play(L"World4IntroAnichalice2_arm", false);
				arm->SetActive(false);

				Transform* tf = arm->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -200.0f,-50.0f });
			}
			std::shared_ptr<GameObject> head = core::ObjectPool<CutScenePlayAnimation>::Spawn();
			{
				head->SetName(L"head");
				head_ani = head->GetComponent<Animator>();
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\1", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\2", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\2_2", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\3", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\3_2", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\4", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\4_2", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\7", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\8", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\10_head", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\16_head", Vector2::Zero, 0.07f, false);
				head_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\17_1", Vector2::Zero, 0.07f, false);
				CutScenePlayAnimation* cutscene = head->GetComponent<CutScenePlayAnimation>();
				cutscene->SetAnimation(L"World4IntroAnichalice1", 5.0);
				cutscene->SetAnimation(L"World4IntroAnichalice2", 0.0);
				cutscene->SetAnimation(L"World4IntroAnichalice2_2", 0.0);

				head_ani->GetEndEvent(L"World4IntroAnichalice1") = std::bind([mouse_ani]()->void
				{
					mouse_ani->Stop();
					mouse_ani->GetOwner()->SetActive(false);
				});
				head_ani->GetEndEvent(L"World4IntroAnichalice2") = std::bind([arm_ani, head_ani]()->void
				{
					head_ani->GetOwner()->GetComponent<Transform>()->SetOffset(Vector2{ -45.0f,0.0f });
					arm_ani->GetOwner()->SetActive(true);
				});
				head_ani->GetStartEvent(L"World4IntroAnichalice3") = std::bind([arm_ani]()->void
				{
					arm_ani->Play(L"World4IntroAnichalice3_arm", false);
				});
				head_ani->GetCompleteEvent(L"World4IntroAnichalice4") = std::bind([tail_ani]()->void
				{
					tail_ani->GetOwner()->SetActive(false);
				});
				head_ani->GetCompleteEvent(L"World4IntroAnichalice4_2") = std::bind([this]()->void
				{
					std::shared_ptr<GameObject> soul = FindObject(L"portal")->FindChild(L"soul");
					std::shared_ptr<GameObject> gost = FindObject(L"gost");
					gost->SetActive(false);
					soul->SetActive(true);
					Vector2 pos = gost->GetComponent<Transform>()->GetPos();
					soul->GetComponent<Transform>()->SetPos(pos);
					soul->GetComponent<Animator>()->Play(L"World4IntroAnichalice5_light", false);
					MoveObject* mv = soul->GetComponent<MoveObject>();
					mv->CreateInfo(Vector2{ 300.0f,-100.0f }, EDirType::LEFT);
					mv->SetActive(true);
				});
				head_ani->GetStartEvent(L"World4IntroAnimugman7") = std::bind([this]()->void
				{
					std::shared_ptr<GameObject> gost = FindObject(L"gost");
					std::shared_ptr<GameObject> arm = gost->FindChild(L"arm");
					arm->GetComponent<Animator>()->Play(L"World4IntroAnimugman7_8arm", true);
					std::shared_ptr<GameObject> tail = gost->FindChild(L"tail");
					tail->SetActive(true);
					tail->GetComponent<Animator>()->Play(L"World4IntroAnichalicetail", true);
					arm->SetActive(true);
				});
				head_ani->GetStartEvent(L"World4IntroAnimugman8") = std::bind([this]()->void
				{
					std::shared_ptr<GameObject> gost = FindObject(L"gost");
					std::shared_ptr<GameObject> mouse = gost->FindChild(L"mouse");
					mouse->SetActive(false);
				});
				head_ani->GetStartEvent(L"World4IntroAnichalice16_head") = std::bind([mouse_ani, this]()->void
				{
					mouse_ani->GetOwner()->SetActive(true);
					mouse_ani->Play(L"World4IntroAnichalice16_mouse", true, 5.0f);
				});
				head_ani->GetStartEvent(L"World4IntroAnichalice17_1") = std::bind([eye_ani, this]()->void
				{
					eye_ani->GetOwner()->SetActive(false);
				});
				head_ani->GetEndEvent(L"World4IntroAnichalice17_1") = std::bind([eye_ani, this]()->void
				{
					mbEndFlag = true;
				});
				tf = head->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -70.0f,-15.0f });
			}
			gost->AddChild(arm);
			gost->AddChild(tail);
			gost->AddChild(head);
			gost->AddChild(eye);
			gost->AddChild(mouse);
			tf = gost->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1290.0f,470.0f });
			gost->SetActive(false);


			AddGameObject(gost, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> portal = core::ObjectPool<Animator>::Spawn();
		Animator* portal_ani = portal->GetComponent<Animator>();
		{
			portal->SetName(L"portal");
			Animator* ani = portal_ani;
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAniportal\\intro", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAniportal\\normal", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\9_portal", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\10_portal", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\15_portal", Vector2::Zero, 0.1f, false);
			Animator* soul_ani = nullptr;
			MoveObject* mv = portal->AddComponent<MoveObject>();
			mv->SetActive(false);
			std::shared_ptr<GameObject> soul = core::ObjectPool<Animator>::Spawn();
			{
				soul->SetName(L"soul");
				MoveObject* mv = soul->AddComponent<MoveObject>();
				mv->CreateInfo(Vector2{ 50.0f,1.0f }, EDirType::LEFT);
				soul_ani = soul->GetComponent<Animator>();
				soul_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAniportal\\chalice_intro", Vector2::Zero, 0.07f, false);
				soul_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\5_light", Vector2::Zero, 0.07f, false);
				soul_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\9", Vector2::Zero, 0.07f, false);
				soul_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\15_effect", Vector2::Zero, 0.07f, false);

				soul_ani->GetCompleteEvent(L"World4IntroAniportalchalice_intro") = std::bind([soul_ani, gost_ani]()->void {
					soul_ani->GetOwner()->SetActive(false);
					gost_ani->GetOwner()->SetActive(true);
				});
				soul_ani->GetCompleteEvent(L"World4IntroAnichalice5_light") = std::bind([soul_ani, gost_ani]()->void {
					soul_ani->GetOwner()->SetActive(false);
					gost_ani->GetOwner()->SetActive(true);
				});
				soul_ani->GetStartEvent(L"World4IntroAnimugman9") = std::bind([soul_ani]()->void
				{
					soul_ani->SetActive(true);
					GameObject* owner = soul_ani->GetOwner();
					owner->SetActive(true);
					MoveObject* mv = owner->GetComponent<MoveObject>();
					mv->SetActive(false);
					Transform* tf = owner->GetComponent<Transform>();
					tf->SetOffset(Vector2{ 140.0f,-20.0f });
				});
				soul_ani->Play(L"World4IntroAniportalchalice_intro", false);
				soul_ani->GetEndEvent(L"World4IntroAnichalice15_effect") = std::bind([soul_ani, gost_ani]()->void
				{
					soul_ani->SetActive(false);
					gost_ani->GetOwner()->SetActive(true);
				});

				Transform* tf = soul->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -25.0f,-100.0f });
			}
			portal->AddChild(soul);
			ani->GetCompleteEvent(L"World4IntroAniportalintro") = std::bind([ani, soul_ani]()->
				void {
				ani->Play(L"World4IntroAniportalnormal", true);
				soul_ani->Play(L"World4IntroAniportalchalice_intro", false);
			});

			ani->Play(L"World4IntroAniportalintro", false);
			Transform* tf = portal->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1400.0f,500.0f });
			portal->SetActive(false);
			AddGameObject(portal, ELayerType::BackObject);
		}


#pragma region cuphead ani
		std::shared_ptr<GameObject> cuphead = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		{
			cuphead->SetName(L"player1");
			MoveObject* mv = cuphead->AddComponent<MoveObject>();
			mv->SetActive(false);
			CutScenePlayAnimation* cutscene = cuphead->GetComponent<CutScenePlayAnimation>();
			Animator* mouse_ani = nullptr;
			std::shared_ptr<GameObject> mouse = core::ObjectPool<Animator>::Spawn();
			{
				mouse->SetName(L"mouse");
				mouse_ani = mouse->GetComponent<Animator>();
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2_mouse", Vector2::Zero, 0.03f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2_mouse_2", Vector2::Zero, 0.1f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\7_mouse", Vector2::Zero, 0.1f, false);
				mouse_ani->Play(L"World4IntroAnicuphead_2_mouse", true, 5.0f);
				mouse_ani->GetEndEvent(L"World4IntroAnicuphead_2_mouse") = std::bind([mouse_ani]()->void
				{
					mouse_ani->Play(L"World4IntroAnicuphead_2_mouse_2", true);
				});
				Transform* tf = mouse->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 20.0f, -220.0f });
			}
			mouse->SetActive(true);
			cuphead->AddChild(mouse);
			Animator* ani = cuphead->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_1", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\3", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\4", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\5", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\6", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\7", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\8", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\9", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\10", Vector2::Zero, 0.15f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\11", Vector2::Zero, 0.1f, false);
			ani->GetStartEvent(L"World4IntroAnicuphead_2") = std::bind([mouse_ani]()->void
			{
				mouse_ani->GetOwner()->SetActive(true);
			});
			ani->GetEndEvent(L"World4IntroAnicuphead_2") = std::bind([mouse_ani]()->void
			{
				mouse_ani->GetOwner()->SetActive(false);
			});
			ani->GetStartEvent(L"World4IntroAnicuphead7") = std::bind([mouse_ani]()->void
			{
				GameObject* owner = mouse_ani->GetOwner();
				owner->SetActive(true);
				mouse_ani->Play(L"World4IntroAnicuphead7_mouse", false);
				Transform* tf = owner->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 40.0f,-140.0f });
			});
			cutscene->SetAnimation(L"World4IntroAnicuphead_2", 15);
			cutscene->SetAnimation(L"World4IntroAnicuphead3", 0.0);
			cutscene->SetAnimation(L"World4IntroAnicuphead4", 5);
			ani->Play(L"World4IntroAnicuphead_1", false);
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f, 650.0f });
			AddGameObject(cuphead, ELayerType::FrontObject);
		}
#pragma endregion

#pragma region mugman_ani
		std::shared_ptr<GameObject> mugman = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		{
			mugman->SetName(L"player2");
			mugman->AddComponent<MoveObject>()->SetActive(false);

			Animator* ani = mugman->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_1", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_1_2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_2_1", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\3", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\3_2", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\4", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\5", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\5_2", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\6", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\5", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\6", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\7", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\8", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\9", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\10", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\11", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\12", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\13", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\14", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\12", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\13", Vector2::Zero, 0.05f, false);
			CutScenePlayAnimation* cutscene = mugman->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnimugman_1_2", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman_2", 7);
			cutscene->SetAnimation(L"World4IntroAnimugman_2_1", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman_1", 3);
			cutscene->SetAnimation(L"World4IntroAnimugman_1_2", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman_2", 4);
			cutscene->SetAnimation(L"World4IntroAnimugman3", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman3_2", 7);
			cutscene->SetAnimation(L"World4IntroAnimugman4", 0);
			cutscene->SetAnimation(L"World4IntroAnimugman5", 0);
			cutscene->SetAnimation(L"World4IntroAnimugman5_2", 0);
			Animator* mouse_ani = nullptr;
			std::shared_ptr<GameObject> mouse = core::ObjectPool<Animator>::Spawn();
			{
				mouse->SetName(L"mouse");

				mouse_ani = mouse->GetComponent<Animator>();

				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_2_mouse", Vector2::Zero, 0.03f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\6_mouse", Vector2::Zero, 0.03f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\9_mouse", Vector2::Zero, 0.03f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\11_mouse", Vector2::Zero, 0.1f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\13_mouse", Vector2::Zero, 0.1f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\14_mouse", Vector2::Zero, 0.1f, false);
				mouse_ani->GetEndEvent(L"World4IntroAnichalice11_mouse") = std::bind([mouse_ani]()->void
				{
					mouse_ani->GetOwner()->SetActive(false);
				});
				mouse_ani->GetEndEvent(L"World4IntroAnichalice14_mouse") = std::bind([mouse_ani, this]()->void
				{
					ActiveShot6();
				});
				Transform* tf = mouse->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -10.0f, -200.0f });
			}
			ani->GetStartEvent(L"World4IntroAnimugman_1") = std::bind([mouse_ani]()->void
			{
				mouse_ani->GetOwner()->SetActive(true);
				mouse_ani->Play(L"World4IntroAnimugman_2_mouse", true);
			});
			ani->GetEndEvent(L"World4IntroAnimugman_1") = std::bind([mouse_ani]()->void
			{
				mouse_ani->GetOwner()->SetActive(false);
				mouse_ani->ActiveReset();
			});
			ani->GetStartEvent(L"World4IntroAnimugman3") = std::bind([portal_ani]()->void
			{
				portal_ani->GetOwner()->SetActive(true);
			});
			ani->GetStartEvent(L"World4IntroAnimugman5") = std::bind([this]()->void
			{
				this->ActiveShot2();
			}
			);
			ani->GetStartEvent(L"World4IntroAnimugman5_2") = std::bind([this]()->void
			{
				std::shared_ptr<GameObject> effect = this->FindObject(L"effect1");
				std::shared_ptr<GameObject> mugman = this->FindObject(L"player2");
				Transform* tf = mugman->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				Vector2 scale = tf->GetScale();
				Transform* e_tf = effect->GetComponent<Transform>();
				pos.y += 15.0f;
				e_tf->SetPos(pos);
				e_tf->SetScale(scale);
				effect->SetActive(true);
			});
			ani->GetCompleteEvent(L"World4IntroAnimugman5_2") = std::bind([this]()->void
			{
				ActiveShot1();
			}
			);
			ani->GetStartEvent(L"World4IntroAnichalice6") = std::bind([this]()->void
			{
				std::shared_ptr<GameObject> player1 = FindObject(L"player1");
				CutScenePlayAnimation* cutscene = player1->GetComponent<CutScenePlayAnimation>();
				cutscene->SetAnimation(L"World4IntroAnicuphead5", 0.0);
				cutscene->SetAnimation(L"World4IntroAnicuphead6", 5.0);
				std::shared_ptr<GameObject> player = FindObject(L"player2");
				std::shared_ptr<GameObject> mouse = player->FindChild(L"mouse");
				//mouse->SetActive(true);
				//mouse->GetComponent<Animator>()->Play(L"World4IntroAnichalice6_mouse", false);
				player->SetActive(true);
			});
			ani->GetStartEvent(L"World4IntroAnichalice8") = std::bind([this]()->void
			{
				std::shared_ptr<GameObject> player = FindObject(L"player2");
				MoveObject* mv = player->GetComponent<MoveObject>();
				mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::RIGHT);
				mv->SetActive(true);
			});
			ani->GetStartEvent(L"World4IntroAnichalice9") = std::bind([this]()->void
			{
				ActiveShot3();
			});
			ani->GetStartEvent(L"World4IntroAnichalice10") = std::bind([this]()->void
			{
				ActiveShot4();
			});
			ani->GetStartEvent(L"World4IntroAnichalice11") = std::bind([mouse_ani]()->void
			{
				mouse_ani->GetOwner()->SetActive(true);
			});
			ani->GetStartEvent(L"World4IntroAnichalice12") = std::bind([this]()->void
			{
				ActiveShot5();
			});
			ani->GetStartEvent(L"World4IntroAnichalice13") = std::bind([mouse_ani, this]()->void
			{
				mouse_ani->GetOwner()->SetActive(true);
				mouse_ani->Play(L"World4IntroAnichalice13_mouse", true);
				std::shared_ptr<GameObject> sb = FindObject(L"salt_bakery");
				sb->SetActive(true);
			});
			ani->GetStartEvent(L"World4IntroAnichalice14") = std::bind([mouse_ani, this]()->void
			{
				mouse_ani->Play(L"World4IntroAnichalice14_mouse", false);
				std::shared_ptr<GameObject> player2 = FindObject(L"player2");
				std::shared_ptr<GameObject> effect = FindObject(L"effect1");
				{
					effect->SetActive(true);
					effect->GetComponent<Animator>()->Play(L"World4IntroAnichalice14_light", true);
					Transform* tf = effect->GetComponent<Transform>();
					Transform* ptf = player2->GetComponent<Transform>();
					tf->SetScale(ptf->GetScale());
					tf->SetPos(ptf->GetPos());
				}
			});

			mugman->AddChild(mouse);

			ani->Play(L"World4IntroAnimugman_1", false);

			Transform* tf = mugman->GetComponent<Transform>();
			tf->SetPos(Vector2{ 750.0f, 650.0f });
			AddGameObject(mugman, ELayerType::FrontObject);
		}
#pragma endregion

#pragma region sb
		std::shared_ptr<GameObject> salt_bakery = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		{
			salt_bakery->SetName(L"salt_bakery");
			salt_bakery->SetActive(false);
			Transform* tf = salt_bakery->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1200.0f, 570.0f });
			Animator* ani = salt_bakery->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\sbshop\\introsb\\1", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\sbshop\\introsb\\2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\sbshop\\introsb\\3", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\sbshop\\introsb\\4", Vector2::Zero, 0.1f, false);
			CutScenePlayAnimation* cutscene = salt_bakery->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"introsb1", 0.0);
			cutscene->SetAnimation(L"introsb2", 0.0);
			AddGameObject(salt_bakery, ELayerType::BackObject);
		}
#pragma endregion

		std::shared_ptr<GameObject> s2_fg = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			s2_fg->SetName(L"inworldintro_s2fg");
			Transform* tf = s2_fg->GetComponent<Transform>();
			tf->SetPos(Vector2{ 85.0f, 170.0f });
			tf->SetScale(Vector2{ 1.3f,1.0f });
			SpriteRenderer* sprite = s2_fg->GetComponent<SpriteRenderer>();
			sprite->SetImage(s2_fg->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_fg.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(s2_fg, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> cabinet = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			cabinet->SetActive(false);
			cabinet->SetName(L"inworldintro_cabinet");
			Transform* tf = cabinet->GetComponent<Transform>();
			tf->SetPos(Vector2{ 590.0f,470.0f });
			tf->SetScale(Vector2{ 1.25f,1.5f });
			SpriteRenderer* sprite = cabinet->GetComponent<SpriteRenderer>();
			sprite->SetImage(cabinet->GetName(), L"..\\Resources\\World4IntroAni\\sbshop\\cutscene_intro_s6_counter.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(cabinet, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> effect1 = core::ObjectPool<Animator>::Spawn();
		{
			effect1->SetName(L"effect1");
			effect1->AddComponent<MoveObject>();
			MoveObject* mv = effect1->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 300.0f,100.0f }, EDirType::RIGHT);
			mv->SetActive(false);
			Animator* ani = effect1->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\5_2_light", Vector2::Zero, 0.03f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\6_light", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\7_light", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnichalice\\14_light", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\11", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\12_1", Vector2::Zero, 0.1f, false);
			ani->GetCompleteEvent(L"World4IntroAnimugman6_light") = std::bind([ani, this]()->void
			{
				FindObject(L"player2")->SetActive(false);
				ani->Play(L"World4IntroAnimugman7_light", false);
				ani->GetOwner()->GetComponent<MoveObject>()->SetActive(true);
			}
			);
			ani->GetCompleteEvent(L"World4IntroAnimugman7_light") = std::bind([ani, this]()->void
			{
				std::shared_ptr<GameObject> gost = FindObject(L"gost");
				gost->SetActive(true);
				std::shared_ptr<GameObject> player = FindObject(L"player2");
				player->SetActive(true);
				CutScenePlayAnimation* cutscene = gost->GetComponent<CutScenePlayAnimation>();
				//here
				MoveObject* mv = ani->GetOwner()->GetComponent<MoveObject>();
				mv->SetActive(false);
				ani->GetOwner()->SetActive(false);
			}
			);

			ani->GetCompleteEvent(L"World4IntroAnimugman11") = std::bind([ani, this]()->void
			{
				ani->Play(L"World4IntroAnimugman12_1", false);
			}
			);
			ani->GetCompleteEvent(L"World4IntroAnimugman12_1") = std::bind([ani, this]()->void
			{
				ani->GetOwner()->SetActive(false);
				std::shared_ptr<GameObject> player2 = FindObject(L"player2");
				{
					player2->SetActive(true);
				}
			}
			);
			ani->Play(L"World4IntroAnimugman5_2_light", true);
			effect1->SetActive(false);
			AddGameObject(effect1, ELayerType::BackObject);
		}


		Vector2 nextpos;
		std::shared_ptr<GameObject> start_tree = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			start_tree->SetName(L"cutscene_intro_s4_forest_start");
			start_tree->SetActive(false);
			MoveObject* mv = start_tree->AddComponent<MoveObject>();
			Transform* tf = start_tree->GetComponent<Transform>();

			SpriteRenderer* sprite = start_tree->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_forest_start", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_forest_start.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			tf->SetPos(Vector2{ 600.0f,200.0f });
			Vector2 pos = tf->GetPos();
			nextpos.x = pos.x + spritesize.x;
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(start_tree, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> tree_loop = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			tree_loop->SetName(L"cutscene_intro_s4_forest_loop");
			tree_loop->SetActive(false);
			MoveObject* mv = tree_loop->AddComponent<MoveObject>();
			Transform* tf = tree_loop->GetComponent<Transform>();

			SpriteRenderer* sprite = tree_loop->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_forest_loop", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_forest_loop.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			tf->SetPos(Vector2{ nextpos.x-10.0f,180.0f });
			Vector2 pos = tf->GetPos();
			nextpos.x = pos.x + spritesize.x;
			nextpos.y = pos.y;
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(tree_loop, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> tree_loop2 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			tree_loop2->SetName(L"cutscene_intro_s4_forest_loop2");
			tree_loop2->SetActive(false);
			MoveObject* mv = tree_loop2->AddComponent<MoveObject>();
			Transform* tf = tree_loop2->GetComponent<Transform>();

			SpriteRenderer* sprite = tree_loop2->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_forest_loop", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_forest_loop.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			tf->SetPos(Vector2{ nextpos.x - 10.0f,180.0f });
			Vector2 pos = tf->GetPos();
			nextpos.x = pos.x + spritesize.x;
			nextpos.y = pos.y;
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(tree_loop2, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> tree_loop3 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			tree_loop3->SetName(L"cutscene_intro_s4_forest_loop3");
			tree_loop3->SetActive(false);
			MoveObject* mv = tree_loop3->AddComponent<MoveObject>();
			Transform* tf = tree_loop3->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			SpriteRenderer* sprite = tree_loop3->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_forest_loop", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_forest_loop.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			tf->SetPos(Vector2{ nextpos.x - 10.0f,180.0f });
			nextpos.x = pos.x + spritesize.x;
			nextpos.y = pos.y;
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(tree_loop3, ELayerType::BackObject);
		}
		nextpos = Vector2::Zero;
		std::shared_ptr<GameObject> shot3_bg1 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			shot3_bg1->SetName(L"cutscene_intro_s4_mid_start");
			shot3_bg1->SetActive(false);
			MoveObject* mv = shot3_bg1->AddComponent<MoveObject>();
			Transform* tf = shot3_bg1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,0.0f });
			tf->SetSize(size);
			Vector2 pos = tf->GetPos();

			SpriteRenderer* sprite = shot3_bg1->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_mid_start", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_mid_start.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			nextpos.x = pos.x + size.x;

			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(shot3_bg1, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> shot3_bg2 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			shot3_bg2->SetName(L"cutscene_intro_s4_mid_loop1");
			shot3_bg2->SetActive(false);
			MoveObject* mv = shot3_bg2->AddComponent<MoveObject>();
			Transform* tf = shot3_bg2->GetComponent<Transform>();
			tf->SetPos(nextpos);
			tf->SetSize(size);
			Vector2 pos = tf->GetPos();

			SpriteRenderer* sprite = shot3_bg2->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_mid_loop1", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_mid_loop1.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			nextpos.x = pos.x + size.x;
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(shot3_bg2, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> shot3_bg3 = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			shot3_bg3->SetName(L"cutscene_intro_s4_main_finish");
			shot3_bg3->SetActive(false);
			MoveObject* mv = shot3_bg3->AddComponent<MoveObject>();
			Transform* tf = shot3_bg3->GetComponent<Transform>();
			tf->SetPos(nextpos);
			tf->SetSize(size);
			Vector2 pos = tf->GetPos();

			SpriteRenderer* sprite = shot3_bg3->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"cutscene_intro_s4_main_finish", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s4_main_finish.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Vector2 spritesize;
			spritesize.x = sprite->GetWidth();
			spritesize.y = sprite->GetHeight();
			nextpos.x = pos.x + size.x;
			mv->CreateInfo(Vector2{ 300.0f,0.0f }, EDirType::LEFT, Vector2{ -10.0f - size.x,pos.y }, true, false);
			AddGameObject(shot3_bg3, ELayerType::BackObject);
		}
		Scene::OnEnter();
	}
	void InWorldIntroScene::OnExit()
	{
		Scene::OnExit();
	}
	void InWorldIntroScene::ActiveShot1()
	{
		Vector2 size = application.GetWindowSize();
		application.ScreenClear();
		FindObject(L"inworldintro_s2fg")->SetActive(true);
		FindObject(L"player1")->SetActive(true);
		std::shared_ptr<GameObject> effect = FindObject(L"effect1");
		{
			effect->GetComponent<Animator>()->Play(L"World4IntroAnimugman6_light", false);
			Transform* e_tf = effect->GetComponent<Transform>();
			std::shared_ptr<GameObject> p2 = FindObject(L"player2");
			{
				Transform* tf = p2->GetComponent<Transform>();
				tf->SetPos(Vector2{ 750.0f, 650.0f });
				CutScenePlayAnimation* cutscene = p2->GetComponent<CutScenePlayAnimation>();
				cutscene->SetAnimation(L"World4IntroAnimugman6", 0.0f);
				cutscene->SetAnimation(L"World4IntroAnichalice5", 0.0f);
				cutscene->SetAnimation(L"World4IntroAnichalice6", 5.0f);
				cutscene->SetAnimation(L"World4IntroAnichalice7", 0.0f);
				cutscene->SetAnimation(L"World4IntroAnichalice8", 5.0f);
				cutscene->SetAnimation(L"World4IntroAnichalice9", 10.5f);
				e_tf->SetPos(tf->GetPos());
				e_tf->SetScale(Vector2{ 1.0f,1.0f });
			}
		}
		std::shared_ptr<GameObject> portal = FindObject(L"portal");
		{
			Transform* tf = portal->GetComponent<Transform>();
			tf->SetScale(Vector2{ 1.0f,1.0f });
			tf->SetPos(Vector2{ 1400.0f,500.0f });
		}
		std::shared_ptr<GameObject> gost = FindObject(L"gost");
		{
			Transform* tf = gost->GetComponent<Transform>();
			//tf->SetScale(Vector2{ 1.0f,1.0f });
			tf->SetPos(Vector2{ 1290.0f,470.0f });
			std::shared_ptr<GameObject> tail = gost->FindChild(L"tail");
			Transform* t_tf = tail->GetComponent<Transform>();
			t_tf->SetScale(Vector2{ 1.0f,1.0f });
			t_tf->SetOffset(Vector2{ 1.0f,1.0f });
			Animator* t_ani = tail->GetComponent<Animator>();
			t_ani->Play(L"World4IntroAnichalicetail", true);

			Transform* h_tf = gost->FindChild(L"head")->GetComponent<Transform>();
			h_tf->SetOffset(Vector2{ -70.0f,-15.0f });

			std::shared_ptr<GameObject> head = gost->FindChild(L"head");
			CutScenePlayAnimation* cutscene = head->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnichalice4", 0.0);
			cutscene->SetAnimation(L"World4IntroAnichalice4_2", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman7", 5.0);
			cutscene->SetAnimation(L"World4IntroAnimugman8", 0.0);

			std::shared_ptr<GameObject> arm = gost->FindChild(L"arm");
			arm->SetActive(false);
		}
		std::shared_ptr<GameObject> mid = FindObject(L"inworldintro_mid");
		{
			SpriteRenderer* sprite = mid->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"inworldintro_mid", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_mid.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
		}

		std::shared_ptr<GameObject> cloud = FindObject(L"inworldintro_cloud");
		{
			SpriteRenderer* sprite = cloud->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"inworldintro_cloud", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_clouds.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = cloud->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 265.0f });
		}
	}
	void InWorldIntroScene::ActiveShot2()
	{
		Vector2 size = application.GetWindowSize();
		application.ScreenClear();
		FindObject(L"inworldintro_s2fg")->SetActive(false);
		FindObject(L"player1")->SetActive(false);

		std::shared_ptr<GameObject> p2 = FindObject(L"player2");
		{
			Transform* tf = p2->GetComponent<Transform>();
			//tf->SetScale(Vector2{ 1.0f,1.0f });
			tf->SetPos(Vector2{ 400.0f,800.0f });
		}
		std::shared_ptr<GameObject> portal = FindObject(L"portal");
		{
			Transform* tf = portal->GetComponent<Transform>();
			tf->SetScale(Vector2{ 2.0f,2.0f });
			Vector2 offset = tf->GetOffset();
			offset.y -= 100.0f;
			tf->SetOffset(offset);
		}
		std::shared_ptr<GameObject> gost = FindObject(L"gost");
		{
			Transform* tf = gost->GetComponent<Transform>();
			//tf->SetScale(Vector2{ 1.0f,1.0f });
			tf->SetPos(Vector2{ 1200.0f,600.0f });
			Transform* t_tf = gost->FindChild(L"tail")->GetComponent<Transform>();
			t_tf->SetScale(Vector2{ 2.0f,2.0f });
			t_tf->SetOffset(Vector2{ -90.0f,-120.0f });
			Transform* h_tf = gost->FindChild(L"head")->GetComponent<Transform>();
			Vector2 h_offset = h_tf->GetOffset();
			h_offset.x -= 60.0f;
			h_offset.y += 10.0f;
			h_tf->SetOffset(h_offset);
			std::shared_ptr<GameObject> head = gost->FindChild(L"head");
			CutScenePlayAnimation* cutscene = head->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnichalice3", 0.0);
			cutscene->SetAnimation(L"World4IntroAnichalice3_2", 0.0);
		}
		std::shared_ptr<GameObject> mid = FindObject(L"inworldintro_mid");
		{
			SpriteRenderer* sprite = mid->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"inworldshot2_mid", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s3_fg.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
		}

		std::shared_ptr<GameObject> cloud = FindObject(L"inworldintro_cloud");
		{
			SpriteRenderer* sprite = cloud->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"inworldshot2_cloud", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s3_clouds.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			Transform* tf = cloud->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,100.0f });
		}
	}
	void InWorldIntroScene::ActiveShot3()
	{
		Vector2 size = application.GetWindowSize();
		application.ScreenClear();
		std::shared_ptr<GameObject> effect = FindObject(L"effect1");
		{
			effect->SetActive(false);
		}

		std::shared_ptr<GameObject> s2fg = FindObject(L"inworldintro_s2fg");
		{
			s2fg->SetActive(false);
		}
		std::shared_ptr<GameObject> mid = FindObject(L"inworldintro_mid");
		{
			mid->SetActive(false);
		}
		/*std::shared_ptr<GameObject> tree = FindObject(L"inwordintro_tree1");
		{
			tree->SetActive(true);
		}*/
		/*	std::shared_ptr<GameObject> bg1 = FindObject(L"inwordintro_bg1");
			{
				bg1->SetActive(true);
			}*/
		std::shared_ptr<GameObject> tree_start = FindObject(L"cutscene_intro_s4_forest_start");
		{
			tree_start->SetActive(true);
		}
		std::shared_ptr<GameObject> tree_loop = FindObject(L"cutscene_intro_s4_forest_loop");
		{
			tree_loop->SetActive(true);
		}

		std::shared_ptr<GameObject> tree_loop2 = FindObject(L"cutscene_intro_s4_forest_loop2");
		{
			tree_loop2->SetActive(true);
		}
		std::shared_ptr<GameObject> tree_loop3 = FindObject(L"cutscene_intro_s4_forest_loop3");
		{
			tree_loop3->SetActive(true);
		}
		std::shared_ptr<GameObject> bg1 = FindObject(L"cutscene_intro_s4_mid_start");
		{
			bg1->SetActive(true);
		}
		std::shared_ptr<GameObject> bg2 = FindObject(L"cutscene_intro_s4_mid_loop1");
		{
			bg2->SetActive(true);
		}
		std::shared_ptr<GameObject> bg3 = FindObject(L"cutscene_intro_s4_main_finish");
		{
			bg3->SetActive(true);
		}

		std::shared_ptr<GameObject> portal = FindObject(L"portal");
		{
			MoveObject* mv = portal->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 40.0f,0.0f }, EDirType::RIGHT);
			mv->SetActive(true);
			Transform* tf = portal->GetComponent<Transform>();
			tf->SetPos(Vector2{ -450.0f, 600.0f });
			Animator* ani = portal->GetComponent<Animator>();
			ani->Play(L"World4IntroAnimugman9_portal", true);

			std::shared_ptr<GameObject> soul = portal->FindChild(L"soul");
			{
				Animator* ani = soul->GetComponent<Animator>();
				ani->Play(L"World4IntroAnimugman9", true);
			}
		}
		std::shared_ptr<GameObject> player1 = FindObject(L"player1");
		{
			MoveObject* mv = player1->GetComponent<MoveObject>();
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 30.0f,0.0f }, EDirType::RIGHT);
			CutScenePlayAnimation* cutscene = player1->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnicuphead7", 10.0);
			Transform* tf = player1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 50.0f,800.0f });
		}
		std::shared_ptr<GameObject> player2 = FindObject(L"player2");
		{
			MoveObject* mv = player2->GetComponent<MoveObject>();
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 40.0f,0.0f }, EDirType::RIGHT);
			CutScenePlayAnimation* cutscene = player2->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnichalice10", 0.0);
			cutscene->SetAnimation(L"World4IntroAnichalice11", 10.0);
			Transform* tf = player2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 300.0f,800.0f });
			std::shared_ptr<GameObject> mouse = player2->FindChild(L"mouse");
			{
				mouse->SetActive(true);
				mouse->GetComponent<Animator>()->Play(L"World4IntroAnichalice9_mouse", false);
				Transform* tf = mouse->GetComponent<Transform>();
				Vector2 offset = tf->GetOffset();
				offset.y += 85.0f;
				offset.x += 20.0f;
				tf->SetOffset(offset);
			}
		}
		std::shared_ptr<GameObject> gost = FindObject(L"gost");
		{
			gost->SetActive(false);
			/*MoveObject* mv = gost->GetComponent<MoveObject>();
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 100.0f,0.0f }, EDirType::RIGHT);
			CutScenePlayAnimation* cutscene = gost->GetComponent<CutScenePlayAnimation>();
			Transform* tf = gost->GetComponent<Transform>();*/
		}

	}
	void InWorldIntroScene::ActiveShot4()
	{
		std::shared_ptr<GameObject> bg2 = FindObject(L"cutscene_intro_s4_mid_loop1");
		{
			if (bg2 != nullptr)
			{
				bg2->SetActive(false);
				RemoveGameObject(bg2.get());
			}
		}
		std::shared_ptr<GameObject> bg3 = FindObject(L"cutscene_intro_s4_main_finish");
		{
			if (bg3 != nullptr)
			{
				bg3->SetActive(false);
				RemoveGameObject(bg3.get());
			}
		}
		std::shared_ptr<GameObject> tree1 = FindObject(L"cutscene_intro_s4_forest_loop2");
		{
			if (tree1 != nullptr)
			{
				tree1->SetActive(false);
				RemoveGameObject(tree1.get());
			}
		}
		std::shared_ptr<GameObject> tree2 = FindObject(L"cutscene_intro_s4_forest_loop3");
		{
			if (tree2 != nullptr)
			{
				tree2->SetActive(false);
				RemoveGameObject(tree2.get());
			}
		}
		Vector2 size = application.GetWindowSize();
		application.ScreenClear();

		/*std::shared_ptr<GameObject> tree = FindObject(L"inwordintro_tree1");
		{
			tree->SetActive(false);
		}*/
		/*std::shared_ptr<GameObject> bg1 = FindObject(L"inwordintro_bg1");
		{
			bg1->SetActive(false);
		}*/
		std::shared_ptr<GameObject> cloude = FindObject(L"inworldintro_cloud");
		{
			cloude->SetActive(false);
		}
		std::shared_ptr<GameObject> sky = FindObject(L"inworldintro_sky");
		{
			Transform* tf = sky->GetComponent<Transform>();
			tf->SetSize(size);
			SpriteRenderer* sprite = sky->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"intros5_bck", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s5_bck.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
		}
		std::shared_ptr<GameObject> portal = FindObject(L"portal");
		{
			portal->SetActive(true);
			portal->FindChild(L"soul")->SetActive(false);
			portal->GetComponent<Animator>()->Play(L"World4IntroAnimugman10_portal", true);
			Transform* tf = portal->GetComponent<Transform>();
			tf->SetPos({ -100.0f,700.0f });
			Vector2 curpos = tf->GetPos();
			MoveObject* mv = portal->GetComponent<MoveObject>();
			curpos.x += 250;
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 100.0f,0.0f }, EDirType::RIGHT, curpos);
		}
		std::shared_ptr<GameObject> gost = FindObject(L"gost");
		{
			gost->SetActive(true);
			Transform* tf = gost->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 700.0f });
			MoveObject* mv = gost->GetComponent<MoveObject>();
			Vector2 curpos = tf->GetPos();
			curpos.x += 250;
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 100.0f,0.0f }, EDirType::RIGHT, curpos);

			gost->FindChild(L"arm")->SetActive(false);
			std::shared_ptr<GameObject> head = gost->FindChild(L"head");
			{
				head->GetComponent<Animator>()->Play(L"World4IntroAnimugman10_head", false);
				Transform* tf = head->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 90,-110 });
			}
			std::shared_ptr<GameObject> tail = gost->FindChild(L"tail");
			{
				tail->GetComponent<Animator>()->Play(L"World4IntroAnimugman10_tail", true);
			}
		}
		std::shared_ptr<GameObject> player1 = FindObject(L"player1");
		{
			player1->SetActive(true);
			player1->FindChild(L"mouse")->SetActive(false);
			Transform* tf = player1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 50.0f,800.0f });
			CutScenePlayAnimation* cutscene = player1->GetComponent<CutScenePlayAnimation>();
			MoveObject* mv = player1->GetComponent<MoveObject>();
			Vector2 curpos = tf->GetPos();
			curpos.x += 500;
			mv->CreateInfo(Vector2{ 400.0f,0.0f }, EDirType::RIGHT, curpos);
			cutscene->SetAnimation(L"World4IntroAnicuphead8", 0.0);
			cutscene->SetAnimation(L"World4IntroAnicuphead9", 5.0);
		}
		std::shared_ptr<GameObject> player2 = FindObject(L"player2");
		{
			MoveObject* mv = player2->GetComponent<MoveObject>();
			mv->SetActive(false);
			CutScenePlayAnimation* cutscene = player2->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnichalice12", 0.0);
			Transform* tf = player2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 800.0f,700.0f });
			std::shared_ptr<GameObject> mouse = player2->FindChild(L"mouse");
			{
				mouse->GetComponent<Animator>()->Play(L"World4IntroAnichalice11_mouse", true, 4.0f);
				Transform* tf = mouse->GetComponent<Transform>();
				Vector2 offset = tf->GetOffset();
				offset.y -= 27.0f;
				offset.x -= 56.0f;
				tf->SetOffset(offset);
			}
		}

	}
	void InWorldIntroScene::ActiveShot5()
	{
		Vector2 size = application.GetWindowSize();
		application.ScreenClear();
		std::shared_ptr<GameObject> sky = FindObject(L"inworldintro_sky");
		{
			Transform* tf = sky->GetComponent<Transform>();
			tf->SetSize(size);
			SpriteRenderer* sprite = sky->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"intros6_bck", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s6_bck.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
		}
		std::shared_ptr<GameObject> portal = FindObject(L"portal");
		{
			portal->SetActive(false);
		}
		std::shared_ptr<GameObject> gost = FindObject(L"gost");
		{
			gost->SetActive(false);
		}
		std::shared_ptr<GameObject> player1 = FindObject(L"player1");
		{
			player1->SetActive(false);
		}
		std::shared_ptr<GameObject> player2 = FindObject(L"player2");
		{
			CutScenePlayAnimation* cutscene = player2->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnichalice13", 4.0);
			cutscene->SetAnimation(L"World4IntroAnichalice14", 4.0);
			Transform* tf = player2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 500.0f,820.0f });
			tf->SetScale(Vector2{ 1.2f,1.2f });
			std::shared_ptr<GameObject> mouse = player2->FindChild(L"mouse");
			{
				mouse->SetActive(true);
				Transform* tf = mouse->GetComponent<Transform>();
				Vector2 offset = tf->GetOffset();
				offset.x = -25.0f;
				offset.y = -130.0f;
				tf->SetOffset(offset);
			}
		}
		std::shared_ptr<GameObject> cabinet = FindObject(L"inworldintro_cabinet");
		{
			cabinet->SetActive(true);
		}

	}
	void InWorldIntroScene::ActiveShot6()
	{
		Vector2 size = application.GetWindowSize();
		application.ScreenClear();
		std::shared_ptr<GameObject> sky = FindObject(L"inworldintro_sky");
		{
			Transform* tf = sky->GetComponent<Transform>();
			tf->SetSize(size);
			SpriteRenderer* sprite = sky->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"intros7_bck", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s7_bck.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
		}
		std::shared_ptr<GameObject> cabinet = FindObject(L"inworldintro_cabinet");
		{
			SpriteRenderer* sprite = cabinet->GetComponent<SpriteRenderer>();
			sprite->SetImage(L"intros7_cabinet", L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s7_mid.bmp");
			Transform* tf = cabinet->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x += 170.0f;
			pos.y -= 295.0f;
			tf->SetPos(pos);

			cabinet->SetActive(true);
		}
		std::shared_ptr<GameObject> player2 = FindObject(L"player2");
		{
			player2->SetActive(false);
			CutScenePlayAnimation* cutscene = player2->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnimugman12", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman13", 0.0);
			MoveObject* mv = player2->GetComponent<MoveObject>();
			mv->SetActive(false);

			Transform* tf = player2->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x += 50.0f;
			tf->SetPos(pos);
			tf->SetScale(Vector2::One);
			std::shared_ptr<GameObject> mouse = player2->FindChild(L"mouse");
			{
				mouse->SetActive(false);
				Transform* tf = mouse->GetComponent<Transform>();
				Vector2 offset = tf->GetOffset();
				offset.x = -25.0f;
				offset.y = -130.0f;
				tf->SetOffset(offset);
			}
		}
		std::shared_ptr<GameObject> portal = FindObject(L"portal");
		{
			portal->SetActive(true);
			MoveObject* mv = portal->GetComponent<MoveObject>();
			mv->SetActive(false);
			Animator* ani = portal->GetComponent<Animator>();
			ani->Play(L"World4IntroAnichalice15_portal", true);
			Transform* portal_tf = portal->GetComponent<Transform>();
			Vector2 portal_pos = portal_tf->GetPos();
			portal_pos.x += 200.0f;
			portal_pos.y -= 100.0f;
			portal_tf->SetPos(portal_pos);
			std::shared_ptr<GameObject> soul = portal->FindChild(L"soul");
			{
				soul->SetActive(true);
				Animator* s_ani = soul->GetComponent<Animator>();
				s_ani->Play(L"World4IntroAnichalice15_effect", false);
				Transform* tf = soul->GetComponent<Transform>();
				MoveObject* mv = soul->GetComponent<MoveObject>();
				Transform* p_tf = player2->GetComponent<Transform>();
				Vector2 offset = p_tf->GetPos() - portal_tf->GetPos();
				mv->SetActive(true);
				tf->SetOffset(offset);
				mv->CreateInfo(Vector2{ 400.0f,200.0f }, EDirType::LEFT, portal_tf->GetPos());
			}
		}
		std::shared_ptr<GameObject> effect1 = FindObject(L"effect1");
		{
			effect1->SetActive(true);
			Transform* p_tf = player2->GetComponent<Transform>();
			Transform* portal_tf = portal->GetComponent<Transform>();
			Vector2 pos = portal_tf->GetPos();
			Vector2 target_pos = p_tf->GetPos();
			Transform* tf = effect1->GetComponent<Transform>();
			Animator* ani = effect1->GetComponent<Animator>();
			MoveObject* mv = effect1->GetComponent<MoveObject>();
			ani->Play(L"World4IntroAnimugman11", false);
			tf->SetPos(pos);
			mv->SetActive(true);

			mv->CreateInfo(Vector2{ 400.0f,200.0f }, EDirType::RIGHT, target_pos);
		}
		std::shared_ptr<GameObject> sb = FindObject(L"salt_bakery");
		{
			sb->SetActive(true);

			CutScenePlayAnimation* cutscene = sb->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"introsb4", 5.0);
			cutscene->SetAnimation(L"introsb3", 5.0);
			cutscene->SetAnimation(L"introsb4", 5.0);
			Transform* tf = sb->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.y -= 150.0f;
			tf->SetPos(pos);
		}

		std::shared_ptr<GameObject> gost = FindObject(L"gost");
		{
			gost->SetActive(false);
			Transform* tf = gost->GetComponent<Transform>();
			Vector2 pos = portal->GetComponent<Transform>()->GetPos();
			pos.x += 50.0f;
			tf->SetPos(pos);
			std::shared_ptr<GameObject> tail = gost->FindChild(L"tail");
			tail->GetComponent<Animator>()->Play(L"World4IntroAnichalicetail3", true);
			std::shared_ptr<GameObject> head = gost->FindChild(L"head");
			head->SetActive(true);

			CutScenePlayAnimation* cutscene = head->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnichalice16_head", 5.0);
			cutscene->SetAnimation(L"World4IntroAnichalice17_1", 0.0);
			std::shared_ptr<GameObject> mouse = gost->FindChild(L"mouse");
			Transform* mtf = mouse->GetComponent<Transform>();
			Transform* htf = head->GetComponent<Transform>();
			Vector2 offset = htf->GetOffset();
			offset.x -= 30.0f;
			offset.y += 60.0f;
			htf->SetOffset(offset);
			offset.y -= 30.0f;
			mtf->SetOffset(offset);
			std::shared_ptr<GameObject> eye = gost->FindChild(L"eye");
			{
				eye->SetActive(true);
				Transform* etf = eye->GetComponent<Transform>();
				offset.y -= 30.0f;
				etf->SetOffset(offset);
			}
		}
		std::shared_ptr<GameObject> player1 = FindObject(L"player1");
		{
			player1->SetActive(true);
			CutScenePlayAnimation* cutscene = player1->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnicuphead10", 0.0);
			cutscene->SetAnimation(L"World4IntroAnicuphead11", 0.0);
			player1->GetComponent<MoveObject>()->SetActive(false);
			Transform* tf = player1->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x -= 250.0f;
			pos.y += 30.0f;
			tf->SetPos(pos);
		}



	}
}