#include "SaltBaker.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "ObjectPool.h"
#include "Application.h"
#include "SceneManager.h"
#include "MoveObject.h"
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

		Animator* ani = mAni;
		MoveObject* mv = mMoveObject;
		mAni->GetEndEvent(L"saltbaker_phase_1intro") = std::bind([ani]()->void
		{
			ani->Play(L"saltbaker_phase_1intro2", false);
		});

		mAni->GetEndEvent(L"saltbaker_phase_1intro2") = std::bind([ani, mv]()->void
		{
			mv->SetActive(true);
			std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");
			arm->SetActive(true);
			arm->GetComponent<MoveObject>()->SetActive(true);
			ani->Play(L"saltbaker_phase_1intro3", false);
		});
		mAni->GetEndEvent(L"saltbaker_phase_1intro3") = std::bind([ani, mv]()->void
		{
			mv->SetActive(true);
			std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");
			arm->SetActive(false);
			arm->GetComponent<MoveObject>()->SetActive(false);
			ani->Play(L"saltbaker_phase_1intro4", false);
		});
		mAni->GetEndEvent(L"saltbaker_phase_1intro4") = std::bind([ani, mv]()->void
		{
			mv->SetActive(false);
			ani->Play(L"saltbaker_phase_1idle", false);
		});
		

		//temp 
		mAni->GetEndEvent(L"saltbaker_phase_1idle") = std::bind([ani, mv]()->void
		{
			ani->Play(L"attack_type11", false);
		});

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
			arm_tf->SetPos(Vector2{ pos.x-400.0f, pos.y + 40.0f });
			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type1dough_attack1", false);
			MoveObject* mv = arm->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 100.0f,0.0f }, Vector2{ 1.0f,0.0f }, Vector2{ pos.x-40.0f ,pos.y });
			mv->SetActive(true);
		});
		mAni->GetEndEvent(L"attack_type11") = std::bind([ani]()->void
		{
			GameObject* owner = ani->GetOwner();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
			ani->Play(L"attack_type12",false);
			
			/*std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");
			arm->SetActive(true);
			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type1dough_attack1", false);*/
		});
		mAni->GetEndEvent(L"attack_type12") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type13", false);
		});
		mAni->GetEndEvent(L"attack_type13") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type14", false);
			std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");

			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type1dough_attack2_1", false);
		});
		mAni->GetEndEvent(L"attack_type14") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type15", false);
		});
		mAni->GetEndEvent(L"attack_type15") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type15_2", false);
		});
		mAni->GetEndEvent(L"attack_type15_2") = std::bind([ani]()->void
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
		mAni->GetEndEvent(L"attack_type16") = std::bind([ani]()->void
		{
			GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
		});

		ani->Play(L"saltbaker_phase_1intro", false);
		Vector2 pos = application.GetWindowSize();

		mTransform->SetPos(Vector2{ pos.x / 2.0f,570.0f });


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
				tf->SetPos(Vector2{ pos.x+300.0f,pos.y-50.0f });
				Animator* ani = arm->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack1", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2_1", Vector2::Zero, 0.09575f);

				ani->GetEndEvent(L"attack_type1dough_attack1") = std::bind([ani]()->void
				{
					ani->Play(L"attack_type1dough_attack2", false);
				});

				ani->Play(L"saltbaker_phase_1intro_arm", false);
				arm->SetActive(false);
			}
			mParts.insert(std::make_pair(EParts::ARM, arm));
		}
	}
	void SaltBaker::RegisterPattern1()
	{
		PatternInfo pattern = { L"attack_type1attack_type11" };
		mPatterns[EPhaseType::PHASE1].push_back(pattern);
	}
	void SaltBaker::RegisterPattern2()
	{
	}
	void SaltBaker::RegisterPattern3()
	{
	}
	void SaltBaker::Update()
	{
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

}

