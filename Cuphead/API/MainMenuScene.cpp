#include "MainMenuScene.h"
#include "Rectangle.h"

#include "Application.h"
#include "SceneManager.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Layer.h"
#include "UI.h"
#include "ObjectPool.h"
//#include "WindowManager.h"

extern yeram_client::Application application;
yeram_client::MainMenuScene::MainMenuScene()
{
	mCurType = ESceneType::MainMenu;
}

yeram_client::MainMenuScene::~MainMenuScene()
{
}

yeram_client::MainMenuScene::MainMenuScene(std::wstring _name)
{
	mCurType = ESceneType::MainMenu;
	SetName(_name);
}

void yeram_client::MainMenuScene::Initialize()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();
	mLayers[(UINT)ELayerType::UI] = new Layer();
	mLayers[(UINT)ELayerType::Player] = new Layer();
	
	//WindowManager::ActiveWindow((UINT)EWindowType::MainMenu);
	//OnEnter();

}

void yeram_client::MainMenuScene::Update()
{
	if (core::Input::GetKeyDown(core::EKeyCode::MouseLeft))
	{
		SceneManager::LoadScene(ESceneType::MoveWorldIntro);
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
#pragma region main menu window
	Vector2 size = application.GetWindowSize();
	std::shared_ptr<GameObject> rectangle = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		rectangle->SetName(L"MenuBackGround");

		
		Transform* tf = rectangle->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x,(long)size.y });

		SpriteRenderer* render = rectangle->AddComponent<SpriteRenderer>();
		render->SetImage(rectangle->GetName().c_str()
			, L"..\\Resources\\mainscreen.bmp");
		render->SetRenderType(ERenderType::StretchBlt);
		render->SetOwner(rectangle.get());
		AddGameObject(rectangle, ELayerType::BackObject);
	}

	std::shared_ptr<GameObject> start_btn = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		start_btn->SetName(L"MenuStartBTNT");
		//start_btn->SetParent(rectangle.get());
	

		Transform* tf = start_btn->GetComponent<Transform>();
		tf->SetPos(Vector2{ 400,90 });
		tf->SetSize(Vector2{ 700,500 });
		
		SpriteRenderer* render = start_btn->GetComponent<SpriteRenderer>();
		render->SetImage(start_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Start\\Start.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
		//start_btn->SetClickEvent(std::bind(&SceneManager::LoadScene, (UINT)ESceneType::PlayMap));
		AddGameObject(start_btn, ELayerType::UI);
	}

	std::shared_ptr<GameObject> end_btn = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		end_btn->SetName(L"MenuEndBTNT");
		//end_btn->SetParent(rectangle.get());
		

		Transform* tf = end_btn->GetComponent<Transform>();
		tf->SetPos(Vector2{ 400,210 });
		tf->SetSize(Vector2{ 700,500 });
	
		SpriteRenderer* render = end_btn->GetComponent<SpriteRenderer>();
		render->SetImage(end_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Exit\\Exit.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(end_btn, ELayerType::UI);
	}

	std::shared_ptr<GameObject> options_btn = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		options_btn->SetName(L"MenuOptionsBTNT");
		//options_btn->SetParent(rectangle.get());
		

		Transform* tf = options_btn->GetComponent<Transform>();
		tf->SetPos(Vector2{ 400,150 });
		tf->SetSize(Vector2{ 700,500 });
		
		SpriteRenderer* render = options_btn->GetComponent<SpriteRenderer>();
		render->SetImage(options_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Options\\Options.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
		//start_btn->SetClickEvent(std::bind(&WindowManager::ActiveWindow, (UINT)EWindowType::Options));
		AddGameObject(options_btn, ELayerType::UI);
	}

	//rectangle->AddChild(start_btn);
	//rectangle->AddChild(end_btn);
	//rectangle->AddChild(options_btn);

#pragma endregion
	Scene::OnEnter();
}

void yeram_client::MainMenuScene::OnExit()
{
	Scene::OnExit();
}

