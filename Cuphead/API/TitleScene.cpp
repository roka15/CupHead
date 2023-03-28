#include "TitleScene.h"
#include "Input.h"
#include "SceneManager.h"
#include "Image.h"
#include "Resources.h"
#include "Application.h"
#include "Rectangle.h"
#include "Player.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Animator.h"
#include "Layer.h"
#include "ObjectPool.h"
extern yeram_client::Application application;

yeram_client::TitleScene::TitleScene()
{
	mCurType = ESceneType::Title;
}

yeram_client::TitleScene::TitleScene(std::wstring _name)
{
	SetName(_name);
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
	Vector2 pos = application.GetWindowSize() / 2.0f;
	//std::shared_ptr<Player> player = core::ObjectPool<Player>::Spawn();
	//{
	//	player->SetName(L"Player");
	//	Transform* tf = player->GetComponent<Transform>();
	//	tf->SetPos(Vector2{ pos.x,pos.y });
	//	AddGameObject(player, ELayerType::Player);

	//	player->CreateCharacter(EPlayerType::MsChalice);
	//	player->CreateCharacter(EPlayerType::Cuphead);
	//	player->SetActive(false);
	//}
}

void yeram_client::TitleScene::Update()
{
	if (core::Input::GetKeyDown(core::EKeyCode::MouseLeft))
	{
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
	Vector2 size = application.GetWindowSize();

	/*std::shared_ptr<Rectangle> title = core::ObjectPool<Rectangle>::Spawn();
	{
		title->SetName(L"TitleBackGround");
		AddGameObject(title, ELayerType::BackObject);

		Transform* tf = title->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x, (long)size.y });

		SpriteRenderer* render = title->AddComponent<SpriteRenderer>();
		render->SetImage(title->GetName().c_str()
			, L"..\\Resources\\title_screen\\Background\\title_screen_background.bmp");
		render->SetRenderType(ERenderType::StretchBlt);
	}
	std::shared_ptr<Rectangle> ground = core::ObjectPool<Rectangle>::Spawn();
	{
		ground->SetName(L"TitleGround");
		AddGameObject(ground, ELayerType::FrontObject);

		Transform* tf = ground->GetComponent<Transform>();
		tf->SetPos(Vector2{ 0l,(long)size.y - 280 });
		tf->SetSize(Vector2{ (long)size.x,280l });
		SpriteRenderer* render = ground->AddComponent<SpriteRenderer>();
		render->SetImage(ground->GetName().c_str()
			, L"..\\Resources\\title_screen\\DLC\\title_chips_left_0001.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
	}
	std::shared_ptr<Rectangle> playobj1 = core::ObjectPool<Rectangle>::Spawn();
	{
		AddGameObject(playobj1, ELayerType::BackObject);

		Transform* tf = playobj1->GetComponent<Transform>();
		tf->SetPos(Vector2{ 400,680 });
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj1->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Cuphead", Vector2::Zero, 0.07f);
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, playobj1.get());
		ani->Play(key, true);

		playobj1->SetName(key);
	}
	std::shared_ptr<Rectangle> playobj2 = core::ObjectPool<Rectangle>::Spawn();
	{
		AddGameObject(playobj2, ELayerType::BackObject);
		Transform* tf = playobj2->GetComponent<Transform>();
		tf->SetPos(Vector2{ 775,750 });
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj2->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Ms Chalice", Vector2::Zero, 0.07f);
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, playobj2.get());
		ani->Play(key, true);
		playobj2->SetName(key);
	}
	std::shared_ptr<Rectangle> playobj3 = core::ObjectPool<Rectangle>::Spawn();
	{
		AddGameObject(playobj3, ELayerType::BackObject);
		Transform* tf = playobj3->GetComponent<Transform>();
		tf->SetPos(Vector2{ 1150,700 });
		tf->SetSize(Vector2{ 400l, 500l });
		Animator* ani = playobj3->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Mugman", Vector2::Zero, 0.07f);
		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, playobj3.get());
		ani->Play(key, true);
		playobj3->SetName(key);
	}
	std::shared_ptr<Rectangle> text = core::ObjectPool<Rectangle>::Spawn();
	{
		AddGameObject(text, ELayerType::FrontObject);
		Transform* tf = text->GetComponent<Transform>();
		tf->SetPos(Vector2{ 650,750 });
		tf->SetScale(Vector2{ 2.0f,2.0f });
		tf->SetSize(Vector2{ 400l, 500l });
		Animator* ani = text->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Text", Vector2::Zero, 0.5f);

		ani->GetStartEvent(key) = std::bind(&Rectangle::aniCompleteEvent, text.get());
		ani->Play(key, true);
		text->SetName(key);
	}*/

	Scene::OnEnter();
}

void yeram_client::TitleScene::OnExit()
{
	Scene::OnExit();
}
