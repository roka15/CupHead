#include "MedusaScene.h"
#include "Layer.h"
#include "Rectangle.h"
#include "Application.h"
#include "Animator.h"
#include "Transform.h"
#include "Resources.h"
#include "Image.h"
#include "Time.h"
#include "MoveObject.h"
#include "Camera.h"
#include "Player.h"
#include "ColliderManager.h"
#include "Ground.h"
#include "SpriteRenderer.h"
#include "ObjectPool.h"
extern yeram_client::Application application;
namespace yeram_client
{
	MedusaScene::MedusaScene() : mTime(0.0f), mYFlag(false)
	{
		mCurType = ESceneType::BossMedusa;
	}
	MedusaScene::MedusaScene(std::wstring _name)
	{
		SetName(_name);
	}
	MedusaScene::~MedusaScene()
	{
	}
	void MedusaScene::Initialize()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::Monster] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
	}

	void MedusaScene::Update()
	{
		GroundUpdate();
		Scene::Update();
	}

	void MedusaScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void MedusaScene::Release()
	{
		GroundInfoRelease();
		Scene::Release();
	}
	void MedusaScene::OnEnter()
	{
		for (auto obj : GetGameObjects(ELayerType::Player))
		{
			Player* player = dynamic_cast<Player*>(obj.get());
			player->ChangeCharacter(EPlayerType::MsChalice);
			player->SetActive(true);
			Transform* tf = player->GetComponent<Transform>();
			tf->SetPos(Vector2{ 200.0f,300.0f });

			Rigidbody* rid = player->GetComponent<Rigidbody>();
			if (rid == nullptr)
				continue;
			rid->SetGround(false);
			rid->SetMass(1.0f);
		}
		ColliderManager::SetLayer(ELayerType::Player, ELayerType::FrontObject, true);

		CreateBackGround();
		CreateGround();
		//temp
		std::shared_ptr<Rectangle> medusa = core::ObjectPool<Rectangle>::Spawn(); 
		AddGameObject(medusa, ELayerType::Monster);
		Transform* tf = medusa->GetComponent<Transform>();
		tf->SetPos(Vector2{ 1300, 800 });
		Animator* ani = medusa->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\MM\\Intro\\MerMaid", Vector2::Zero, 0.1f, false);
		ani->Play(key, true);

		Scene::OnEnter();
	}
	void MedusaScene::OnExit()
	{
		Scene::OnExit();
	}
	void MedusaScene::CreateGround()
	{
		Vector2 center = application.GetWindowSize() / 2.0f;

		std::wstring key;
		std::shared_ptr<Rectangle> water_1 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_1->GetComponent<Transform>();
			tf->SetPos(Vector2{ 50.0f,900.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_1, ELayerType::FrontObject);
			Animator* ani = water_1->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back1", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_1->SetName(key);
			/*Script* script = water_1->AddComponent<Script>();

			script->RegisterScript(typeid(MoveObject).name(), new MoveObject);*/
		}
		std::shared_ptr<Rectangle> water_1_2 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_1_2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 650.f,900.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_1_2, ELayerType::FrontObject);
			Animator* ani = water_1_2->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back1", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_1_2->SetName(key);
		}
		std::shared_ptr<Rectangle> water_1_3 =  core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_1_3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1250.0f,900.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_1_3, ELayerType::FrontObject);
			Animator* ani = water_1_3->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back1", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_1_3->SetName(key);
		}
		std::shared_ptr<Rectangle> water_1_4 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_1_4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1850.0f,900.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_1_4, ELayerType::FrontObject);
			Animator* ani = water_1_4->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back1", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_1_4->SetName(key);
		}
		mGroundsInfo.insert(std::make_pair(key, std::queue<std::shared_ptr<GameObject>>()));
		mGroundsInfo[key].push(water_1);
		mGroundsInfo[key].push(water_1_2);
		mGroundsInfo[key].push(water_1_3);
		mGroundsInfo[key].push(water_1_4);
		mGroundInfos.insert(std::make_pair(key, GroundInfo{ Vector2{590.0f,0.0f},Vector2{4.0f,0.4}}));

		std::shared_ptr<Rectangle> water_2 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 200.0f,950.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_2, ELayerType::FrontObject);
			Animator* ani = water_2->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back3", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_2->SetName(key);
		}
		std::shared_ptr<Rectangle> water_2_2 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_2_2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 880.0f,950.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_2_2, ELayerType::FrontObject);
			Animator* ani = water_2_2->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back3", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_2_2->SetName(key);
		}
		std::shared_ptr<Rectangle> water_2_3 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_2_3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1560.0f,950.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_2_3, ELayerType::FrontObject);
			Animator* ani = water_2_3->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back3", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_2_3->SetName(key);
		}
		std::shared_ptr<Rectangle> water_2_4 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_2_4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 2240.0f,950.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_2_4, ELayerType::FrontObject);
			Animator* ani = water_2_4->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back3", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_2_4->SetName(key);
		}
		mGroundsInfo.insert(std::make_pair(key, std::queue<std::shared_ptr<GameObject>>()));
		mGroundsInfo[key].push(water_2);
		mGroundsInfo[key].push(water_2_2);
		mGroundsInfo[key].push(water_2_3);
		mGroundsInfo[key].push(water_2_4);
		mGroundInfos.insert(std::make_pair(key, GroundInfo{ Vector2{680.0f,0.0f}, Vector2{5.0f,0.4} }));

		std::shared_ptr<Rectangle> water_3 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_3->GetComponent<Transform>();
			tf->SetPos(Vector2{ -50.0f,1030.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_3, ELayerType::FrontObject);
			Animator* ani = water_3->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back4", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_3->SetName(key);
		}
		std::shared_ptr<Rectangle> water_3_2 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_3_2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 750.0f,1030.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_3_2, ELayerType::FrontObject);
			Animator* ani = water_3_2->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back4", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_3_2->SetName(key);
		}
		std::shared_ptr<Rectangle> water_3_3 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_3_3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1550.0f,1030.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_3_3, ELayerType::FrontObject);
			Animator* ani = water_3_3->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back4", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_3_3->SetName(key);
		}
		std::shared_ptr<Rectangle> water_3_4 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_3_4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 2350.0f,1030.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_3_4, ELayerType::FrontObject);
			Animator* ani = water_3_4->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back4", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_3_4->SetName(key);
		}
		mGroundsInfo.insert(std::make_pair(key, std::queue<std::shared_ptr<GameObject>>()));
		mGroundsInfo[key].push(water_3);
		mGroundsInfo[key].push(water_3_2);
		mGroundsInfo[key].push(water_3_3);
		mGroundsInfo[key].push(water_3_4);
		mGroundInfos.insert(std::make_pair(key, GroundInfo{ Vector2{800.0f,0.0f},Vector2{6.5f,0.3}}));

		std::shared_ptr<Rectangle> water_4 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 200.0f,1090.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_4, ELayerType::FrontObject);
			Animator* ani = water_4->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back5", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_4->SetName(key);
		}
		std::shared_ptr<Rectangle> water_4_2 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_4_2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1070.0f,1090.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_4_2, ELayerType::FrontObject);
			Animator* ani = water_4_2->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back5", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_4_2->SetName(key);
		}
		std::shared_ptr<Rectangle> water_4_3 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_4_3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1940.0f,1090.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_4_3, ELayerType::FrontObject);
			Animator* ani = water_4_3->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back5", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_4_3->SetName(key);
		}
		std::shared_ptr<Rectangle> water_4_4 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_4_4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 2810.0f,1090.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_4_4, ELayerType::FrontObject);
			Animator* ani = water_4_4->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back5", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_4_4->SetName(key);
		}
		mGroundsInfo.insert(std::make_pair(key, std::queue<std::shared_ptr<GameObject>>()));
		mGroundsInfo[key].push(water_4);
		mGroundsInfo[key].push(water_4_2);
		mGroundsInfo[key].push(water_4_3);
		mGroundsInfo[key].push(water_4_4);
		mGroundInfos.insert(std::make_pair(key, GroundInfo{ Vector2{860.0f,0.0f},Vector2{8.0f,0.5} }));
		
		std::shared_ptr<Rectangle> water_5 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_5->GetComponent<Transform>();
			tf->SetPos(Vector2{ 362.0f,920.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_5, ELayerType::FrontObject);
			Animator* ani = water_5->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back6", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_5->SetName(key);
		}
		std::shared_ptr<Rectangle> water_5_2 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_5_2->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1230.0f,920.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_5_2, ELayerType::FrontObject);
			Animator* ani = water_5_2->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back6", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_5_2->SetName(key);
		}
		std::shared_ptr<Rectangle> water_5_3 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_5_3->GetComponent<Transform>();
			tf->SetPos(Vector2{ 2098.0f,920.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_5_3, ELayerType::FrontObject);
			Animator* ani = water_5_3->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back6", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_5_3->SetName(key);
		}
		std::shared_ptr<Rectangle> water_5_4 = core::ObjectPool<Rectangle>::Spawn();
		{
			Transform* tf = water_5_4->GetComponent<Transform>();
			tf->SetPos(Vector2{ 2966.0f,920.0f });
			tf->SetScale(Vector2{ 1.2f,1.0f });
			AddGameObject(water_5_4, ELayerType::FrontObject);
			Animator* ani = water_5_4->AddComponent<Animator>();
			key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back6", Vector2::Zero, 0.1f);
			ani->Play(key, true);
			water_5_4->SetName(key);
		}

		std::shared_ptr<Ground> ground_col = core::ObjectPool<Ground>::Spawn();
		{
			Transform* tf = ground_col->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0.0f,100.0f });
			AddGameObject(ground_col, ELayerType::FrontObject);

			Collider* col = ground_col->GetComponent<Collider>();
			col->SetSize(Vector2(center.x * 2.0f, 100.0f));
			col->SetCenter(Vector2(0.0f, 500.0f));
		}

		

		mGroundsInfo.insert(std::make_pair(key, std::queue<std::shared_ptr<GameObject>>()));
		mGroundsInfo[key].push(water_5);
		mGroundsInfo[key].push(water_5_2);
		mGroundsInfo[key].push(water_5_3);
		mGroundsInfo[key].push(water_5_4);
		mGroundInfos.insert(std::make_pair(key, GroundInfo{ Vector2{865.0f,0.0f},Vector2{10.0f,0.4} }));
	}

	void MedusaScene::CreateBackGround()
	{
		std::wstring key;
		std::shared_ptr <Rectangle> background = core::ObjectPool<Rectangle>::Spawn(); 
		{
			AddGameObject(background, ELayerType::BackObject);
			SpriteRenderer* render = background->AddComponent<SpriteRenderer>();
			render->SetImage(L"MedusaMainBackImage", L"..\\Resources\\MM\\BackGround\\MainBackImage\\mermaid_bg_sky_0001.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
			background->SetName(L"MedusaMainBackImage");
		}
	}

	void MedusaScene::GroundUpdate()
	{
		float y = 0;
		mTime += Time::DeltaTime();

		
		if (mTime >= 0.6f)
		{
			mYFlag = !mYFlag;
			mTime = 0.0f;
		}
		

		for (auto ground_queue : mGroundsInfo)
		{
			std::queue<std::shared_ptr<GameObject>>& q = ground_queue.second;
			int i = q.size();
			while (i > 0)
			{
				std::shared_ptr<GameObject> ground = q.front();
				q.pop();
				std::wstring name = ground->GetName();
				Transform* tf = ground->GetComponent<Transform>();
				Vector2 curpos = tf->GetPos();
				curpos.x -= mGroundInfos[name].mSpeed.x;

				if (mYFlag == true)
					curpos.y += mGroundInfos[name].mSpeed.y;
				else
					curpos.y -= mGroundInfos[name].mSpeed.y;

				tf->SetPos(curpos);
				if (CheckOutMap(ground.get()) == true)
				{
					float x = mGroundInfos[name].mDiff.x-1;
					Transform* spawn_tf = q.back()->GetComponent<Transform>();
					x += spawn_tf->GetPos().x;
					//x += ani->GetSpriteSize().x;
					tf->SetPos(Vector2{ x,curpos.y });
				}
				q.push(ground);
				i--;
			}

		}
	}

	bool MedusaScene::CheckOutMap(GameObject* _obj)
	{
		Transform* tf = _obj->GetComponent<Transform>();
		Vector2 pos = tf->GetPos();
		Animator* ani = _obj->GetComponent<Animator>();
		Vector2 size(ani->GetSpriteSize());
		if (pos.x + size.x <= 0)
		{
			return true;
		}
		return false;
	}

	void MedusaScene::GroundInfoRelease()
	{
		for (auto map : mGroundsInfo)
		{
			std::queue<std::shared_ptr<GameObject>>& queue = map.second;
			while (queue.empty() == false)
			{
				std::shared_ptr<GameObject>& sp = queue.front();
				queue.pop();
				sp.reset();
			}
		}
	}

}

