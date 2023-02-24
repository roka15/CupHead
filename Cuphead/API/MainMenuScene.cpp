#include "MainMenuScene.h"
#include "BackGroundObject.h"
#include "Application.h"

extern yeram_client::Application application;
yeram_client::MainMenuScene::MainMenuScene()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();

	Vector2 size = application.GetWindowSize();

	BackGroundObject* background
		= new BackGroundObject
		(L"BackGround"
			, L"..\\Resources\\mainscreen.bmp"
			, ERenderType::StretchBlt
			, Vector2{ 0,0 }
	, Vector2{ (long)size.x, (long)size.y });

	mLayers[(UINT)ELayerType::BackObject]->AddGameObject(background);
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
		mLayers[i]->Initalize();
	}
}

void yeram_client::MainMenuScene::Update()
{
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
	for (UINT i = (UINT)ELayerType::NONE + 1; i < (UINT)ELayerType::MAX; i++)
	{
		if (mLayers[i] == nullptr)
			continue;
		mLayers[i]->Release();
	}
}

void yeram_client::MainMenuScene::OnEnter()
{
}

void yeram_client::MainMenuScene::OnExit()
{
}
