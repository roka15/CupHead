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
#pragma region main menu window
	Vector2 size = application.GetWindowSize();
	//std::shared_ptr<Rectangle> rectangle = core::ObjectPool<Rectangle>::Spawn();
	//{
	//	rectangle->SetName(L"MenuBackGround");

	//	AddGameObject(rectangle, ELayerType::BackObject);
	//	Transform* tf = rectangle->GetComponent<Transform>();
	//	tf->SetSize(Vector2{ (long)size.x,(long)size.y });

	//	SpriteRenderer* render = rectangle->AddComponent<SpriteRenderer>();
	//	render->SetImage(rectangle->GetName().c_str()
	//		, L"..\\Resources\\mainscreen.bmp");
	//	render->SetRenderType(ERenderType::StretchBlt);
	//	render->SetOwner(rectangle.get());
	//}

	//std::shared_ptr<UI> start_btn = core::ObjectPool<UI>::Spawn();
	//{
	//	start_btn->SetName(L"MenuStartBTNT");
	//	start_btn->SetParent(rectangle.get());
	//	AddGameObject(start_btn, ELayerType::UI);

	//	Transform* tf = start_btn->GetComponent<Transform>();
	//	tf->SetPos(Vector2{ 400,90 });
	//	tf->SetSize(Vector2{ 700,500 });
	//	start_btn->SetImage(start_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Start\\Start.bmp");
	//	SpriteRenderer* render = start_btn->GetComponent<SpriteRenderer>();
	//	render->SetRenderType(ERenderType::TransParentBlt);
	//	//start_btn->SetClickEvent(std::bind(&SceneManager::LoadScene, (UINT)ESceneType::PlayMap));
	//}

	//std::shared_ptr<UI> end_btn = core::ObjectPool<UI>::Spawn();
	//{
	//	end_btn->SetName(L"MenuEndBTNT");
	//	end_btn->SetParent(rectangle.get());
	//	AddGameObject(end_btn, ELayerType::UI);

	//	Transform* tf = end_btn->GetComponent<Transform>();
	//	tf->SetPos(Vector2{ 400,210 });
	//	tf->SetSize(Vector2{ 700,500 });
	//	end_btn->SetImage(end_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Exit\\Exit.bmp");
	//	SpriteRenderer* render = end_btn->GetComponent<SpriteRenderer>();
	//	render->SetRenderType(ERenderType::TransParentBlt);
	//}

	//std::shared_ptr<UI> options_btn = core::ObjectPool<UI>::Spawn();
	//{
	//	options_btn->SetName(L"MenuOptionsBTNT");
	//	options_btn->SetParent(rectangle.get());
	//	AddGameObject(options_btn, ELayerType::UI);

	//	Transform* tf = options_btn->GetComponent<Transform>();
	//	tf->SetPos(Vector2{ 400,150 });
	//	tf->SetSize(Vector2{ 700,500 });
	//	options_btn->SetImage(options_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Options\\Options.bmp");
	//	SpriteRenderer* render = options_btn->GetComponent<SpriteRenderer>();
	//	render->SetRenderType(ERenderType::TransParentBlt);
	//	//start_btn->SetClickEvent(std::bind(&WindowManager::ActiveWindow, (UINT)EWindowType::Options));
	//}

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

