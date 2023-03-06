#include "TitleScene.h"
#include "Input.h"
#include "SceneManager.h"
#include "Image.h"
#include "Resources.h"
#include "Application.h"
#include "BackGroundObject.h"

extern yeram_client::Application application;

yeram_client::TitleScene::TitleScene()
{
	mLayers.resize((UINT)ELayerType::MAX);
	mLayers[(UINT)ELayerType::BackObject] = new Layer();

	Vector2 size = application.GetWindowSize();
	
	/*BackGroundObject* title 
		= new BackGroundObject
		    (L"TitleBackGround"
			,L"..\\Resources\\title_screen\\Background\\title_screen_background.bmp"
	        , ERenderType::StretchBlt
			, Vector2{ 0,0 }
	        , Vector2{ (long)size.x, (long)size.y });
	
	
	BackGroundObject* ground = new BackGroundObject
	(L"Ground"
		, L"..\\Resources\\title_screen\\DLC\\title_chips_left_0001.bmp"
		, ERenderType::TransParentBlt
		, Vector2{ 0l,(long)size.y-280 }
	, Vector2{ (long)size.x,280l });

	BackGroundObject* playobj1 = new BackGroundObject
	(L"PlayImage1"
		, L"..\\Resources\\title_screen\\DLC\\Cuphead\\cuphead_title_screen_0001.bmp"
		, ERenderType::TransParentBlt
		,Vector2{ 170,140 }
		, Vector2{ 400l, 500l });

	BackGroundObject* playobj2 = new BackGroundObject
	(L"PlayImage2"
		, L"..\\Resources\\title_screen\\DLC\\Ms Chalice\\chalice_title_screen_0001.bmp"
		, ERenderType::TransParentBlt
		, Vector2{ 600,210 }
	, Vector2{ 400l, 500l });

	BackGroundObject* playobj3 = new BackGroundObject
	(L"PlayImage3"
		, L"..\\Resources\\title_screen\\DLC\\Mugman\\mugman_title_screen_0001.bmp"
		, ERenderType::TransParentBlt
		, Vector2{ 1000,160 }
	, Vector2{ 400l, 500l });

	AddGameObject(title,ELayerType::BackObject);
	AddGameObject(ground, ELayerType::BackObject);
	AddGameObject(playobj1, ELayerType::BackObject);
	AddGameObject(playobj2, ELayerType::BackObject);
	AddGameObject(playobj3, ELayerType::BackObject);*/
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
	if (core::Input::GetKeyState(core::EKeyCode::MouseLeft) == core::EKeyState::Down)
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
