#include "Boss.h"
#include "GameObject.h"
#include "MoveObject.h"

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
	}

	void Boss::Update()
	{
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

}
