#include "SaltBakeryShopScene.h"
#include "Layer.h"
#include "Player.h"
#include "PixelCrash.h"
#include "Ground.h"
#include "CutScenePlayAnimation.h"
#include "Character.h"
#include "GameObject.h"
#include "Camera.h"
#include "ObjectPool.h"
#include "ColliderManager.h"
#include "Application.h"
#include "Resources.h"
extern yeram_client::Application application;
yeram_client::SaltBakeryShopScene::SaltBakeryShopScene()
{
	mCurType = ESceneType::SaltBakeryShop;
}

yeram_client::SaltBakeryShopScene::SaltBakeryShopScene(std::wstring _name)
{
	mCurType = ESceneType::SaltBakeryShop;
	SetName(_name);
}

yeram_client::SaltBakeryShopScene::~SaltBakeryShopScene()
{
}

void yeram_client::SaltBakeryShopScene::Initialize()
{
	mLayers[(UINT)ELayerType::BackObject] = new Layer();
	mLayers[(UINT)ELayerType::BackColObject] = new Layer();
	mLayers[(UINT)ELayerType::FrontObject] = new Layer();
	mLayers[(UINT)ELayerType::Player] = new Layer();
	mCurSceneNum = 0;
	Scene::Initialize();
}

void yeram_client::SaltBakeryShopScene::Update()
{
	if (mCurSceneNum == 1)
	{
		Camera::SetVerticalMove(false);

		Vector2 player_move_offset = mPlayer->GetComponent<Player>()->GetMoveOffset();
		mWindowPos.x += player_move_offset.x;
		if (mWindowPos.x >= application.GetWindowSize().x / 2)
		{
			if (mWindowPos.x >= (application.GetWindowSize().x / 2) * 4)
			{
				Camera::SetTarget(nullptr);
			}
			else
			{
				Camera::SetTarget(mPlayer.get());
			}
		}
		else
		{
			Camera::SetTarget(nullptr);
		}

	}

	Scene::Update();
}

void yeram_client::SaltBakeryShopScene::Render(HDC hdc)
{

	Scene::Render(hdc);
}

void yeram_client::SaltBakeryShopScene::Release()
{
	mPlayer.reset();
	Scene::Release();
}

