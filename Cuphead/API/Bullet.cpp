#include "Bullet.h"
#include "GameObject.h"
#include "Time.h"
#include "Application.h"
#include "MoveObject.h"
extern  yeram_client::Application application;
namespace yeram_client
{
	Bullet::Bullet() :Script()
	{
		SetName(L"Bullet");
	}

	Bullet::Bullet(const Bullet& _other)
	{
		mID = _other.mID;
		mDamage= _other.mDamage;
		mShotType= _other.mShotType;
		mbParry = _other.mbParry;
		mMoveObject = mOwner->AddComponent<MoveObject>();
		mColider = mOwner->AddComponent<Collider>();
		mTransform = mOwner->GetComponent<Transform>();
		mAni = mOwner->AddComponent<Animator>();;
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
		GameObject* owner = GetOwner();
		mMoveObject = owner->AddComponent<MoveObject>();
		mColider = owner->AddComponent<Collider>();
		mTransform = owner->GetComponent<Transform>();
		mAni = owner->AddComponent<Animator>();
	}

	void Bullet::Update()
	{


	}

	void Bullet::Render(HDC hdc)
	{
	}

	void Bullet::Release()
	{
		Script::Release();
	}

	void Bullet::Reset()
	{
		mID = 0;
		/*if (GetOwner()->GetName() != L"Player")
		{
			mbParry = rand() % 2;
		}*/
		mDamage = 1;
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		//3.Ãæµ¹
		Death(other);
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
		Death(other);
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

	void Bullet::CreateAnimation(std::wstring _path, Vector2 _offset, float _duration, bool _alpha)
	{
		mAni->CreateAnimations(_path, _offset, _duration, _alpha);
	}

	void Bullet::SetAnimation(std::wstring _name, bool _flag)
	{
		mAni->Play(_name, _flag);
	}

	void Bullet::SetAnimation(std::wstring _name, bool _flag, EDirType _dir)
	{
		std::wstring ani_key = mAni->GetDirAniKey(_name, _dir);
		mAni->Play(ani_key, _flag);
	}

	void Bullet::Shoot()
	{
		mOwner->SetActive(true);
	}

	void Bullet::Death(Collider* _other)
	{
		
	}

	void Bullet::SetColInfo(std::wstring _ani_name)
	{
		
		Vector2 size = mAni->GetSpriteSize(_ani_name);
		const Vector2& scale = mTransform->GetScale();
		size *= scale;
		mColider->SetSize(size);
		mColider->SetCenter(Vector2{ -(size.x / 2),-size.y });
		
	}

	void Bullet::CreateInfo(const Vector2& _speed, const Vector2& _startpos, const Vector2& _endpos)
	{
		Reset();
		SetPos(_startpos);
		Vector2 dir = _endpos - _startpos;
		dir = dir.Normalize();
		mMoveObject->CreateInfo(_speed, dir, true, true);
	}

	void Bullet::CreateInfo(const Vector2& _speed, const Vector2& _startpos, const Vector2& _dirpos, bool _dir)
	{
		Reset();
		SetPos(_startpos);
		Vector2 dir = _dirpos;
		dir = dir.Normalize();
		mMoveObject->CreateInfo(_speed, dir, true, true);
	}

	void Bullet::CreateInfo(const Vector2& _speed, const Vector2& _startpos, const Vector2& _dirpos, const Vector2& _killpos, bool _dir)
	{
		Reset();
		SetPos(_startpos);
		Vector2 dir = _dirpos;
		dir = dir.Normalize();
		mMoveObject->CreateInfo(_speed, dir, _killpos, true, true);
	}

	void Bullet::SetEndPos()
	{
		mMoveObject->SetEndPos();
	}


	bool Bullet::MapOutCheck()
	{
		const Vector2& winrect = application.GetWindowSize();
		const Vector2& pos = mTransform->GetPos();
		const Vector2& size = mAni->GetSpriteSize();
		if (pos.x + size.x <= 0.0f || pos.x - size.x >= winrect.x ||
			pos.y + size.y <= 0.0f || pos.y - size.y >= winrect.y)
			return true;

		return false;
	}

}
