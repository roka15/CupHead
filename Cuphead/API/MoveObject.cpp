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

	void MoveObject::CreateInfo(const Vector2& _speed, EDirType _dir, const Vector2& _kill_pos)
	{
		mEndPos = _kill_pos;
		mbEndFlag = true;
		CreateInfo(_speed, _dir);
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
			if (mbEndFlag == true)
			{
				if (pos.x < mEndPos.x)
				{
					SetActive(false);
					return;
				}
			}
			speed *= -1;
			break;
		case EDirType::RIGHT:
			if (mbEndFlag == true)
			{
				if (pos.x > mEndPos.x)
				{
					SetActive(false);
					return;
				}
			}
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
