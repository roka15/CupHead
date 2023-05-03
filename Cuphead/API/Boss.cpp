#include "Boss.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Time.h"
#include "PlayerBullet.h"
#include "Pepper.h"
namespace yeram_client
{
	Boss::Boss():Script()
	{
		SetName(L"Boss");
	}

	Boss::~Boss()
	{
	}

	void Boss::Initialize()
	{
		GameObject* owner = GetOwner();
		mMoveObject = owner->AddComponent<MoveObject>();
		mCol = owner->AddComponent<Collider>();
		mAni = owner->AddComponent<Animator>();
		mTransform = owner->GetComponent<Transform>();
		mPhaseType = EPhaseType::PHASE1;
		mbChagePhase = true;
		Script::Initialize();
	}

	void Boss::Update()
	{
		mTime += Time::DeltaTime();
		/*switch (mPhaseType)
		{
		case EPhaseType::PHASE1:
			Phase1();
			break;
		case EPhaseType::PHASE2:
			Phase2();
			break;
		case EPhaseType::PHASE3:
			Phase3();
			break;
		}*/
	}

	void Boss::Render(HDC hdc)
	{
	}

	void Boss::Release()
	{
		Script::Release();
	}

	void Boss::OnCollisionEnter(Collider* other)
	{
		GameObject* owner = other->GetOwner();
		PlayerBullet* player_bullet = owner->GetComponent<PlayerBullet>();
		Pepper* pepper = owner->GetComponent<Pepper>();
		if (player_bullet != nullptr|| pepper !=nullptr)
		{
			TakeDamage();
		}
	}

	void Boss::OnCollisionStay(Collider* other)
	{
	}

	void Boss::OnCollisionExit(Collider* other)
	{
	}

	void Boss::TakeDamage()
	{
		mHP--;
		if (mbChagePhase == true)
		{
			return;
		}
		if ((mMaxHP / 3) < mHP&& mHP <= mMaxHP - (mMaxHP / 3)&&mPhaseType==EPhaseType::PHASE1)//phase 2 전환
		{
			mbChagePhase = true;
			Phase2();
		}
		else if (mHP < (mMaxHP / 3) && mPhaseType == EPhaseType::PHASE2) // phase 3 전환
		{
			mbChagePhase = true;
			Phase3();
		}
	}

	void Boss::Phase1()
	{

	}

	void Boss::Phase2()
	{
	}

	void Boss::Phase3()
	{
	}

}
