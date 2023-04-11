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
	}
	void InWorldIntroScene::Update()
	{
		Scene::Update();
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

		std::shared_ptr<GameObject> mid = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mid->SetName(L"inworldintro_mid");
			Transform* tf = mid->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 150.0f });
			tf->SetScale(Vector2{ 1.3f, 1.0f});
			SpriteRenderer* sprite = mid->GetComponent<SpriteRenderer>();
			sprite->SetImage(mid->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_mid.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mid, ELayerType::BackObject);
		}
#pragma region cuphead ani
		std::shared_ptr<GameObject> cuphead = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		{
			cuphead->SetName(L"World4IntroAnicuphead_1");
			CutScenePlayAnimation* cutscene = cuphead->GetComponent<CutScenePlayAnimation>();
			Animator* mouse_ani = nullptr;
			std::shared_ptr<GameObject> mouse = core::ObjectPool<Animator>::Spawn();
			{
				mouse->SetName(L"World4IntroAnicuphead_2_mouse");
				mouse_ani = mouse->GetComponent<Animator>();
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2_mouse", Vector2::Zero, 0.03f, false);
				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2_mouse_2", Vector2::Zero, 0.1f, false);
				mouse_ani->Play(mouse->GetName(), true,5.0f);
				mouse_ani->GetEndEvent(L"World4IntroAnicuphead_2_mouse") = std::bind([mouse_ani]()->void {mouse_ani->Play(L"World4IntroAnicuphead_2_mouse_2", true); });
				Transform* tf = mouse->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 20.0f, -220.0f });
			}
			mouse->SetActive(false);
			cuphead->AddChild(mouse);
			Animator* ani = cuphead->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_1", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\3", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnicuphead\\4", Vector2::Zero, 0.1f, false);
			ani->GetStartEvent(L"World4IntroAnicuphead_2") = std::bind([mouse_ani]()->void
			{
				mouse_ani->SetActive(true);
			});
			ani->GetEndEvent(L"World4IntroAnicuphead_2") = std::bind([mouse_ani]()->void
			{
				mouse_ani->SetActive(false);
			});
			cutscene->SetAnimation(L"World4IntroAnicuphead_2", 15);
			cutscene->SetAnimation(L"World4IntroAnicuphead3", 0.0);
			cutscene->SetAnimation(L"World4IntroAnicuphead4",10);
			ani->Play(cuphead->GetName(), false);
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f, 650.0f });
			AddGameObject(cuphead, ELayerType::FrontObject);
		}
#pragma endregion

#pragma region mugman_ani
		std::shared_ptr<GameObject> mugman = core::ObjectPool<CutScenePlayAnimation>::Spawn();
		{
			mugman->SetName(L"World4IntroAnimugman_1");
			
			Animator* ani = mugman->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_1", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_1_2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_2", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_2_1", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\3", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\3_2", Vector2::Zero, 0.05f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAnimugman\\4", Vector2::Zero, 0.05f, false);

			CutScenePlayAnimation* cutscene = mugman->GetComponent<CutScenePlayAnimation>();
			cutscene->SetAnimation(L"World4IntroAnimugman_1_2", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman_2", 7);
			cutscene->SetAnimation(L"World4IntroAnimugman_2_1", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman_1", 3);
			cutscene->SetAnimation(L"World4IntroAnimugman_1_2", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman_2", 4);
			cutscene->SetAnimation(L"World4IntroAnimugman3", 0.0);
			cutscene->SetAnimation(L"World4IntroAnimugman3_2", 8);
			cutscene->SetAnimation(L"World4IntroAnimugman4", 0);

			Animator* mouse_ani = nullptr;
			std::shared_ptr<GameObject> mouse = core::ObjectPool<Animator>::Spawn();
			{
				mouse->SetName(L"World4IntroAnimugman_2_mouse");

				mouse_ani = mouse->GetComponent<Animator>();

				mouse_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\mugman_2_mouse", Vector2::Zero, 0.03f, false);

				Transform* tf = mouse->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -10.0f, -200.0f });
			}
			ani->GetStartEvent(L"World4IntroAnimugman_1") = std::bind([mouse_ani]()->void
			{mouse_ani->SetActive(true);
			mouse_ani->Play(L"World4IntroAnimugman_2_mouse", true); });
			ani->GetEndEvent(L"World4IntroAnimugman_1") = std::bind([mouse_ani]()->void
			{
				mouse_ani->SetActive(false);
				mouse_ani->ActiveReset();
			});

			mugman->AddChild(mouse);
			/*ani->GetCompleteEvent(L"World4IntroAnicuphead_1") = std::bind([ani, mouse]()->void
			{
				ani->Play(L"World4IntroAnicuphead_2", true);
				mouse->SetActive(true);
			});*/
			ani->Play(mugman->GetName(), false);
			
			Transform* tf = mugman->GetComponent<Transform>();
			tf->SetPos(Vector2{ 750.0f, 650.0f });
			AddGameObject(mugman, ELayerType::FrontObject);
		}
#pragma endregion

		std::shared_ptr<GameObject> portal = core::ObjectPool<Animator>::Spawn();
		{
			portal->SetName(L"World4IntroAniportalintro");
			Animator* ani = portal->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAniportal\\intro", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAniportal\\normal", Vector2::Zero, 0.1f, false);
			Animator* soul_ani = nullptr;
			std::shared_ptr<GameObject> soul = core::ObjectPool<Animator>::Spawn();
			{
				soul->SetName(L"World4IntroAniportalchalice_intro");
				MoveObject* mv = soul->AddComponent<MoveObject>();
				mv->CreateInfo(Vector2{ 50.0f,1.0f }, EDirType::LEFT);
				soul_ani = soul->GetComponent<Animator>();
				soul_ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\World4IntroAniportal\\chalice_intro", Vector2::Zero, 0.07f, false);
				soul_ani->GetCompleteEvent(L"World4IntroAniportalchalice_intro") = std::bind([soul_ani]()->void {soul_ani->GetOwner()->SetActive(false); });
				soul_ani->Play(L"World4IntroAniportalchalice_intro", false);
				Transform* tf = soul->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -25.0f,-100.0f });
			}
			portal->AddChild(soul);
			ani->GetCompleteEvent(L"World4IntroAniportalintro") = std::bind([ani, soul_ani]()->
				void {
				ani->Play(L"World4IntroAniportalnormal", true); 
				soul_ani->Play(L"World4IntroAniportalchalice_intro", false);
			});
			
			ani->Play(portal->GetName(), false);
			Transform* tf = portal->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1400.0f,500.0f });
			AddGameObject(portal, ELayerType::FrontObject);
		}
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
		
	}
	void InWorldIntroScene::OnExit()
	{
	}
}