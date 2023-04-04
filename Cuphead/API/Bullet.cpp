#include "Bullet.h"

#include "GameObject.h"

namespace yeram_client
{
	Bullet::Bullet() :Script()
	{
		SetName(L"Bullet");
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
		GameObject* owner = GetOwner();
		mColider = owner->AddComponent<Collider>();
		mTransform = owner->GetComponent<Transform>();
		mAni = owner->AddComponent<Animator>();
	}

	void Bullet::Update()
	{
		//��ǥ �������� �̵�.

		//update �� check list 
		
	    //1.��ǥ���� ����
		
		
		//2.�� ������ ����.
		
		
	}

	void Bullet::Render(HDC hdc)
	{
	}

	void Bullet::Release()
	{
	}

	void Bullet::Reset()
	{
		mDeSpawnDistance = 0.0f;
		mEndPos = Vector2::Zero;
		mSpeed = Vector2::Zero;
		mID = 0;
		if (GetOwner()->GetName()!=L"Player")
		{
			mbParry = rand() % 2;
		}
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		//3.�浹
	
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
	}

	void Bullet::OnCollisionExit(Collider* other)
	{
	}

	void Bullet::SetScale(const Vector2& _scale)
	{
		mTransform->SetScale(_scale);
	}

	void Bullet::SetPos(const Vector2& _pos)
	{
		mTransform->SetPos(_pos);
	}

	void Bullet::SetAnimation(std::wstring _path, Vector2 _offset, float _duration, bool _alpha)
	{
	}

	void Bullet::SetColCenter()
	{
	}

	bool Bullet::MapOutCheck()
	{
		return false;
	}

}
