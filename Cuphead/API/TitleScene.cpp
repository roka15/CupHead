#include "TitleScene.h"
#include "Input.h"
#include "SceneManager.h"
#include "Image.h"
#include "Resources.h"
#include "Application.h"
#include "Rectangle.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Animator.h"
#include "Layer.h"
extern yeram_client::Application application;

yeram_client::TitleScene::TitleScene()
{
	mCurType = ESceneType::Title;
}

yeram_client::TitleScene::~TitleScene()
{
}

void yeram_client::TitleScene::Initialize()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();
	mLayers[(UINT)ELayerType::Player] = new Layer();
	mLayers[(UINT)ELayerType::FrontObject] = new Layer();
	Vector2 size = application.GetWindowSize();

	Rectangle* title = GameObject::Instantiate<Rectangle>(L"TitleBackGround",Vector2{ 0,0 }, ELayerType::BackObject);
	{
		Transform* tf = title->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x, (long)size.y });
		
		SpriteRenderer* render = title->AddComponent<SpriteRenderer>();
		render->SetImage(title->GetName().c_str()
			, L"..\\Resources\\title_screen\\Background\\title_screen_background.bmp");
		render->SetRenderType(ERenderType::StretchBlt);
	}
	Rectangle* ground = GameObject::Instantiate<Rectangle>(L"TitleGround",Vector2{ 0,0 }, ELayerType::FrontObject);
	{
		Transform* tf = ground->GetComponent<Transform>();
		tf->SetPos(Vector2{ 0l,(long)size.y - 280 });
		tf->SetSize(Vector2{ (long)size.x,280l });
		SpriteRenderer* render = ground->AddComponent<SpriteRenderer>();
		render->SetImage(ground->GetName().c_str()
			, L"..\\Resources\\title_screen\\DLC\\title_chips_left_0001.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
	}
	Rectangle* playobj1 = GameObject::Instantiate<Rectangle>(Vector2{ 190,100 }, ELayerType::Player);
	{
		Transform* tf = playobj1->GetComponent<Transform>();
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj1->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Cuphead", Vector2::Zero, 0.05f);
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, playobj1);
		ani->Play(key, true);

		playobj1->SetName(key);
	}
	Rectangle* playobj2 = GameObject::Instantiate<Rectangle>(L"MainMSChalice",Vector2{ 630,210 }, ELayerType::Player);
	{
		Transform* tf = playobj2->GetComponent<Transform>();
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj2->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Ms Chalice", Vector2::Zero, 0.05f);
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, playobj2);
		ani->Play(key, true);
		playobj2->SetName(key);
	}
	Rectangle* playobj3 = GameObject::Instantiate<Rectangle>(L"MainMugMan",Vector2{ 970,100 }, ELayerType::Player);
	{
		Transform* tf = playobj3->GetComponent<Transform>();
		tf->SetSize(Vector2{ 400l, 500l });
		Animator* ani = playobj3->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Mugman", Vector2::Zero, 0.05f);
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, playobj3);
		ani->Play(key, true);
		playobj3->SetName(key);
	}
	Rectangle* text = GameObject::Instantiate<Rectangle>(L"MainPressText",Vector2{ 450,550 }, ELayerType::FrontObject);
	{
		Transform* tf = text->GetComponent<Transform>();
		tf->SetScale(Vector2{ 2.0f,2.0f });
		tf->SetSize(Vector2{ 400l, 500l });
		Animator* ani = text->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Text", Vector2::Zero, 0.5f);
		
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, text);
		ani->Play(key, true);
		text->SetName(key);
	}
	
	Scene::Initialize();
}

void yeram_client::TitleScene::Update()
{
	if (core::Input::GetKeyDown(core::EKeyCode::MouseLeft))
	{
		OnExit();
		SceneManager::LoadScene(ESceneType::MainMenu);
	}
	Scene::Update();
}

void yeram_client::TitleScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void yeram_client::TitleScene::Release()
{
	Scene::Release();
}

void yeram_client::TitleScene::OnEnter()
{
	Scene::OnEnter();
}

void yeram_client::TitleScene::OnExit()
{
	Scene::OnExit();
}
