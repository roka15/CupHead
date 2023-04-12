#include "WorldMoveIntroScene.h"
#include"SceneManager.h"
#include "Layer.h"
#include "ObjectPool.h"
#include "Application.h"
#include "MoveObject.h"
#include "OriginalImagePos.h"
#include "Time.h"
extern yeram_client::Application application;
namespace yeram_client
{
	WorldMoveIntroScene::WorldMoveIntroScene()
	{
		mCurType = ESceneType::MoveWorldIntro;
	}
	WorldMoveIntroScene::WorldMoveIntroScene(std::wstring _name)
	{
		mCurType = ESceneType::MoveWorldIntro;
		SetName(_name);
	}
	WorldMoveIntroScene::~WorldMoveIntroScene()
	{
	}
	void WorldMoveIntroScene::Initialize()
	{
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
	}
	void WorldMoveIntroScene::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 20.0f)
		{
			SceneManager::LoadScene(ESceneType::InWorldIntro);
		}
		Scene::Update();
	}
	void WorldMoveIntroScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void WorldMoveIntroScene::Release()
	{
		Scene::Release();
	}
	void WorldMoveIntroScene::OnEnter()
	{
		Vector2 size = application.GetWindowSize();
		std::shared_ptr<GameObject> background = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			background->SetName(L"moveintro_background");
			Transform* tf = background->GetComponent<Transform>();
			tf->SetSize(size);
			SpriteRenderer* sprite = background->GetComponent<SpriteRenderer>();
			sprite->SetImage(background->GetName(), L"..\\Resources\\worldmove_intro\\bg\\cutscene_intro_s1_sky.bmp");
			sprite->SetRenderType(ERenderType::StretchBlt);
			AddGameObject(background, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> cloud = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			cloud->SetName(L"moveintro_cloud");
			SpriteRenderer* sprite = cloud->GetComponent<SpriteRenderer>();
			sprite->SetImage(cloud->GetName(), L"..\\Resources\\worldmove_intro\\bg\\cutscene_intro_s1_clouds.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(cloud, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg2 = core::ObjectPool<MoveObject>::Spawn();
		{
			bg2->SetName(L"moveintro_bg2");
			Transform* tf = bg2->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.y += 170;
			tf->SetPos(pos);
			tf->SetScale(Vector2{ 1.1f,1.0f });
			SpriteRenderer* sprite = bg2->AddComponent<SpriteRenderer>();
			sprite->SetImage(bg2->GetName(), L"..\\Resources\\worldmove_intro\\bg\\cutscene_intro_s1_mountains.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);

			MoveObject* mv = bg2->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 10.0f,0.0f },EDirType::LEFT);
			AddGameObject(bg2, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> bg_leak= core::ObjectPool<SpriteRenderer>::Spawn();
		{
			bg_leak->SetName(L"moveintro_bg_leak");
			Transform* tf = bg_leak->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.y += 405;
			tf->SetPos(pos);
			tf->SetScale(Vector2{ 1.0f,1.5f });
			SpriteRenderer* sprite = bg_leak->GetComponent<SpriteRenderer>();
			sprite->SetImage(bg_leak->GetName(), L"..\\Resources\\worldmove_intro\\bg\\cutscene_intro_s1_lake.bmp");
			sprite->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(bg_leak, ELayerType::BackObject);
		}

		std::shared_ptr<GameObject> boat = core::ObjectPool<MoveObject>::Spawn();
		{
			boat->SetName(L"worldmove_introboat");
			Transform* tf = boat->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,700.0f });
			
			MoveObject* mv = boat->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{75.0f,0.0f}, EDirType::RIGHT);
			Animator* ani = boat->AddComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\worldmove_intro\\boat", Vector2::Zero, 0.05f, false);
			ani->Play(boat->GetName(), true);
			std::shared_ptr<GameObject> cup_eyes = core::ObjectPool<Animator>::Spawn();
			{
				cup_eyes->SetName(L"worldmove_introcuphead_eye");
				Animator* ani = cup_eyes->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\worldmove_intro\\cuphead_eye", Vector2::Zero, 0.05f, false);
				ani->Play(cup_eyes->GetName(), true);
				Transform* tf = cup_eyes->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 135.0f,-140.0f });
			}
			boat->AddChild(cup_eyes);
			std::shared_ptr<GameObject> mug_eyes = core::ObjectPool<Animator>::Spawn();
			{
				mug_eyes->SetName(L"worldmove_intromug_eye");
				Animator* ani = mug_eyes->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\worldmove_intro\\mug_eye", Vector2::Zero, 0.05f, false);
				ani->Play(mug_eyes->GetName(), true);
				Transform* tf = mug_eyes->GetComponent<Transform>();
				tf->SetOffset(Vector2{ 40.0f,-85.0f });
			}
			boat->AddChild(mug_eyes);
			std::shared_ptr<GameObject> boat_man = core::ObjectPool<Animator>::Spawn();
			{
				boat_man->SetName(L"worldmove_introboatman");
				//OriginalImagePos* oi = boat_man->AddComponent<OriginalImagePos>();
				Animator* ani = boat_man->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\worldmove_intro\\boatman", Vector2::Zero, 0.05f, false);
				ani->Play(boat_man->GetName(), true);
				Transform* tf = boat_man->GetComponent<Transform>();
				tf->SetOffset(Vector2{ -70.0f,30.0f });

				//oi->Initialize();
			}
			boat->AddChild(boat_man);
			AddGameObject(boat, ELayerType::FrontObject);


			std::shared_ptr<GameObject> grass = core::ObjectPool<MoveObject>::Spawn();
			{
				grass->SetName(L"moveintro_bg_grass");

				Transform* tf = grass->GetComponent<Transform>();
				tf->SetPos(Vector2{ 1300.0f,770.0f });
				SpriteRenderer* sprite = grass->AddComponent<SpriteRenderer>();
				sprite->SetImage(grass->GetName(), L"..\\Resources\\worldmove_intro\\bg\\cutscene_intro_s1_fg_grass.bmp");
				sprite->SetRenderType(ERenderType::TransParentBlt);
				
				MoveObject* mv = grass->GetComponent<MoveObject>();
				mv->CreateInfo(Vector2{ 20.0f,0.0f }, EDirType::LEFT);
				AddGameObject(grass, ELayerType::FrontObject);
			}
		}
		
		Scene::OnEnter();
	}
	void WorldMoveIntroScene::OnExit()
	{
		Scene::OnExit();
	}
}