#include "MoveObject.h"
#include "GameObject.h"
#include "MoveObjectManager.h"

namespace yeram_client
{
	MoveObject::MoveObject() :Script()
	{
	}
	MoveObject::~MoveObject()
	{
	}

	void MoveObject::Initialize()
	{
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

	void MoveObject::CreateInfo(const Vector2& _speed, float _dspawn_time, const Vector2& _diff, const byte _outdir, const Vector2& _dir, const bool& _regular)
	{
		mStartPos = this->GetOwner()->GetComponent<Transform>()->GetPos();
		mSpeed = _speed;
		mDspawnTime = _dspawn_time;
		mDiff = _diff;
		mOutDirbit = _outdir;
		mDir = _dir;
		mbRegular = _regular;
	}


	void MoveObject::Move()
	{
		GameObject* owner = this->GetOwner();
		if (MoveObjectManager::MapOutCheck(owner) == true)
		{
			MoveObjectManager::SetSpawnPos(owner);
		}
		else
		{
			Transform* tf = owner->GetComponent<Transform>();
			Vector2 pos = tf->GetPos();
			pos.x += mSpeed.x * mDir.x;
			pos.y += mSpeed.y * mDir.y;
			tf->SetPos(pos);
		}
	}

	void MoveObject::OnCollisionEnter(Collider* other)
	{
		Collider* col = GetOwner()->GetComponent<Collider>();

	}
	void MoveObject::OnCollisionStay(Collider* other)
	{
	}
	void MoveObject::OnCollisionExit(Collider* other)
	{
	}
}
