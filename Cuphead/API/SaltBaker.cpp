#include "SaltBaker.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "ObjectPool.h"
#include "Application.h"
#include "SceneManager.h"
#include "MoveObject.h"
#include "CookieBullet.h"
#include "SugarBullet.h"
#include "ParryingObject.h"
extern yeram_client::Application application;

namespace yeram_client
{
	SaltBaker::SaltBaker() :Boss()
	{
		SetName(L"SaltBaker");
		mobjType = EGameObjectType::Boss;
	}

	SaltBaker::~SaltBaker()
	{
	}

	void SaltBaker::Initialize()
	{
		Boss::Initialize();
		mMoveObject->CreateInfo(Vector2{ 400.0f,20.0f }, Vector2{ -1.0f,-1.0f });
		mMoveObject->SetActive(false);


		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\idle", Vector2::Zero, 0.1f);

		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5_2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\6", Vector2::Zero, 0.1f);


		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\1_2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\5", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\6", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\7", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\8", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\8_2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\9", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\10", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\11", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\11_2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\12", Vector2::Zero, 0.1f);


		Animator* ani = mAni;
		MoveObject* mv = mMoveObject;
		SetPhase(EPhaseType::PHASE1);
#pragma region intro event
		mAni->GetCompleteEvent(L"saltbaker_phase_1intro") = std::bind([ani]()->void
		{
			ani->Play(L"saltbaker_phase_1intro2", false);
		});

		mAni->GetCompleteEvent(L"saltbaker_phase_1intro2") = std::bind([ani, mv, this]()->void
		{
			mv->SetActive(true);
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			arm->GetComponent<MoveObject>()->SetActive(true);
			ani->Play(L"saltbaker_phase_1intro3", false);
		});
		mAni->GetCompleteEvent(L"saltbaker_phase_1intro3") = std::bind([ani, mv, this]()->void
		{
			mv->SetActive(true);
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
			arm->GetComponent<MoveObject>()->SetActive(false);
			ani->Play(L"saltbaker_phase_1intro4", false);
		});
		mAni->GetCompleteEvent(L"saltbaker_phase_1intro4") = std::bind([ani, mv, this]()->void
		{
			mAttackCheck[EPhaseType::PHASE1][EAttackType::Type1]->mActive = true;
			mAttackCheck[EPhaseType::PHASE1][EAttackType::Type2]->mActive = true;
			mv->SetActive(false);
			ani->Play(L"saltbaker_phase_1idle", false);
		});


		//temp 
		mAni->GetCompleteEvent(L"saltbaker_phase_1idle") = std::bind([ani]()->void
		{

			//switch (mPhaseType)
			//{
			//default:
			//	Phase1();
			//}

			ani->Play(L"attack_type11", false);
		});
#pragma endregion
#pragma region p1 attacktype1 event
		mAni->GetStartEvent(L"attack_type11") = std::bind([ani]()->void
		{
			GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(true);
			o_mv->CreateInfo(Vector2{ 0.0f,100.0f }, Vector2{ 0.0f,1.0f }, Vector2{ pos.x,pos.y + 40.0f });
			std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");
			arm->SetActive(true);
			Transform* arm_tf = arm->GetComponent<Transform>();
			arm_tf->SetPos(Vector2{ pos.x - 400.0f, pos.y + 40.0f });
			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type1dough_attack1", false);
			MoveObject* mv = arm->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 100.0f,0.0f }, Vector2{ 1.0f,0.0f }, Vector2{ pos.x - 40.0f ,pos.y });
			mv->SetActive(true);
		});
		mAni->GetCompleteEvent(L"attack_type11") = std::bind([ani]()->void
		{
			GameObject* owner = ani->GetOwner();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
			ani->Play(L"attack_type12", false);

			/*std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");
			arm->SetActive(true);
			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type1dough_attack1", false);*/
		});
		mAni->GetCompleteEvent(L"attack_type12") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type13", false);
		});
		mAni->GetCompleteEvent(L"attack_type13") = std::bind([ani, this]()->void
		{
			ani->Play(L"attack_type14", false);

			/*	if(mParts[EParts::ARM]==mParts.end())
				{ }*/
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];

			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type1dough_attack2_1", false);
		});
		mAni->GetCompleteEvent(L"attack_type14") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type15", false);
		});
		mAni->GetCompleteEvent(L"attack_type15") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type15_2", false);
		});
		mAni->GetCompleteEvent(L"attack_type15_2") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type16", false);
		});
		mAni->GetStartEvent(L"attack_type16") = std::bind([ani]()->void
		{
			GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(true);
			o_mv->CreateInfo(Vector2{ 0.0f,100.0f }, Vector2{ 0.0f,-1.0f }, Vector2{ pos.x,pos.y - 50.0f });
		});
		mAni->GetCompleteEvent(L"attack_type16") = std::bind([ani, this]()->void
		{
			GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
			//mAttackCheck[EPhaseType::PHASE1][EAttackType::Type1]->mActive = true;
			//ani->Play(L"saltbaker_phase_1idle", true);
			//test

		});
