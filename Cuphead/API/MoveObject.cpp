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

	void MoveObject::CreateInfo(const Vector2& _speed, EDirType _dir)
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
		Vector2 pos = mTf->GetPos();
		mDirpos = mEndPos - pos;
		mDirpos.Normalize();
		mStartPos = pos;
	}


	void MoveObject::Move()
	{
		GameObject* owner = this->GetOwner();
		GameObject* obj = owner->GetParent();
		Vector2 originpos = mTf->GetPos();
		Vector2 pos = obj == nullptr ? mTf->GetPos() : mTf->GetOffset();
		float speed = mSpeed.x;
		if (mbEndFlag == false)
		{
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

		}
		else
		{
			bool xflag = false;
			bool yflag = false;
			if (mStartPos.x < mEndPos.x)
			{
				if (originpos.x >= mEndPos.x)
					xflag = true;
			}
			else if (mStartPos.x > mEndPos.x)
			{
				if (originpos.x <= mEndPos.x)
					xflag = true;
			}
			if (mStartPos.y < mEndPos.y)
			{
				if (originpos.y >= mEndPos.y)
					yflag = true;
			}
			else if (mStartPos.y > mEndPos.y)
			{
				if (originpos.y <= mEndPos.y)
					yflag = true;
			}

			if (xflag == false)
			{
				pos.x += mDirpos.x * mSpeed.x * Time::DeltaTime();
			}
			if (yflag == false)
			{
				pos.y += mDirpos.y * mSpeed.y * Time::DeltaTime();
			}
			if (xflag == true && yflag == true)
			{
				SetActive(false);
				return;
			}
		}

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
