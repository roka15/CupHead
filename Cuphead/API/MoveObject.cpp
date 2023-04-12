#include "MoveObject.h"
#include "GameObject.h"
#include "Time.h"
namespace yeram_client
{
	MoveObject::MoveObject() :Script()
	{
		SetName(L"MoveObject");
	}
	MoveObject::~MoveObject()
	{
	}

	void MoveObject::Initialize()
	{
		Script::Initialize();
	}

	void MoveObject::Update()
	{
		Move();
	}

	void MoveObject::Render(HDC hdc)
	{
	}

	void MoveObject::Release()
	{
	}

	void MoveObject::CreateInfo(const Vector2& _speed,EDirType _dir)
	{
		mSpeed = _speed;
		mDir = _dir;
		mTf = GetOwner()->GetComponent<Transform>();
	}


	void MoveObject::Move()
	{
		GameObject* owner = this->GetOwner();
		GameObject* obj = owner->GetParent();
		Vector2 pos = obj==nullptr? mTf->GetPos() : mTf->GetOffset();
		float speed = mSpeed.x;
		switch (mDir)
		{
		case EDirType::LEFT:
			speed *= -1;
			break;
		case EDirType::RIGHT:
			speed *= 1;
			break;
		}

		pos.x += speed * Time::DeltaTime();
		
		if (obj == nullptr)
		{
			mTf->SetPos(pos);
		}
		else
		{
			mTf->SetOffset(pos);
		}
		
	}

	void MoveObject::OnCollisionEnter(Collider* other)
	{
		
	}
	void MoveObject::OnCollisionStay(Collider* other)
	{
	}
	void MoveObject::OnCollisionExit(Collider* other)
	{
	}
}
