#include "MoveObject.h"
#include "GameObject.h"
#include "Time.h"
#include "Application.h"
extern yeram_client::Application application;
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
		mArriveEvent = std::bind([this]()->void {SetActive(false); });
	}

	void MoveObject::Update()
	{
		if (mbWave == true)
		{
			WaveMove();
		}
		else
		{
			Move();
		}
	}

	void MoveObject::Render(HDC hdc)
	{
	}

	void MoveObject::Release()
	{
	}

	void MoveObject::CreateInfo(const Vector2& _speed, EDirType _dir)
	{
		mTf = GetOwner()->GetComponent<Transform>();
		mSpeed = _speed;
		mDir = _dir;
	}

	void MoveObject::CreateInfo(const Vector2& _speed, EDirType _dir, const Vector2& _kill_pos, bool _despawn, bool _outcheck)
	{
		mEndPos = _kill_pos;
		mbEndFlag = true;
		CreateInfo(_speed, _dir);
		Vector2 pos = mTf->GetPos();
		mDirpos = mEndPos - pos;
		mDirpos.Normalize();
		mStartPos = pos;
		mbOutCheck = _outcheck;
		mbDespawn = _despawn;
		mbArrive = false;
	}

	void MoveObject::CreateInfo(const Vector2& _speed, const Vector2& _dir, bool _despawn, bool _outcheck)
	{
		mTf = GetOwner()->GetComponent<Transform>();
		mbEndFlag = true;
		mSpeed = _speed;
		mDirpos = _dir;
		Vector2 pos = mTf->GetPos();
		mStartPos = pos;
		mbOutCheck = _outcheck;
		mbDespawn = _despawn;
		mbArrive = false;
	}

	void MoveObject::CreateInfo(const Vector2& _speed, const Vector2& _dir, const Vector2& _kill_pos, bool _despawn, bool _outcheck)
	{
		mTf = GetOwner()->GetComponent<Transform>();
		mbEndFlag = true;
		mSpeed = _speed;
		mDirpos = _dir;

		Vector2 pos = mTf->GetPos();
		mStartPos = pos;
		mEndPos = _kill_pos;
		mbOutCheck = _outcheck;
		mbDespawn = _despawn;
		mbArrive = false;
	}

	void MoveObject::WaveMove()
	{
		GameObject* owner = this->GetOwner();
		GameObject* obj = owner->GetParent();
		Vector2 pos = obj == nullptr ? mTf->GetPos() : mTf->GetOffset();
		pos.x += mDirpos.x * mSpeed.x * Time::DeltaTime();
		pos.y += mEndPos.y * sinf(pos.x * (3.14159254f / 180.0f)) * Time::DeltaTime();

		mTf->SetPos(pos);
	}




	void MoveObject::Move()
	{
		GameObject* owner = this->GetOwner();
		GameObject* obj = owner->GetParent();
		Vector2 originpos = mTf->GetPos();
		Vector2 pos = obj == nullptr ? mTf->GetPos() : mTf->GetOffset();
		float speed = mSpeed.x;

		bool map_out_flag = false;
		bool xflag = false;
		bool yflag = false;
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
			if (mbOutCheck == true)
			{
				Animator* ani = GetOwner()->GetComponent<Animator>();
				SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
				Vector2 size;
				Vector2 winsize = application.GetWindowSize();
				if (ani != nullptr)
				{
					if (ani->UseAnimation() == true)
						size = ani->GetSpriteSize();
				}
				else if (sprite != nullptr)
				{
					size.x = sprite->GetWidth();
					size.y = sprite->GetHeight();
				}
				size *= mTf->GetScale();
				if (originpos.x + size.x < -size.x || originpos.x - size.x>winsize.x + size.x
					|| originpos.y + size.y <-size.y || originpos.y - size.y>winsize.y + size.y)
				{
					if ((mStartPos.x < -size.x && originpos.x + size.x < -size.x)
						|| (mStartPos.x > winsize.x + size.x && originpos.x - size.x > winsize.x + size.x))
					{
						xflag = false;
					}
					else
					{
						xflag = true;
					}

					if ((mStartPos.y < -size.y && originpos.y + size.y < -size.y)
						|| (mStartPos.y > winsize.y + size.y && originpos.y - size.y > winsize.y + size.y))
					{
						yflag = false;
					}
					else
					{
						yflag = true;
					}
					if (xflag == true && yflag == true)
					{
						if (mbDespawn == true)
						{
							SceneManager::RemoveObjectRequest(GetOwner());
							return;
						}
					}
				}
				int a = 0;
			}
			//else
			{
				if (mStartPos.x < mEndPos.x)
				{
					if (originpos.x >= mEndPos.x)
						xflag = true;
					else if (mbOutCheck == true && map_out_flag == false)
						xflag = false;
				}
				else if (mStartPos.x > mEndPos.x)
				{
					if (originpos.x <= mEndPos.x)
						xflag = true;
					else if (mbOutCheck == true && map_out_flag == false)
						xflag = false;
				}
				else if (originpos.x == mEndPos.x)
					xflag = true;

				if (mStartPos.y < mEndPos.y)
				{
					if (originpos.y >= mEndPos.y)
						yflag = true;
					else if (mbOutCheck == true && map_out_flag == false)
						yflag = false;
				}
				else if (mStartPos.y > mEndPos.y)
				{
					if (originpos.y <= mEndPos.y)
						yflag = true;
					else if (mbOutCheck == true && map_out_flag == false)
						yflag = false;
				}
				else if (originpos.y == mEndPos.y)
					yflag = true;
			}
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
			mbArrive = true;
			mArriveEvent();
			return;
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

	void MoveObject::SetEndPos()
	{
		Vector2 winsize = application.GetWindowSize();
		SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
		Animator* ani = GetOwner()->GetComponent<Animator>();
		Vector2 size;
		if (ani != nullptr)
			size = ani->GetSpriteSize();
		else
			size = Vector2{ sprite->GetWidth(),sprite->GetHeight() };
		if (mbEndFlag == false)
		{
			if (mDir == EDirType::LEFT)
			{
				mEndPos = Vector2{ -size.x,mTf->GetPos().y };
			}
			else if (mDir == EDirType::RIGHT)
			{
				mEndPos = Vector2{ winsize.x + size.x,mTf->GetPos().y };
			}
		}
		else
		{
			Vector2 winsize = application.GetWindowSize();
			SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
			Animator* ani = GetOwner()->GetComponent<Animator>();
			Vector2 size;
			if (ani != nullptr)
				size = ani->GetSpriteSize();
			else
				size = Vector2{ sprite->GetWidth(),sprite->GetHeight() };

			if (mDirpos.x < 0)
			{
				mEndPos.x = -size.x;
			}
			else if (mDirpos.x > 0)
			{
				mEndPos.x = winsize.x + size.x;
			}
			else
			{
				mEndPos.x = mTf->GetPos().x;
			}

			if (mDirpos.y < 0)
			{
				mEndPos.y = -size.y;
			}
			else if (mDirpos.y > 0)
			{
				mEndPos.y = winsize.y + size.y;
			}
			else
			{
				mEndPos.y = mTf->GetPos().y;
			}
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