#pragma endregion
#pragma region p1 attacktype2 event

		mAni->GetCompleteEvent(L"attack_type21") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->SetActive(true);
			sugar->GetComponent<Animator>()->Play(L"attack_type21_2reg", false);
			//1_2reg ÄÑÁÖ±â
			ani->Play(L"attack_type21_2", false);
		});
		mAni->GetCompleteEvent(L"attack_type21_2") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			Transform* s_tf = sugar->GetComponent<Transform>();
			Vector2 pos = s_tf->GetPos();
			pos.x += 60.0f;
			pos.y += 110.0f;
			s_tf->SetPos(pos);
			sugar->GetComponent<Animator>()->Play(L"attack_type22_sugar", false);
			ani->Play(L"attack_type22", false);
		});

		mAni->GetCompleteEvent(L"attack_type22") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type23_sugar", false);
			ani->Play(L"attack_type23", false);
		});

		mAni->GetCompleteEvent(L"attack_type23") = std::bind([ani, mv, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type24_sugar", true);

			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();

			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 330.0f,0.0f }, Vector2{ 1.0,0.0f }, Vector2{ pos.x + 330.0f,pos.y }, false, false);
			ani->Play(L"attack_type24", false);
		});

		mAni->GetCompleteEvent(L"attack_type24") = std::bind([ani, mv]()->void
		{
			mv->SetActive(false);
			ani->Play(L"attack_type25", false);
		});

		mAni->GetCompleteEvent(L"attack_type25") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type26_sugar", false);
			ani->Play(L"attack_type26", false);
		});

		mAni->GetCompleteEvent(L"attack_type26") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type27_sugar", false);
			ani->Play(L"attack_type27", false);
		});

		mAni->GetCompleteEvent(L"attack_type27") = std::bind([ani, mv, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type28_sugar", false);

			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 200.0f,0.0f }, Vector2{ 1.0,0.0f }, Vector2{ pos.x + 60.0f,pos.y }, false, false);
			ani->Play(L"attack_type28", false);
		});
		mAni->GetCompleteEvent(L"attack_type28") = std::bind([ani, mv, this]()->void
		{
			mv->SetActive(false);
			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x -= 240.0f;
			pos.y -= 50.0f;
			tf->SetPos(pos);
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type28_2_sugar", false);
			ani->Play(L"attack_type28_2", false);
		});

		mAni->GetCompleteEvent(L"attack_type28_2") = std::bind([ani, mv, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->GetComponent<Animator>()->Play(L"attack_type29_sugar", false);

			ani->Play(L"attack_type29", false);
		});

		mAni->GetCompleteEvent(L"attack_type29") = std::bind([ani, mv, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->SetActive(false);

			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			Transform* tf = arm->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x -= 350.0f;
			pos.y += 195.0f;
			tf->SetPos(pos);
			arm->GetComponent<Animator>()->Play(L"attack_type210_arm", false);
			/*	Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
				Vector2 o_pos = o_tf->GetPos();
				o_pos.y += 10.0f;
				mv->SetActive(true);
				mv->CreateInfo(Vector2{0.0f,100.0f}, Vector2{0.0f,1.0f}, o_pos,false,false);*/
			ani->Play(L"attack_type210", false);
		});
		mAni->GetCompleteEvent(L"attack_type210") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type211", false);
		});
		mAni->GetCompleteEvent(L"attack_type211") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->GetComponent<Animator>()->Play(L"attack_type211_2_arm", false);
			Transform* tf = arm->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x += 300.0f;
			//pos.y -= 100.0f;
			tf->SetPos(pos);
			ani->Play(L"attack_type211_2", false);
		});

		mAni->GetCompleteEvent(L"attack_type211_2") = std::bind([ani, this]()->void
		{
			mAttackCheck[EPhaseType::PHASE1][EAttackType::Type2]->mActive = true;
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.y += 100.0f;
			tf->SetPos(pos);
			ani->Play(L"attack_type212", false);
		});
		/**/
