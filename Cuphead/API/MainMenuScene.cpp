#include "MainMenuScene.h"
#include "Rectangle.h"
#include "Application.h"
#include "SceneManager.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Layer.h"
#include "UI.h"
//#include "WindowManager.h"

extern yeram_client::Application application;
yeram_client::MainMenuScene::MainMenuScene()
{
	mCurType = ESceneType::MainMenu;
}

yeram_client::MainMenuScene::~MainMenuScene()
{
}

void yeram_client::MainMenuScene::Initialize()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();
	mLayers[(UINT)ELayerType::UI] = new Layer();
	
	//WindowManager::ActiveWindow((UINT)EWindowType::MainMenu);
	Vector2 size = application.GetWindowSize();
#pragma region main menu window
	Rectangle* rectangle = GameObject::Instantiate<Rectangle>(L"MenuBackGround", Vector2{ 0,0 }, nullptr, ELayerType::UI);
	{
		Transform* tf = rectangle->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x,(long)size.y });

		SpriteRenderer* render = rectangle->AddComponent<SpriteRenderer>();
		render->SetImage(rectangle->GetName().c_str()
			, L"..\\Resources\\mainscreen.bmp");
		render->SetRenderType(ERenderType::StretchBlt);
		render->SetOwner(rectangle);
	}
	
	UI* start_btn = GameObject::Instantiate<UI>(L"MenuStartBTNT", Vector2{ 400,90 }, rectangle);
	{
		Transform* tf = start_btn->GetComponent<Transform>();
		tf->SetSize(Vector2{ 700,500 });
		start_btn->SetImage(start_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Start\\Start.bmp");
		SpriteRenderer* render = start_btn->GetComponent<SpriteRenderer>();
		render->SetRenderType(ERenderType::TransParentBlt);

		//start_btn->SetClickEvent(std::bind(&SceneManager::LoadScene, (UINT)ESceneType::PlayMap));
	}

	UI* end_btn = GameObject::Instantiate<UI>(L"MenuEndBTNT", Vector2{ 400,210 }, rectangle);
	{
		Transform* tf = end_btn->GetComponent<Transform>();
		tf->SetSize(Vector2{ 700,500 });
		end_btn->SetImage(end_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Exit\\Exit.bmp");
		SpriteRenderer* render = end_btn->GetComponent<SpriteRenderer>();
		render->SetRenderType(ERenderType::TransParentBlt);
	}

	UI* options_btn = GameObject::Instantiate<UI>(L"MenuOptionsBTNT", Vector2{ 400,150 }, rectangle);
	{
		Transform* tf = options_btn->GetComponent<Transform>();
		tf->SetSize(Vector2{ 700,500 });
		options_btn->SetImage(options_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Options\\Options.bmp");
		SpriteRenderer* render = options_btn->GetComponent<SpriteRenderer>();
		render->SetRenderType(ERenderType::TransParentBlt);
		//start_btn->SetClickEvent(std::bind(&WindowManager::ActiveWindow, (UINT)EWindowType::Options));
	}
#pragma endregion

	//layer 추가
	//layer init 돌리기.
	Scene::Initialize();
}

void yeram_client::MainMenuScene::Update()
{
	if (core::Input::GetKeyDown(core::EKeyCode::MouseLeft))
	{
		SceneManager::LoadScene(ESceneType::PlayMap);
	}

	Scene::Update();
}

void yeram_client::MainMenuScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void yeram_client::MainMenuScene::Release()
{
	Scene::Release();
}

void yeram_client::MainMenuScene::OnEnter()
{
}

void yeram_client::MainMenuScene::OnExit()
{
	Scene::OnExit();
}

