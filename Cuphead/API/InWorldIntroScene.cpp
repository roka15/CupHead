#include "InWorldIntroScene.h"
#include "Application.h"
#include "Layer.h"
#include "ObjectPool.h"
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
			cloud->SetName(L"inworldintro_mid");
			Transform* tf = mid->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f, 150.0f });
			tf->SetScale(Vector2{ 1.3f, 1.0f});
			SpriteRenderer* sprite = mid->GetComponent<SpriteRenderer>();
			sprite->SetImage(mid->GetName(), L"..\\Resources\\World4IntroAni\\bg\\cutscene_intro_s2_mid.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mid, ELayerType::BackObject);
		}
#pragma region cuphead ani
		std::shared_ptr<GameObject> cuphead = core::ObjectPool<Animator>::Spawn();
		{
			cuphead->SetName(L"World4IntroAnicuphead_1");
			std::shared_ptr<GameObject> mouse = core::ObjectPool<Animator>::Spawn();
			{
				mouse->SetName(L"World4IntroAnicuphead_2_mouse");
				Animator* ani = mouse->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2_mouse", Vector2::Zero, 0.1f, false);
				ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2_mouse_2", Vector2::Zero, 0.1f, false);
				ani->Play(mouse->GetName(), false);
				ani->GetCompleteEvent(L"World4IntroAnicuphead_2_mouse") = std::bind([ani]()->void {ani->Play(L"World4IntroAnicuphead_2_mouse_2", true); });
				Transform* tf = mouse->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 20.0f, -220.0f });
			}
			mouse->SetActive(false);
			cuphead->AddChild(mouse);
			Animator* ani = cuphead->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_1", Vector2::Zero, 0.1f, false);
			ani->CreateAnimations(L"..\\Resources\\World4IntroAni\\cuphead_2", Vector2::Zero, 0.1f, false);
			ani->GetCompleteEvent(L"World4IntroAnicuphead_1") = std::bind([ani, mouse]()->void 
			{
				ani->Play(L"World4IntroAnicuphead_2", true);
				mouse->SetActive(true); 
			});
			ani->Play(cuphead->GetName(), false);
			Transform* tf = cuphead->GetComponent<Transform>();
			tf->SetPos(Vector2{ 400.0f, 650.0f });
			AddGameObject(cuphead, ELayerType::FrontObject);
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
		
	}
	void InWorldIntroScene::OnExit()
	{
	}
}