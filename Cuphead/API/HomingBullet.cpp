#include "HomingBullet.h"
#include "GameObject.h"
#include "MoveObject.h"
namespace yeram_client
{
	HomingBullet::HomingBullet() :mSpeed(Vector2{200.0f,200.0f})
	{
	}

	HomingBullet::~HomingBullet()
	{
	}

	void HomingBullet::Initialize()
	{
	}

	void HomingBullet::Update()
	{
	}

	void HomingBullet::Render(HDC hdc)
	{
	}

	void HomingBullet::Release()
	{
	}

	void HomingBullet::OnCollisionEnter(Collider* other)
	{
		Bullet::OnCollisionEnter(other);
	}

	void HomingBullet::OnCollisionStay(Collider* other)
	{
	}

	void HomingBullet::OnCollisionExit(Collider* other)
	{
	}

	void HomingBullet::Shoot()
	{
	}

	void HomingBullet::SetColInfo(std::wstring _ani_name)
	{
	}

	void HomingBullet::Death(Collider* _other)
	{
	}

	void HomingBullet::GetTargetPos(Vector2 _target)
	{
		Vector2 pos = mTransform->GetPos();
		Vector2 dir = _target - pos;
		dir.Normalize();
		mMoveObject->CreateInfo(mSpeed, dir,true,true);
	}

}