void yeram_client::SaltBakeryShopScene::OnEnter()
{
	Scene::OnEnter();
	ColliderManager::SetLayer(ELayerType::Player, ELayerType::BackColObject, true);
	mPlayer = mLayers[(UINT)ELayerType::Player]->FindObject(L"Player");
	Player* player = mPlayer->GetComponent<Player>();
	player->ChangeCharacter(EPlayerType::MsChalice);
	player->GetActiveCharacter()->Initialize();

	Transform* tf = mPlayer->GetComponent<Transform>();

	Rigidbody* rigd = mPlayer->GetComponent<Rigidbody>();
	rigd->Use_Gravity(true);
	rigd->SetGround(true);
	rigd->SetMass(1.0f);

	Camera::SetTarget(nullptr);

	Sound* sound = Resources::Load<Sound>(L"shop_enter_bell_sound", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_WorldMap_BoatTravelAccept.wav");
	sound->Play(false);

	Sound* skip_sound = Resources::Load<Sound>(L"shop_skip_sound", L"..\\Resources\\AudioSource\\AudioClip\\mus_dlc_kitchen_skip.wav");
	skip_sound->Play(true);
	std::shared_ptr<GameObject> bg = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		bg->SetName(L"sbshop_bg");
		bg->SetCameraMoveActive(false);
		Transform* tf = bg->GetComponent<Transform>();
		tf->SetSize(application.GetWindowSize());
		SpriteRenderer* sprite = bg->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_bg", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\12-bakery_bg_main.bmp");
		sprite->SetRenderType(ERenderType::StretchBlt);
		AddGameObject(bg, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> portal = core::ObjectPool<Collider>::Spawn();
	{
		portal->SetName(L"sbshop_portal");
		Transform* tf = portal->GetComponent<Transform>();
		tf->SetPos(Vector2{ 1100.0f,800.0f });
		Collider* col = portal->GetComponent<Collider>();
		col->SetSize(Vector2{ 300.0f,100.0f });
		col->GetEnterEvent() = std::bind([this]()->void
		{
			ActiveScene1();
		});
		AddGameObject(portal, ELayerType::BackColObject);
	}

	std::shared_ptr<GameObject> front_obj = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		front_obj->SetName(L"sbshop_frontobj");
		Transform* tf = front_obj->GetComponent<Transform>();
		tf->SetPos(Vector2{ -150.0f,570.0f });
		tf->SetScale(Vector2{ 1.2f,1.3f });
		SpriteRenderer* sprite = front_obj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_frontobj", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\01-bakery_bg_foreground.bmp");
		sprite->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(front_obj, ELayerType::FrontObject);
	}
	std::shared_ptr<GameObject> ground_col = core::ObjectPool<Ground>::Spawn();
	{
		ground_col->SetName(L"sbshop_ground");
		ground_col->GetComponent<Collider>()->SetSize(Vector2{ (application.GetWindowSize().x / 2) + 400.0f,100.0f });
		ground_col->GetComponent<Transform>()->SetPos(Vector2{ 0.0f,700.0f });
		AddGameObject(ground_col, ELayerType::BackColObject);
	}
	std::shared_ptr<GameObject> stairs_col = core::ObjectPool<Ground>::Spawn();
	{
		stairs_col->SetActive(false);
		stairs_col->SetName(L"cellar_stairs_col_ground");
		stairs_col->GetComponent<Collider>()->SetSize(Vector2{ 150.0f,80.0f });
		stairs_col->GetComponent<Transform>()->SetPos(Vector2{ 50.0f,500.0f });
		AddGameObject(stairs_col, ELayerType::BackColObject);
	}
	std::shared_ptr<GameObject> stairs_col2 = core::ObjectPool<Ground>::Spawn();
	{
		stairs_col2->SetActive(false);
		stairs_col2->SetName(L"cellar_stairs_col_ground2");
		stairs_col2->GetComponent<Collider>()->SetSize(Vector2{ 150.0f,80.0f });
		stairs_col2->GetComponent<Transform>()->SetPos(Vector2{ 150.0f,600.0f });
		AddGameObject(stairs_col2, ELayerType::BackColObject);
	}
	std::shared_ptr<GameObject> stairs_col3 = core::ObjectPool<Ground>::Spawn();
	{
		stairs_col3->SetActive(false);
		stairs_col3->SetName(L"cellar_stairs_col_ground3");
		stairs_col3->GetComponent<Collider>()->SetSize(Vector2{ 150.0f,80.0f });
		stairs_col3->GetComponent<Transform>()->SetPos(Vector2{ 220.0f,650.0f });
		AddGameObject(stairs_col3, ELayerType::BackColObject);
	}
	std::shared_ptr<GameObject> stairs_col4 = core::ObjectPool<Ground>::Spawn();
	{
		stairs_col4->SetActive(false);
		stairs_col4->SetName(L"cellar_stairs_col_ground4");
		stairs_col4->GetComponent<Collider>()->SetSize(Vector2{ 150.0f,80.0f });
		stairs_col4->GetComponent<Transform>()->SetPos(Vector2{ 300.0f,700.0f });
		AddGameObject(stairs_col4, ELayerType::BackColObject);
	}

	std::shared_ptr<GameObject> stairs_col5 = core::ObjectPool<Ground>::Spawn();
	{
		stairs_col5->SetActive(false);
		stairs_col5->SetName(L"cellar_stairs_col_ground5");
		stairs_col5->GetComponent<Collider>()->SetSize(Vector2{ 150.0f,80.0f });
		stairs_col5->GetComponent<Transform>()->SetPos(Vector2{ (application.GetWindowSize().x / 2) * 4.0f + 300.0f, 600.0f });
		AddGameObject(stairs_col5, ELayerType::BackColObject);
	}

	std::shared_ptr<GameObject> stairs_col6 = core::ObjectPool<Ground>::Spawn();
	{
		stairs_col6->SetActive(false);
		stairs_col6->SetName(L"cellar_stairs_col_ground6");
		stairs_col6->GetComponent<Collider>()->SetSize(Vector2{ 400.0f,80.0f });
		stairs_col6->GetComponent<Transform>()->SetPos(Vector2{ (application.GetWindowSize().x / 2) * 4.0f + 500.0f, 550.0f });
		AddGameObject(stairs_col6, ELayerType::BackColObject);
	}
	std::shared_ptr<GameObject> bg2 = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		bg2->SetActive(false);
		bg2->SetName(L"sbshop_cellar_wall_bg");
		Transform* tf = bg2->GetComponent<Transform>();
		tf->SetPos(Vector2{ 40.0f,20.0f });
		tf->SetScale(Vector2{ 2.0f,1.7f });

		SpriteRenderer* sprite = bg2->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_cellar_wall_bg", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\hall_bg_wall.bmp");
		sprite->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(bg2, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> bg3 = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		bg3->SetActive(false);
		bg3->SetName(L"sbshop_cellar_floor_bg");
		Transform* tf = bg3->GetComponent<Transform>();
		tf->SetPos(Vector2{ -20.0f,-20.0f });
		tf->SetScale(Vector2{ 2.2f,2.6f });
		SpriteRenderer* sprite = bg3->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_cellar_floor_bg", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\hall_mg_main_floor_pillars.bmp");
		sprite->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(bg3, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> finish = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		finish->SetActive(false);
		finish->SetName(L"sbshop_cellar_lair_bg");
		Transform* tf = finish->GetComponent<Transform>();
		tf->SetPos(Vector2{ (application.GetWindowSize().x / 2) * 4.0f - 300.0f,-20.0f });
		tf->SetScale(Vector2{ 1.0f,1.2f });
		SpriteRenderer* sprite = finish->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_cellar_lair_bg", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\hall_mg_lair.bmp");
		sprite->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(finish, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> stairs = core::ObjectPool<SpriteRenderer>::Spawn();
	{
		stairs->SetActive(false);
		stairs->SetName(L"sbshop_cellar_stairs_bg");
		Transform* tf = stairs->GetComponent<Transform>();
		tf->SetPos(Vector2{ -5.0f,-10.0f });
		tf->SetScale(Vector2{ 1.0f,1.2f });
		SpriteRenderer* sprite = stairs->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_cellar_stairs_bg", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\hall_mg_stairs.bmp");
		sprite->SetRenderType(ERenderType::TransParentBlt);
		AddGameObject(stairs, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> saltaniobj = core::ObjectPool<CutScenePlayAnimation>::Spawn();
	{
		saltaniobj->SetActive(false);
		saltaniobj->SetName(L"cellarsaltshadow");
		Animator* ani = saltaniobj->GetComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_salt_shadow\\intro", Vector2::Zero, 0.1f);
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_salt_shadow\\intro2", Vector2::Zero, 0.5f);
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_salt_shadow\\loop", Vector2::Zero, 0.1f);
		CutScenePlayAnimation* cutscene = saltaniobj->GetComponent<CutScenePlayAnimation>();
		cutscene->SetAnimation(L"cellar_salt_shadowintro", 10.0f);
		cutscene->SetAnimation(L"cellar_salt_shadowintro2", 0.0f);
		cutscene->SetAnimation(L"cellar_salt_shadowloop", 10.0f);
		Transform* tf = saltaniobj->GetComponent<Transform>();
		tf->SetPos(Vector2{ (application.GetWindowSize().x / 2) * 4.0f + 500.0f,520.0f });
		AddGameObject(saltaniobj, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> flameaniobj1 = core::ObjectPool<Animator>::Spawn();
	{
		flameaniobj1->SetActive(false);
		flameaniobj1->SetName(L"cellarflame1");
		Animator* ani = flameaniobj1->GetComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_flame\\1", Vector2::Zero, 0.1f);
		ani->Play(L"cellar_flame1", true);
		Transform* tf = flameaniobj1->GetComponent<Transform>();
		tf->SetPos(Vector2{ 740.0f,390.0f });
		AddGameObject(flameaniobj1, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> flameaniobj2 = core::ObjectPool<Animator>::Spawn();
	{
		flameaniobj2->SetActive(false);
		flameaniobj2->SetName(L"cellarflame2");
		Animator* ani = flameaniobj2->GetComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_flame\\2", Vector2::Zero, 0.1f);
		ani->Play(L"cellar_flame2", true);
		Transform* tf = flameaniobj2->GetComponent<Transform>();
		tf->SetPos(Vector2{ 1390.0f,390.0f });
		AddGameObject(flameaniobj2, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> flameaniobj3 = core::ObjectPool<Animator>::Spawn();
	{
		flameaniobj3->SetActive(false);
		flameaniobj3->SetName(L"cellarflame3");
		Animator* ani = flameaniobj3->GetComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_flame\\1", Vector2::Zero, 0.1f);
		ani->Play(L"cellar_flame1", true);
		Transform* tf = flameaniobj3->GetComponent<Transform>();
		tf->SetPos(Vector2{ 2025.0f,390.0f });
		AddGameObject(flameaniobj3, ELayerType::BackObject);
	}
	std::shared_ptr<GameObject> flameaniobj4 = core::ObjectPool<Animator>::Spawn();
	{
		flameaniobj4->SetActive(false);
		flameaniobj4->SetName(L"cellarflame4");
		Animator* ani = flameaniobj4->GetComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\cellar_flame\\2", Vector2::Zero, 0.1f);
		ani->Play(L"cellar_flame2", true);
		Transform* tf = flameaniobj4->GetComponent<Transform>();
		tf->SetPos(Vector2{ 2640.0f,390.0f });
		AddGameObject(flameaniobj4, ELayerType::BackObject);
	}

}

void yeram_client::SaltBakeryShopScene::OnExit()
{
	ColliderManager::SetLayer(ELayerType::Player, ELayerType::BackColObject, false);
	Scene::OnExit();
}

void yeram_client::SaltBakeryShopScene::ActiveScene1()
{
	mCurSceneNum = 1;
	Transform* tf = mPlayer->GetComponent<Transform>();
	tf->SetPos(Vector2{ 100.0f,400.0f });
	mWindowPos = tf->GetPos();

	Sound* sound = Resources::Find<Sound>(L"shop_skip_sound");
	sound->Stop(true);

	Sound* base_sound = Resources::Load<Sound>(L"shop_base_sound", L"..\\Resources\\AudioSource\\AudioClip\\mus_dlc_kitchen_basement.wav");
	base_sound->Play(true);

	std::shared_ptr<GameObject> ground_col = FindObject(L"sbshop_ground");
	{
		ground_col->GetComponent<Collider>()->SetSize(Vector2{ (application.GetWindowSize().x / 2) * 5.0f,100.0f });
		ground_col->GetComponent<Transform>()->SetPos(Vector2{ 0.0f,750.0f });
	}
	std::shared_ptr<GameObject> stairs_col1 = FindObject(L"cellar_stairs_col_ground");
	{
		stairs_col1->SetActive(true);
	}
	std::shared_ptr<GameObject> stairs_col2 = FindObject(L"cellar_stairs_col_ground2");
	{
		stairs_col2->SetActive(true);
	}
	std::shared_ptr<GameObject> stairs_col3 = FindObject(L"cellar_stairs_col_ground3");
	{
		stairs_col3->SetActive(true);
	}
	std::shared_ptr<GameObject> stairs_col4 = FindObject(L"cellar_stairs_col_ground4");
	{
		stairs_col4->SetActive(true);
	}
	std::shared_ptr<GameObject> stairs_col5 = FindObject(L"cellar_stairs_col_ground5");
	{
		stairs_col5->SetActive(true);
	}
	std::shared_ptr<GameObject> stairs_col6 = FindObject(L"cellar_stairs_col_ground6");
	{
		stairs_col6->SetActive(true);
	}
	std::shared_ptr<GameObject> flame1 = FindObject(L"cellarflame1");
	{
		flame1->SetActive(true);
	}
	std::shared_ptr<GameObject> flame2 = FindObject(L"cellarflame2");
	{
		flame2->SetActive(true);
	}
	std::shared_ptr<GameObject> flame3 = FindObject(L"cellarflame3");
	{
		flame3->SetActive(true);
	}
	std::shared_ptr<GameObject> flame4 = FindObject(L"cellarflame4");
	{
		flame4->SetActive(true);
	}
	std::shared_ptr<GameObject> bg2 = FindObject(L"sbshop_cellar_wall_bg");
	{
		bg2->SetActive(true);
	}
	std::shared_ptr<GameObject> bg3 = FindObject(L"sbshop_cellar_floor_bg");
	{
		bg3->SetActive(true);
	}
	std::shared_ptr<GameObject> finish = FindObject(L"sbshop_cellar_lair_bg");
	{
		finish->SetActive(true);
	}
	std::shared_ptr<GameObject> stairs = FindObject(L"sbshop_cellar_stairs_bg");
	{
		stairs->SetActive(true);
	}
	std::shared_ptr<GameObject> portal = FindObject(L"sbshop_portal");
	{
		Collider* col = portal->GetComponent<Collider>();
		col->GetEnterEvent() = std::bind([]()->void
		{
			//salt baker ani scene 넘어가기.
			SceneManager::SetLoadSceneMessage(std::bind([]()->void
			{
				SceneManager::LoadScene(ESceneType::SaltBakerBossIntro);
			}));
		}
		);

		Transform* tf = portal->GetComponent<Transform>();
		tf->SetPos(Vector2{ (application.GetWindowSize().x / 2) * 4.0f + 650.0f ,450.0f });
		portal->GetComponent<Collider>()->SetSize(Vector2{ 80.0f,80.0f });
	}
	std::shared_ptr<GameObject> bg1 = FindObject(L"sbshop_bg");
	{
		SpriteRenderer* sprite = bg1->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_cellar_dark_bg", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\Cellar\\hall_bg_darkness.bmp");
	}



	std::shared_ptr<GameObject> frontobj = FindObject(L"sbshop_frontobj");
	{
		frontobj->SetActive(false);
		SpriteRenderer* sprite = frontobj->GetComponent<SpriteRenderer>();
		sprite->SetImage(L"sbshop_frontobj", L"..\\Resources\\scene\\dlc\\salt_baker_shop_scene\\01-bakery_bg_foreground.bmp");
	}
	std::shared_ptr<GameObject> shadowsalt = FindObject(L"cellarsaltshadow");
	{
		shadowsalt->SetActive(true);
	}
}
