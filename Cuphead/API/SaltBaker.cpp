#include "SaltBaker.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "ObjectPool.h"
#include "Application.h"
#include "SceneManager.h"
#include "MoveObject.h"
#include "CookieBullet.h"
#include "SugarBullet.h"
#include "BerryBullet.h"
#include "LemonBullet.h"
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
		mMoveObject->CreateInfo(Vector2{ 550.0f,20.0f }, Vector2{ -1.0f,-1.0f });
		mMoveObject->SetActive(false);


		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\idle", Vector2::Zero, 0.1f);

		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2_1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2_2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5_2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5_3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\6", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\7", Vector2::Zero, 0.1f);


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


		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\5", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\6", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\7", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\8", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\9", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\10", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\11", Vector2::Zero, 0.1f);


		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\5", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\6", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\7", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\8", Vector2::Zero, 0.1f);
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
			Transform* a_tf = arm->GetComponent<Transform>();
			Vector2 pos = a_tf->GetPos();
			pos.x += 50.0f;
			pos.y += 50.0f;
			a_tf->SetPos(pos);
			arm->SetActive(false);
			arm->GetComponent<MoveObject>()->SetActive(false);
			ani->Play(L"saltbaker_phase_1intro4", false);
		});
		mAni->GetCompleteEvent(L"saltbaker_phase_1intro4") = std::bind([ani, mv, this]()->void
		{
			//mAttackCheck[EPhaseType::PHASE1][EAttackType::Type1]->mActive = true;
			//mAttackCheck[EPhaseType::PHASE1][EAttackType::Type2]->mActive = true;
			//mAttackCheck[EPhaseType::PHASE1][EAttackType::Type5]->mActive = true;
			//mAttackCheck[EPhaseType::PHASE1][EAttackType::Type4]->mActive = true;
			mv->SetActive(false);
			ani->Play(L"saltbaker_phase_1idle", false);
		});

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

		mAni->GetStartEvent(L"attack_type11") = std::bind([ani, this]()->void
		{
			GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(true);
			o_mv->CreateInfo(Vector2{ 0.0f,100.0f }, Vector2{ 0.0f,1.0f }, Vector2{ pos.x,pos.y + 40.0f });
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(true);
			Transform* acc_tf = acc->GetComponent<Transform>();
			acc_tf->SetPos(Vector2{ pos.x - 400.0f, pos.y + 40.0f });
			Animator* acc_ani = acc->GetComponent<Animator>();
			acc_ani->Play(L"attack_type1dough_attack1", false);
			MoveObject* mv = acc->GetComponent<MoveObject>();
			mv->CreateInfo(Vector2{ 100.0f,0.0f }, Vector2{ 1.0f,0.0f }, Vector2{ pos.x - 40.0f ,pos.y });
			mv->SetActive(true);
		});
		mAni->GetCompleteEvent(L"attack_type11") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(false);
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			arm->GetComponent<Animator>()->Play(L"attack_type12_arm", false);
			Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 o_pos = o_tf->GetPos();
			
			Transform* a_tf = arm->GetComponent<Transform>();
			Vector2 pos = o_pos;
			pos.x -= 0.0f;
			pos.y += 30.0f;
			a_tf->SetPos(pos);
			GameObject* owner = ani->GetOwner();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
			ani->Play(L"attack_type12", false);

			//std::shared_ptr<GameObject> arm = SceneManager::GetActiveScene()->FindObject(L"sb_arm");
			//arm->SetActive(true);
			//Animator* arm_ani = arm->GetComponent<Animator>();
			//arm_ani->Play(L"attack_type1dough_attack1", false);
		});
		mAni->GetCompleteEvent(L"attack_type12") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->GetComponent<Animator>()->Play(L"attack_type12_1arm", false);
			Transform* a_tf = arm->GetComponent<Transform>();
			Vector2 pos = a_tf->GetPos();
			pos.x += 150.0f;
			pos.y += 10.0f;
			a_tf->SetPos(pos);
			GameObject* owner = ani->GetOwner();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
			ani->Play(L"attack_type12_1", false);
		});
		mAni->GetCompleteEvent(L"attack_type12_1") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->GetComponent<Animator>()->Play(L"attack_type12_2arm", false);
			Transform* a_tf = arm->GetComponent<Transform>();
			Vector2 pos = a_tf->GetPos();
			pos.x -= 50.0f;
			pos.y += 30.0f;
			a_tf->SetPos(pos);
			GameObject* owner = ani->GetOwner();
			ani->Play(L"attack_type12_2", false);
		});
		mAni->GetCompleteEvent(L"attack_type12_2") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->GetComponent<Animator>()->Play(L"attack_type13_arm", true);
			GameObject* owner = ani->GetOwner();
			ani->Play(L"attack_type13", false);
		});


		mAni->GetCompleteEvent(L"attack_type13") = std::bind([ani, this]()->void
		{
			ani->Play(L"attack_type14", false);

			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 o_pos =tf->GetPos();
			o_pos.y += 50.0f;
			tf->SetPos(o_pos);
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			Transform* a_tf = arm->GetComponent<Transform>();
			Vector2 pos = a_tf->GetPos();
			pos.x -= 60.0f;
			pos.y += 40.0f;
			a_tf->SetPos(pos);
			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type14_arm", false);
		});

		mAni->GetCompleteEvent(L"attack_type14") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			Transform* a_tf = arm->GetComponent<Transform>();
			Vector2 pos = a_tf->GetPos();
			pos.x += 40.0f;
			pos.y -= 80.0f;
			a_tf->SetPos(pos);
			Animator* arm_ani = arm->GetComponent<Animator>();
			arm_ani->Play(L"attack_type15_arm", false);
			ani->Play(L"attack_type15", false);
		});

		mAni->GetCompleteEvent(L"attack_type15") = std::bind([ani]()->void
		{
			ani->Play(L"attack_type15_2", false);
		});
		mAni->GetCompleteEvent(L"attack_type15_2") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(true);
			Vector2 pos = arm->GetComponent<Transform>()->GetPos();
			acc->GetComponent<Transform>()->SetPos(pos);
			acc->GetComponent<Animator>()->Play(L"attack_type1dough_attack2_1", false);
			ani->Play(L"attack_type15_3", false);
		});

		mAni->GetCompleteEvent(L"attack_type15_3") = std::bind([ani]()->void
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
		mAni->GetCompleteEvent(L"attack_type16") = std::bind([ani,mv, this]()->void
		{
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(false);
			GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);
			mAttackCheck[EPhaseType::PHASE1][EAttackType::Type1]->mActive = true;
			//ani->Play(L"saltbaker_phase_1idle", true);
			//test
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 400.0f,0.0f }, Vector2{ 1.0f,0.0f }, Vector2{ application.GetWindowSize().x - 250.0f,pos.y });
			mv->SetArriveEvent(std::bind([ani,mv]()->void 
			{
				ani->Play(L"attack_type41", false);
				mv->SetActive(false);
				mv->SetArriveEvent(std::bind([mv]()->void { mv->SetActive(false); }));
			}));
			ani->Play(L"attack_type17", false);
		});
		mAni->GetCompleteEvent(L"attack_type17") = std::bind([ani, this]()->void
		{
			/*GameObject* owner = ani->GetOwner();
			Transform* o_tf = owner->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			MoveObject* o_mv = owner->GetComponent<MoveObject>();
			o_mv->SetActive(false);*/
			//mAttackCheck[EPhaseType::PHASE1][EAttackType::Type1]->mActive = true;
			//ani->Play(L"saltbaker_phase_1idle", true);
			//test
			//ani->Play(L"attack_type41", false);
		});