#pragma endregion
		//mAni->Play(L"saltbaker_phase_1intro", false);
		//test
	    mAni->Play(L"attack_type21", false);
		Vector2 pos = application.GetWindowSize();

		mTransform->SetPos(Vector2{ pos.x / 2.0f,450.0f });
		mTransform->SetScale(Vector2{ 1.1f,1.3f });


		if (mParts.find(EParts::ARM) == mParts.end())
		{
			std::shared_ptr<GameObject> arm = core::ObjectPool<Animator>::Spawn();
			{
				arm->SetName(L"sb_arm");

				MoveObject* mv = arm->AddComponent<MoveObject>();
				mv->SetActive(false);
				mv->CreateInfo(Vector2{ 400.0f,20.0f }, Vector2{ -1.0f,-1.0f });
				Vector2 pos = mTransform->GetPos();
				Transform* tf = arm->GetComponent<Transform>();
				tf->SetScale(mTransform->GetScale());
				tf->SetPos(Vector2{ pos.x + 270.0f,pos.y - 30.0f });
				Animator* ani = arm->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack1", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2_1", Vector2::Zero, 0.09575f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\10_arm", Vector2::Zero, 0.099f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\11_arm", Vector2::Zero, 0.099f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\11_2_arm", Vector2::Zero, 0.1f);
				ani->GetCompleteEvent(L"attack_type1dough_attack1") = std::bind([ani]()->void
				{
					ani->Play(L"attack_type1dough_attack2", false);
				});
				ani->GetCompleteEvent(L"attack_type210_arm") = std::bind([ani, tf]()->void
				{
					Vector2 pos = tf->GetPos();
					pos.x += 210.0f;
					pos.y -= 100.0f;
					tf->SetPos(pos);
					ani->Play(L"attack_type211_arm", false);
				});
				ani->Play(L"saltbaker_phase_1intro_arm", false);
				arm->SetActive(false);
			}
			mParts.insert(std::make_pair(EParts::ARM, arm));
		}
		if (mParts.find(EParts::ACC) == mParts.end())
		{
			std::shared_ptr<GameObject> sugar = core::ObjectPool<Animator>::Spawn();
			{
				sugar->SetName(L"sb_p1a2sugar");
				sugar->SetActive(false);
				MoveObject* mv = sugar->AddComponent<MoveObject>();
				mv->SetActive(false);
				Vector2 pos = mTransform->GetPos();
				Transform* tf = sugar->GetComponent<Transform>();
				tf->SetScale(mTransform->GetScale());
				tf->SetPos(Vector2{ 730.0f,500.0f });
				Animator* ani = sugar->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\1_2reg", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\2_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\3_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\4_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\6_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\7_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\8_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\8_2_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\9_sugar", Vector2::Zero, 0.1f);

			}
			mParts.insert(std::make_pair(EParts::ACC, sugar));
		}
		std::vector<std::wstring> vec;
		vec.push_back(L"camel_type1");
		vec.push_back(L"camel_type2");
		vec.push_back(L"camel_type3");
		std::vector<std::wstring> vec2;
		vec2.push_back(L"sugarbullettype1");
		vec2.push_back(L"sugarbullettype2");
		vec2.push_back(L"sugarbullettype3");
		vec2.push_back(L"sugarbullettype4");
		mPhaseInfo.insert(std::make_pair(EPhaseType::PHASE1, std::map<EAttackType, std::vector<std::wstring>>()));
		mPhaseInfo[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type1, vec));
		mPhaseInfo[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type2, vec2));

		mAttackCheck.insert(std::make_pair(EPhaseType::PHASE1, std::map<EAttackType, SpawnInfo*>()));
		mAttackCheck[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type1, new SpawnInfo{ false,3.0,7,0,std::bind([this]()->void
		{
			P1AttackType1();
		}) }));
		mAttackCheck[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type2, new SpawnInfo{ false,3.0,8,0,std::bind([this]()->void
		{
			P1AttackType2();
		}) }));
	}

	void SaltBaker::Update()
	{
		Boss::Update();
		std::map<EAttackType, SpawnInfo*> map = mAttackCheck[mPhaseType];
		for (auto& spawn_info : map)
		{
			SpawnInfo* spawn = spawn_info.second;
			if (spawn->mActive == false)
				continue;
			double diff = mTime - spawn->mSpawnTime;
			if (diff >= spawn->mCoolTime)
			{
				if (spawn->mCount <= 0)
				{
					spawn->mActive = false;
					continue;
				}
				spawn->mCount--;
				spawn->mSpawnEvent();
				spawn->mSpawnTime = mTime;
			}

		}
	}

	void SaltBaker::Render(HDC hdc)
	{
	}

	void SaltBaker::Release()
	{
		for (auto& parts : mParts)
		{
			parts.second.reset();
		}
		mParts.clear();


		for (auto& m : mAttackCheck)
		{
			for (auto& spawninfo : m.second)
			{
				delete spawninfo.second;
				spawninfo.second = nullptr;
			}
			m.second.clear();
		}
		mAttackCheck.clear();
	}

	void SaltBaker::OnCollisionEnter(Collider* other)
	{
	}

	void SaltBaker::OnCollisionStay(Collider* other)
	{
	}

	void SaltBaker::OnCollisionExit(Collider* other)
	{
	}
	void SaltBaker::P1AttackType1()
	{
		mActiveAttack = mPhaseInfo[EPhaseType::PHASE1][EAttackType::Type1];
		int str_cnt = mActiveAttack.size();

		bool flag = false;

		int cnt = 0;

		int str_type = rand() % str_cnt;
		std::shared_ptr<GameObject> cookie = core::ObjectPool<CookieBullet>::Spawn();
		
		CookieBullet* cb = cookie->GetComponent<CookieBullet>();
		std::wstring ani_name = mActiveAttack[str_type];
		int speed = rand()%3==0 ? 1 : 2;
		float xspeed = 100.0f * speed;

		Vector2 pos = Vector2{ 0.0f,600.0f };
		
		cb->SetPos(pos);
		cb->CreateInfo(Vector2{ xspeed,xspeed * 2.0f }, Vector2{ 100.0f,100.0f }, Vector2{ 1.0f,-1.0f });
		cb->Shoot();
		cb->SetAnimation(ani_name, false);
		SceneManager::GetActiveScene()->AddGameObject(cookie, ELayerType::Bullet);
	}
	void SaltBaker::P1AttackType2()
	{
		mActiveAttack = mPhaseInfo[EPhaseType::PHASE1][EAttackType::Type2];
		int str_cnt = mActiveAttack.size();


		int str_type = rand() % str_cnt;
		std::shared_ptr<GameObject> sugar = core::ObjectPool<SugarBullet>::Spawn();
		SugarBullet* sb = sugar->GetComponent<SugarBullet>();
		std::wstring ani_name = mActiveAttack[str_type];

		if (str_type == 3) // type4
		{
			ParryingObject* po = sugar->AddComponent<ParryingObject>();
			sb->SetParry(true);
		}

		Vector2 pos = Vector2{ 0.0f,700.0f };

		sb->SetPos(pos);
		sb->SetAnimation(ani_name, true);
		sb->CreateInfo(Vector2{ 100,400 }, Vector2{ 4000.0f,1000.0f }, Vector2{ 1.0f,-1.0f });
		sb->Shoot();

		SceneManager::GetActiveScene()->AddGameObject(sugar, ELayerType::Bullet);
	}
	void SaltBaker::Phase1()
	{
		mAni->Play(L"attack_type11", false);

		std::map<EAttackType, std::vector<std::wstring>>& phase1_map = mPhaseInfo[EPhaseType::PHASE1];

		int size = phase1_map.size();

		int attack_type = rand() % size;
		mActiveAttack = phase1_map[(EAttackType)attack_type];

	}

	void SaltBaker::Phase2()
	{
	}

	void SaltBaker::Phase3()
	{
	}
	void SaltBaker::RegisterPattern1()
	{
		//PatternInfo pattern = { L"attack_type1attack_type11" };
		//mPatterns[EPhaseType::PHASE1].push_back(pattern);
	}
	void SaltBaker::RegisterPattern2()
	{
	}
	void SaltBaker::RegisterPattern3()
	{
	}
}

