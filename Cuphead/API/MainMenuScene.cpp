#include "MainMenuScene.h"
#include "Rectangle.h"
#include "Application.h"
#include "SceneManager.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "Transform.h"

extern yeram_client::Application application;
yeram_client::MainMenuScene::MainMenuScene()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();

	Vector2 size = application.GetWindowSize();

	Rectangle* rectangle = new Rectangle();

	Transform* tf = rectangle->GetComponent<Transform>();
	tf->SetPos(Vector2{ 0,0 });
	tf->SetSize(Vector2{ (long)size.x,(long)size.y });

	SpriteRenderer* render = rectangle->AddComponent<SpriteRenderer>();
	render->SetImage(L"MenuBackGround"
		, L"..\\Resources\\mainscreen.bmp");
	render->SetRenderType(ERenderType::StretchBlt);
	render->SetOwner(rectangle);

	AddGameObject(rectangle, ELayerType::BackObject);
}

yeram_client::MainMenuScene::~MainMenuScene()
{
}

void yeram_client::MainMenuScene::Initialize()
{
	//layer 추가
	//layer init 돌리기.
	for (UINT i = (UINT)ELayerType::NONE + 1; i < (UINT)ELayerType::MAX; i++)
	{
		if (mLayers[i] == nullptr)
			continue;
		mLayers[i]->Initialize();
	}
}

void yeram_client::MainMenuScene::Update()
{
	if (core::Input::GetKeyDown(core::EKeyCode::MouseLeft))
	{
		OnExit();
		SceneManager::LoadScene(ESceneType::PlayMap);
	}
	Scene::Update();

	for (UINT i = (UINT)ELayerType::NONE + 1; i < (UINT)ELayerType::MAX; i++)
	{
		if (mLayers[i] == nullptr)
			continue;
		mLayers[i]->Update();
	}
}

void yeram_client::MainMenuScene::Render(HDC hdc)
{
	
	for (UINT i = (UINT)ELayerType::NONE + 1; i < (UINT)ELayerType::MAX; i++)
	{
		if (mLayers[i] == nullptr)
			continue;
		mLayers[i]->Render(hdc);
	}
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