#pragma endregion
#pragma region p1 attacktype2 event

		mAni->GetCompleteEvent(L"attack_type21") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->SetActive(true);
			sugar->GetComponent<Animator>()->Play(L"attack_type21_2reg", false);
			Vector2 pos = ani->GetOwner()->GetComponent<Transform>()->GetPos();
			Transform* stf = sugar->GetComponent<Transform>();
			stf->SetPos(pos);
			//1_2reg ���ֱ�
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
			GameObject* owner = ani->GetOwner();
			std::shared_ptr<GameObject> sugar = mParts[EParts::ACC];
			sugar->SetActive(false);

			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			Transform* otf = owner->GetComponent<Transform>();
			Vector2 pos = otf->GetPos();
			Transform* tf = arm->GetComponent<Transform>();
			pos.x -= 200.0f;
			pos.y += 135.0f;
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
		mAni->GetCompleteEvent(L"attack_type212") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.y += 100.0f;
			tf->SetPos(pos);
			ani->Play(L"attack_type51", false);
		});

#pragma endregion
#pragma region p1 attacktype4 event
		mAni->GetCompleteEvent(L"attack_type41") = std::bind([ani,this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			Transform* a_tf = arm->GetComponent<Transform>();
			pos.x -= 100.0f;
			pos.y += 100.0f;
			a_tf->SetPos(pos);
			Animator* a_ani = arm->GetComponent<Animator>();
			a_ani->Play(L"attack_type42_arm", false);
			ani->Play(L"attack_type42",false);
		});
		
		mAni->GetCompleteEvent(L"attack_type42") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(true);

			Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			Transform* a_tf = acc->GetComponent<Transform>();
			pos.x -= 00.0f;
			pos.y += 100.0f;
			a_tf->SetPos(pos);
			Animator* a_ani = acc->GetComponent<Animator>();
			a_ani->Play(L"attack_type43_remon", false);
			ani->Play(L"attack_type43", false);
		});
	
		mAni->GetCompleteEvent(L"attack_type43") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(false);

			Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			Transform* a_tf = arm->GetComponent<Transform>();
			pos.x += 250.0f;
			pos.y += 50.0f;
			a_tf->SetPos(pos);
			MoveObject* amv = arm->GetComponent<MoveObject>();
			//amv->SetActive(true);
			//amv->CreateInfo(Vector2{ 10.0f,0.0f }, Vector2{ -1.0f,0.0f }, Vector2{ pos.x - 50.0f,pos.y }, false, false);
			Animator* a_ani = arm->GetComponent<Animator>();
			a_ani->Play(L"attack_type44_arm", false);
			ani->Play(L"attack_type44", false);
		});
		
		mAni->GetCompleteEvent(L"attack_type44") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(true);

			Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			Transform* a_tf = acc->GetComponent<Transform>();
			pos.x -= 00.0f;
			pos.y += 100.0f;
			a_tf->SetPos(pos);
			Animator* a_ani = acc->GetComponent<Animator>();
			a_ani->Play(L"attack_type45_remon", false);
			ani->Play(L"attack_type45", false);
		});
		
		mAni->GetCompleteEvent(L"attack_type45") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(true);
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(false);

			Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = o_tf->GetPos();
			Transform* a_tf = arm->GetComponent<Transform>();
			pos.x += 100.0f;
			pos.y += 100.0f;
			a_tf->SetPos(pos);
			//MoveObject* amv = acc->GetComponent<MoveObject>();
			//amv->SetActive(true);
			//amv->CreateInfo(Vector2{ 10.0f,0.0f }, Vector2{ -1.0f,0.0f }, Vector2{ pos.x - 50.0f,pos.y }, false, false);
			Animator* a_ani = arm->GetComponent<Animator>();
			a_ani->Play(L"attack_type46_arm", false);
			ani->Play(L"attack_type46", false);
		});
		
		mAni->GetCompleteEvent(L"attack_type46") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			arm->SetActive(false);
	
			ani->Play(L"attack_type47", false);
		});
		mAni->GetCompleteEvent(L"attack_type47") = std::bind([ani,mv,this]()->void
		{
			mAttackCheck[EPhaseType::PHASE1][EAttackType::Type4]->mActive = true;
			mv->SetActive(true);
			Vector2 pos = mv->GetOwner()->GetComponent<Transform>()->GetPos();
			mv->CreateInfo(Vector2{ 400.0f,0.0f }, Vector2{ -1.0f,0.0f }, Vector2{ 200.0f,pos.y });
			mv->SetArriveEvent(std::bind([mv,ani]()->void
			{
				ani->Play(L"attack_type21", false);
				mv->SetActive(false);
				mv->SetArriveEvent(std::bind([mv]()->void { mv->SetActive(false); }));
			}));
			ani->Play(L"attack_type48", false);
		});
		
		//mAni->GetCompleteEvent(L"attack_type46") = std::bind([ani, this]()->void
		//{
		//	std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
		//	arm->SetActive(false);
		//	std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
		//	acc->SetActive(true);

		//	Transform* o_tf = ani->GetOwner()->GetComponent<Transform>();
		//	Vector2 pos = o_tf->GetPos();
		//	Transform* a_tf = arm->GetComponent<Transform>();
		//	pos.x += 100.0f;
		//	pos.y += 100.0f;
		//	a_tf->SetPos(pos);
		//	MoveObject* amv = arm->GetComponent<MoveObject>();
		//	amv->SetActive(true);
		//	//amv->CreateInfo(Vector2{ 10.0f,0.0f }, Vector2{ -1.0f,0.0f }, Vector2{ pos.x - 50.0f,pos.y }, false, false);
		//	Animator* a_ani = arm->GetComponent<Animator>();
		//	a_ani->Play(L"attack_type45_remon", false);
		//	ani->Play(L"attack_type46", false);
		//});
