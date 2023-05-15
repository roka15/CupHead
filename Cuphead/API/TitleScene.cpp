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
	mCurType = ESceneType::Title;
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
	/*std::shared_ptr<GameObject> player_obj = core::ObjectPool<Player>::Spawn();
	{
		player_obj->SetName(L"Player");
		Transform* tf = player_obj->GetComponent<Transform>();
		tf->SetPos(Vector2{ pos.x,pos.y });
		

		std::shared_ptr<GameObject> player_reg = core::ObjectPool<Animator>::Spawn();
		player_reg->SetName(L"Reg");
		player_obj->AddChild(player_reg);
		std::shared_ptr<GameObject> player_head = core::ObjectPool<Animator>::Spawn();
		player_head->SetName(L"Head");
		player_obj->AddChild(player_head);

		std::shared_ptr<GameObject> player_shooter = core::ObjectPool<Animator>::Spawn();
		player_shooter->SetName(L"Shooter");
		player_obj->AddChild(player_shooter);

		Player* player = player_obj->GetComponent<Player>();
		player->CreateCharacter(EPlayerType::MsChalice);
		player->CreateCharacter(EPlayerType::Cuphead);
		player_obj->SetActive(false);

		AddGameObject(player_obj, ELayerType::Player);
	}*/
	
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

	Sound* sound = Resources::Load<Sound>(L"title_sound", L"..\\Resources\\AudioSource\\AudioClip\\mus_dlc_title.wav");
	sound->Play(true);
	std::shared_ptr<GameObject> title = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		title->SetName(L"TitleBackGround");
	

		Transform* tf = title->GetComponent<Transform>();
		tf->SetSize(Vector2{ (long)size.x, (long)size.y });

		SpriteRenderer* render = title->GetComponent<SpriteRenderer>();
		render->SetImage(title->GetName()
			, L"..\\Resources\\title_screen\\Background\\title_screen_background.bmp");
		render->SetRenderType(ERenderType::StretchBlt);
		AddGameObject(title, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> ground = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		ground->SetName(L"TitleGround");
		

		Transform* tf = ground->GetComponent<Transform>();
		tf->SetPos(Vector2{ 0l,(long)size.y - 280 });
		tf->SetSize(Vector2{ (long)size.x,280l });
		SpriteRenderer* render = ground->GetComponent<SpriteRenderer>();
		render->SetImage(ground->GetName()
			, L"..\\Resources\\title_screen\\DLC\\title_chips_left_0001.bmp");
		render->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(ground, ELayerType::FrontObject);
	}
	std::shared_ptr<GameObject> playobj1 = core::ObjectPool<Animator>::Spawn();
	{
		Transform* tf = playobj1->GetComponent<Transform>();
		tf->SetPos(Vector2{ 400,680 });
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj1->GetComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Cuphead", Vector2::Zero, 0.07f);
		
		ani->Play(key, true);

		playobj1->SetName(key);
		AddGameObject(playobj1, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> playobj2 = core::ObjectPool<Animator>::Spawn();
	{
		
		Transform* tf = playobj2->GetComponent<Transform>();
		tf->SetPos(Vector2{ 775,750 });
		tf->SetSize(Vector2{ 400l, 500l });

		Animator* ani = playobj2->GetComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Ms Chalice", Vector2::Zero, 0.07f);
	
		ani->Play(key, true);
		playobj2->SetName(key);
		AddGameObject(playobj2, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> playobj3 = core::ObjectPool<Animator>::Spawn();
	{
	
		Transform* tf = playobj3->GetComponent<Transform>();
		tf->SetPos(Vector2{ 1150,700 });
		tf->SetSize(Vector2{ 400l, 500l });
		Animator* ani = playobj3->GetComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Mugman", Vector2::Zero, 0.07f);
		
		ani->Play(key, true);
		playobj3->SetName(key);
		AddGameObject(playobj3, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> text = core::ObjectPool<Animator>::Spawn();
	{
		
		Transform* tf = text->GetComponent<Transform>();
		tf->SetPos(Vector2{ 900,850 });
		tf->SetScale(Vector2{ 2.0f,2.0f });
		tf->SetSize(Vector2{ 800l, 700l });
		Animator* ani = text->GetComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\title_screen\\DLC\\Text", Vector2::Zero, 0.5f);

		ani->Play(key, true);
		text->SetName(key);
		AddGameObject(text, ELayerType::FrontObject);
	}

	Scene::OnEnter();
}

void yeram_client::TitleScene::OnExit()
{
	Sound* sound = Resources::Find<Sound>(L"title_sound");
	sound->Stop(true);
	Scene::OnExit();
}
