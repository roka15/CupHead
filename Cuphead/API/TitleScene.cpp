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
extern yeram_client::Application application;

yeram_client::TitleScene::TitleScene()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();
	mLayers[(UINT)ELayerType::Player] = new Layer();

	Vector2 size = application.GetWindowSize();

	Rectangle* title = new Rectangle();
	{
		Transform* tf = title->GetComponent<Transform>();
		tf->SetPos(Vector2{ 0,0 });
		tf->SetSize(Vector2{ (long)size.x, (long)size.y });
		SpriteRenderer* render = title->AddComponent<SpriteRenderer>();
		render->SetImage(L"TitleBackGround"
			, L"..\\Resources\\title_screen\\Background\\title_screen_background.bmp");
		render->SetRenderType(ERenderType::StretchBlt);
	}
	Rectangle* ground = new Rectangle();
	{
		Transform* tf = ground->GetComponent<Transform>();
		tf->SetPos(Vector2{ 0l,(long)size.y - 280 });
		tf->SetSize(Vector2{(long)size.x,280l });
		SpriteRenderer* render = ground->AddComponent<SpriteRenderer>();
		render->SetImage(L"TitleGround"
			, L"..\\Resources\\title_screen\\DLC\\title_chips_left_0001.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
	}
	Rectangle* playobj1 = new Rectangle();
	{
		Transform* tf = playobj1->GetComponent<Transform>();
		tf->SetPos(Vector2{ 170,140 });
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj1->AddComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Cuphead", Vector2::Zero, 0.1f);
		playobj1->SetName(L"DLCCuphead");
	}
	Rectangle* playobj2 = new Rectangle();
	{
		Transform* tf = playobj2->GetComponent<Transform>();
		tf->SetPos(Vector2{ 650,210 });
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani= playobj2->AddComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Ms Chalice", Vector2::Zero, 0.1f);
		playobj2->SetName(L"DLCMs Chalice");
	}
	Rectangle* playobj3 = new Rectangle();
	{
		Transform* tf = playobj3->GetComponent<Transform>();
		tf->SetPos(Vector2{ 1000,160 });
		tf->SetSize(Vector2{ 400l, 500l });
		Animator* ani = playobj3->AddComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Mugman", Vector2::Zero, 0.1f);
		playobj3->SetName(L"DLCMugMan");
	}
	
	AddGameObject(title,ELayerType::BackObject);
	AddGameObject(ground, ELayerType::BackObject);
	AddGameObject(playobj1, ELayerType::Player);
	AddGameObject(playobj2, ELayerType::Player);
	AddGameObject(playobj3, ELayerType::Player);
}

yeram_client::TitleScene::~TitleScene()
{
}

void yeram_client::TitleScene::Initialize()
{
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