#pragma endregion
#pragma region p1 attacktype5 event
		mAni->GetCompleteEvent(L"attack_type51") = std::bind([ani, mv, this]()->void
		{
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			{
				acc->SetActive(true);
				Transform* a_tf = acc->GetComponent<Transform>();
				a_tf->SetPos(Vector2{ application.GetWindowSize().x - 10.0f,600.0f });
				Vector2 pos = a_tf->GetPos();
				MoveObject* a_mv = acc->GetComponent<MoveObject>();
				a_mv->SetActive(true);
				a_mv->CreateInfo(Vector2{ 300.0f,0.0f }, Vector2{ -1.0f,0.0f }, Vector2{ pos.x / 2.0f,pos.y }, false, false);
				acc->GetComponent<Animator>()->Play(L"attack_type52_berrybox", true);
			}
			Transform* tf = mv->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			mv->SetActive(true);
			mv->CreateInfo(Vector2{ 850.0f,0.0f }, Vector2{ 1.0f,0.0f }, Vector2{ pos.x + 850.0f ,pos.y }, false, false);

			ani->Play(L"attack_type52", false);
		});
		mAni->GetCompleteEvent(L"attack_type52") = std::bind([ani, mv]()->void
		{
			mv->SetActive(false);
			ani->Play(L"attack_type53", false);
		});
		mAni->GetCompleteEvent(L"attack_type53") = std::bind([ani]()->void
		{
			Transform* tf = ani->GetOwner()->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.y -= 100.0f;
			tf->SetPos(pos);
			ani->Play(L"attack_type54", false);
		});
		mAni->GetCompleteEvent(L"attack_type54") = std::bind([ani]()->void
		{

			ani->Play(L"attack_type55", false);
		});
		mAni->GetCompleteEvent(L"attack_type55") = std::bind([ani, this]()->void
		{
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			acc->SetActive(false);
			Vector2 pos = acc->GetComponent<Transform>()->GetPos();
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			{
				arm->SetActive(true);
				Transform* a_tf = arm->GetComponent<Transform>();
				//pos.x -= 90.0f;
				//pos.y -= 90.0f;
				a_tf->SetPos(pos);
				MoveObject* a_mv = arm->GetComponent<MoveObject>();
				a_mv->SetActive(false);
				arm->GetComponent<Animator>()->Play(L"attack_type56_arm", false);
			}
			ani->Play(L"attack_type56", false);
		});
		mAni->GetCompleteEvent(L"attack_type56") = std::bind([ani, this]()->void
		{
			GameObject* owner = ani->GetOwner();
			std::shared_ptr<GameObject> arm = mParts[EParts::ARM];
			{
				arm->SetActive(false);
			}
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			{
				acc->SetActive(true);
				Transform* tf = owner->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				pos.x += 75.0f;
				pos.y += 0.0f;
				Transform* a_tf = acc->GetComponent<Transform>();
				a_tf->SetPos(pos);
				MoveObject* a_mv = acc->GetComponent<MoveObject>();
				a_mv->SetActive(false);
				acc->GetComponent<Animator>()->Play(L"attack_type57_berrybox", false);
			}
			ani->Play(L"attack_type57", false);
		});

		mAni->GetCompleteEvent(L"attack_type57") = std::bind([ani, this]()->void
		{
			GameObject* owner = ani->GetOwner();
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			{
				Transform* tf = owner->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				pos.x += 75.0f;
				pos.y += 120.0f;
				Transform* a_tf = acc->GetComponent<Transform>();
				a_tf->SetPos(pos);
				acc->GetComponent<Animator>()->Play(L"attack_type58_berrybox", false);
			}
			ani->Play(L"attack_type58", false);
		});
		mAni->GetCompleteEvent(L"attack_type58") = std::bind([ani, this]()->void
		{
			GameObject* owner = ani->GetOwner();
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			{
				Transform* tf = owner->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				pos.x += 85.0f;
				pos.y += 120.0f;
				Transform* a_tf = acc->GetComponent<Transform>();
				a_tf->SetPos(pos);
				acc->GetComponent<Animator>()->Play(L"attack_type59_berrybox", false);
			}
			ani->Play(L"attack_type59", false);
		});


		mAni->GetCompleteEvent(L"attack_type59") = std::bind([ani,mv, this]()->void
		{
			mAttackCheck[EPhaseType::PHASE1][EAttackType::Type5]->mActive = true;
			GameObject* owner = ani->GetOwner();
			std::shared_ptr<GameObject> acc = mParts[EParts::ACC];
			{
				
				Transform* tf = owner->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				pos.x += 85.0f;
				pos.y += 150.0f;
				Transform* a_tf = acc->GetComponent<Transform>();
				a_tf->SetPos(pos);
				acc->GetComponent<Animator>()->Play(L"attack_type510_berrybox", true);
				MoveObject*a_mv = acc->GetComponent<MoveObject>();
				a_mv->SetActive(true);
				a_mv->CreateInfo(Vector2{ 300.0f,0.0f }, Vector2{ -1.0f,0.0f }, Vector2{ -500.0f,pos.y }, true, true);
			}
			mv->SetActive(true);
			Vector2 pos = ani->GetOwner()->GetComponent<Transform>()->GetPos();
			pos.x += 400.0f;
			mv->CreateInfo(Vector2{ 400.0f,0.0f }, Vector2{ 1.0f,0.0f }, pos, false, false);
		
			ani->Play(L"attack_type510", false);
		});
		
		mAni->GetCompleteEvent(L"attack_type510") = std::bind([ani,mv,this]()->void
		{
			ani->Play(L"attack_type511", false);
		});
		mAni->GetCompleteEvent(L"attack_type511") = std::bind([ani]()->void
		{
			//ani->Play(L"attack_type21", false);
		});
