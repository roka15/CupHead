#include "Monster.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Time.h"
#include "PlayerBullet.h"
#include "Application.h"
extern yeram_client::Application application;
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
		TakeDamage(other);
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

	void Monster::Idle()
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

	void Monster::TakeDamage(Collider* other)
	{
		GameObject* obj = other->GetOwner();
		PlayerBullet* pb = obj->GetComponent<PlayerBullet>();
		if (pb != nullptr)
		{
			mHP--;
		}
	}

	std::wstring Monster::GetSpawnDir()
	{
		std::wstring name;
		Vector2 center = application.GetWindowSize() / 2.0f;
		Vector2 pos = mTransform->GetPos();
		if (pos.x < center.x && pos.y < center.y)//left up
		{
			name = L"LeftUp";
		}
		else if (pos.x<center.x && pos.y>center.y)//left down
		{
			name = L"LeftDown";
		}
		else if (pos.x > center.x && pos.y < center.y)//right up
		{
			name = L"RightUp";
		}
		else if (pos.x > center.x && pos.y > center.y)//right down
		{
			name = L"RightDown";
		}
		return name;
	}

}
