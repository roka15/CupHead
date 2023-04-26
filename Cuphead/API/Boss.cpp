#include "Boss.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Time.h"
namespace yeram_client
{
	Boss::Boss()
	{
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
		mPhaseType = EPhaseType::NONE;
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
	}
	
	void Boss::OnCollisionEnter(Collider* other)
	{
	}

	void Boss::OnCollisionStay(Collider* other)
	{
	}

	void Boss::OnCollisionExit(Collider* other)
	{
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