#pragma endregion
		mAni->Play(L"saltbaker_phase_1intro", false);
		//test
	   // mAni->Play(L"attack_type48", false);
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
				mv->CreateInfo(Vector2{ 450.0f,20.0f }, Vector2{ -1.0f,-1.0f });
				Vector2 pos = mTransform->GetPos();
				Transform* tf = arm->GetComponent<Transform>();
				tf->SetScale(mTransform->GetScale());
				tf->SetPos(Vector2{ pos.x + 320.0f,pos.y + 20.0f });
				Animator* ani = arm->GetComponent<Animator>();
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2_arm", Vector2::Zero, 0.09575f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2_1arm", Vector2::Zero, 0.09575f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2_2arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\3_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\4_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\10_arm", Vector2::Zero, 0.099f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\11_arm", Vector2::Zero, 0.099f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\11_2_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\2_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\4_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\4_2arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\6_arm", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\6_arm", Vector2::Zero, 0.1f);


				ani->GetCompleteEvent(L"attack_type210_arm") = std::bind([ani, tf]()->void
				{
					Vector2 pos = tf->GetPos();
					pos.x += 210.0f;
					pos.y -= 100.0f;
					tf->SetPos(pos);
					ani->Play(L"attack_type211_arm", false);
				});
				ani->GetCompleteEvent(L"attack_type44_arm") = std::bind([ani]()->void
				{
					GameObject* owner = ani->GetOwner();
					Transform* tf = owner->GetComponent<Transform>();
					Vector2 pos = tf->GetPos();
					pos.x -= 200.0f;
					pos.y += 100.0f;
					tf->SetPos(pos);

					ani->Play(L"attack_type44_2arm", false);
				});
				ani->Play(L"saltbaker_phase_1intro_arm", false);
				arm->SetActive(false);
			}
			mParts.insert(std::make_pair(EParts::ARM, arm));
		}
		if (mParts.find(EParts::ACC) == mParts.end())
		{
			std::shared_ptr<GameObject> acc = core::ObjectPool<Animator>::Spawn();
			{
				acc->SetName(L"sb_p1acc");
				acc->SetActive(false);
				MoveObject* mv = acc->AddComponent<MoveObject>();
				mv->SetActive(false);
				Vector2 pos = mTransform->GetPos();
				Transform* tf = acc->GetComponent<Transform>();
				tf->SetScale(mTransform->GetScale());
				tf->SetPos(Vector2{ 730.0f,500.0f });
				Animator* ani = acc->GetComponent<Animator>();

				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack1", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2_1", Vector2::Zero, 0.09575f);

				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\1_2reg", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\2_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\3_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\4_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\6_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\7_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\8_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\8_2_sugar", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\9_sugar", Vector2::Zero, 0.1f);

				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\3_remon", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\5_remon", Vector2::Zero, 0.1f);

				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\2_berrybox", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\7_berrybox", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\8_berrybox", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\9_berrybox", Vector2::Zero, 0.1f);
				ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\10_berrybox", Vector2::Zero, 0.1f);
				ani->GetCompleteEvent(L"attack_type1dough_attack1") = std::bind([ani]()->void
				{
					ani->Play(L"attack_type1dough_attack2", false);
				});
			}
			mParts.insert(std::make_pair(EParts::ACC, acc));
		}

		mPhaseInfo.insert(std::make_pair(EPhaseType::PHASE1, std::map<EAttackType, std::vector<std::wstring>>()));

		{
			std::vector<std::wstring> vec;
			vec.push_back(L"camel_type1");
			vec.push_back(L"camel_type2");
			vec.push_back(L"camel_type3");
			mPhaseInfo[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type1, vec));
		}
		{
			std::vector<std::wstring> vec;
			vec.push_back(L"sugarbullettype1");
			vec.push_back(L"sugarbullettype2");
			vec.push_back(L"sugarbullettype3");
			vec.push_back(L"sugarbullettype4");
			mPhaseInfo[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type2, vec));
		}
		{
			std::vector<std::wstring> vec;
			vec.push_back(L"berrybulletType1");
			vec.push_back(L"berrybulletType2");
			vec.push_back(L"berrybulletType3");
			vec.push_back(L"berrybulletType4");
			mPhaseInfo[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type5, vec));
		}
		{
			std::vector<std::wstring> vec;
			vec.push_back(L"lemonbullettype1");
			vec.push_back(L"lemonbullettype2");
			vec.push_back(L"lemonbullettype3");
			vec.push_back(L"lemonbullettype4");
			mPhaseInfo[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type4, vec));
		}






		mAttackCheck.insert(std::make_pair(EPhaseType::PHASE1, std::map<EAttackType, SpawnInfo*>()));
		mAttackCheck[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type1, new SpawnInfo{ false,3.0,7,0,std::bind([this]()->void
		{
			P1AttackType1();
		}) }));
		mAttackCheck[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type2, new SpawnInfo{ false,3.0,8,0,std::bind([this]()->void
		{
			P1AttackType2();
		}) }));
		mAttackCheck[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type4, new SpawnInfo{ false,4.0,8,0,std::bind([this]()->void
		{
			P1AttackType4();
		}) }));
		mAttackCheck[EPhaseType::PHASE1].insert(std::make_pair(EAttackType::Type5, new SpawnInfo{ false,3.0,8,0,std::bind([this]()->void
		{
			P1AttackType5();
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
		int speed = rand() % 3 == 0 ? 1 : 2;
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
	void SaltBaker::P1AttackType4()
	{
		mActiveAttack = mPhaseInfo[EPhaseType::PHASE1][EAttackType::Type4];
		int str_cnt = mActiveAttack.size();
		int str_type = rand() % str_cnt;
		std::shared_ptr<GameObject> lemon = core::ObjectPool<LemonBullet>::Spawn();
		LemonBullet* cb = lemon->GetComponent<LemonBullet>();
		std::wstring ani_name = mActiveAttack[str_type];
		cb->SetAnimation(ani_name, true);
		cb->SetColInfo(ani_name);
		cb->CreateInfo(Vector2{ -1.0f,0.0f }, true);
		cb->Shoot();
		SceneManager::GetActiveScene()->AddGameObject(lemon, ELayerType::Bullet);
	}
	void SaltBaker::P1AttackType5()
	{
		mActiveAttack = mPhaseInfo[EPhaseType::PHASE1][EAttackType::Type5];
		int str_cnt = mActiveAttack.size();
		int str_type = rand() % str_cnt;
		std::shared_ptr<GameObject> berry = core::ObjectPool<BerryBullet>::Spawn();
		BerryBullet* bb = berry->GetComponent<BerryBullet>();
		std::wstring ani_name = mActiveAttack[str_type];

		bb->SetAnimation(ani_name, true);
		bb->SetColInfo(ani_name);
		bb->CreateInfo(Vector2{ 100.0f,200.0f });
		bb->Shoot();
		SceneManager::GetActiveScene()->AddGameObject(berry, ELayerType::Bullet);
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

