#include "ZigZagBullet.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Player.h"
namespace yeram_client
{
	ZigZagBullet::ZigZagBullet() :Bullet()
	{
		SetName(L"ZigZagBullet");
	}

	ZigZagBullet::ZigZagBullet(const ZigZagBullet& _other)
	{
		mUpAnimation = _other.mUpAnimation;
		mDownAnimation = _other.mDownAnimation;
		mDeathAnimation = _other.mDeathAnimation;
		mDir = _other.mDir;
		mDistance = _other.mDistance;
		mSpeed = _other.mSpeed;
	}

	ZigZagBullet::~ZigZagBullet()
	{
	}

	void ZigZagBullet::Initialize()
	{
		Bullet::Initialize();
	}

	void ZigZagBullet::Update()
	{

	}

	void ZigZagBullet::Render(HDC hdc)
	{
	}

	void ZigZagBullet::Release()
	{
		Bullet::Release();
	}

	void ZigZagBullet::Reset()
	{
	}

	void ZigZagBullet::OnCollisionEnter(Collider* other)
	{
		Bullet::OnCollisionEnter(other);
	}

	void ZigZagBullet::OnCollisionStay(Collider* other)
	{
		Bullet::OnCollisionStay(other);
	}

	void ZigZagBullet::OnCollisionExit(Collider* other)
	{
	}

	void ZigZagBullet::Shoot()
	{
		Bullet::Shoot();
	}

	void ZigZagBullet::Death(Collider* _other)
	{
		Bullet::Death(_other);
	}

	void ZigZagBullet::RegisterAniKey(const std::wstring& _up, const std::wstring& _down, const std::wstring& _death)
	{
		mUpAnimation = _up;
		mDownAnimation = _down;
		mDeathAnimation = _death;
		Bullet::SetColInfo(mUpAnimation);
	}

	void ZigZagBullet::CreateInfo(const Vector2& _speed, const Vector2& _distance, const Vector2& _start_dir)
	{

		mSpeed = _speed;
		mDistance = _distance;
		mDir = _start_dir;
		Vector2 pos = mTransform->GetPos();
		mStartpos = pos;
		pos.x += mDistance.x * mDir.x;
		pos.y += mDistance.y * mDir.y;
		mMoveObject->CreateInfo(mSpeed, mDir, pos, true, true);
		mMoveObject->SetArriveEvent(std::bind([this]()->void
		{
			NextInfoSetting();
		}));
	}

	const Vector2 ZigZagBullet::GetEndPos()
	{
		Vector2 pos = mTransform->GetPos();
		if (mbYFlag == true)
		{
			if (mDir.x > 0)
				pos.x += mDistance.x;
			else
			{
				pos.x -= mDistance.x;
			}

			if (mDir.y < 0)
				pos.y = mStartpos.y - mDistance.y;
			else
				pos.y = mStartpos.y + mDistance.y;
		}
		else if (mbXFlag == true)
		{
			if (mDir.y > 0)
				pos.y += mDistance.y;
			else
			{
				pos.y -= mDistance.y;
			}
			if (mDir.x < 0)
				pos.x = mStartpos.x - mDistance.x;
			else
				pos.x = mStartpos.x + mDistance.x;
		}

		return pos;
	}

	void ZigZagBullet::NextInfoSetting()
	{
		if (mbDeath == true)
			return;
		if (mMoveObject->IsArrive() == true)
		{
			if (mbYFlag == true)
			{
				mDir.y *= -1;
			}
			else if (mbXFlag == true)
			{
				mDir.x *= -1;
			}
			const Vector2& pos = GetEndPos();
			mMoveObject->CreateInfo(mSpeed, mDir, pos, true, true);
		}
	}

	void ZigZagBullet::SetColInfo(std::wstring _ani_name)
	{
		Vector2 size = mAni->GetSpriteSize(_ani_name);
		const Vector2& scale = mTransform->GetScale();
		mColider->SetCenter(Vector2{ -(size.x / 2),-size.y });
		size *= scale;
		mColider->SetSize(size);
	}

	std::function<void()>& ZigZagBullet::GetCompleteEvent(std::wstring _name)
	{
		return mAni->GetCompleteEvent(_name);
	}

}
