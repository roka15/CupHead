#include "Monster.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Time.h"
namespace yeram_client
{
	Monster::Monster():Script()
	{
		SetName(L"Monster");
	}

	Monster::~Monster()
	{

	}

	void Monster::Initialize()
	{
		mOwner->SetName(L"Monster");
		mOwner->SetLayerType(ELayerType::Monster);
		GameObject* owner = GetOwner();
		mMoveObject = owner->AddComponent<MoveObject>();
		mCol = owner->AddComponent<Collider>();
		mAni = owner->AddComponent<Animator>();
		mTransform = owner->GetComponent<Transform>();
		mTime = 0.0;
		Script::Initialize();
	}

	void Monster::Update()
	{
		mTime += Time::DeltaTime();
	}

	void Monster::Render(HDC hdc)
	{
	}

	void Monster::Release()
	{
		Script::Release();
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
		Death(other);
	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}

	void Monster::Death(Collider* _other)
	{
	}

	void Monster::Attack()
	{
	}

	void Monster::Intro()
	{
	}

	void Monster::SetColCenter()
	{
		Vector2 size = mAni->GetSpriteSize();
		const Vector2& scale = mTransform->GetScale();
		size *= scale;
		mCol->SetSize(size / 2);
		mCol->SetCenter(Vector2{ (-size.x / 4) ,-size.y + (size.y / 4) });
	}

}
