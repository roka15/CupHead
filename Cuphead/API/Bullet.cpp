#include "Bullet.h"
#include "GameObject.h"
#include "Time.h"
#include "Application.h"
extern  yeram_client::Application application;
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
		Vector2& pos = mTransform->GetPos();
		pos.x += mDirVector.x * mSpeed * Time::DeltaTime();
		pos.y += mDirVector.y * mSpeed * Time::DeltaTime();
		//목표 지점까지 이동.

		//update 후 check list 
		
	    //1.목표지점 도달
		
		
		//2.맵 밖으로 나감.
		if (MapOutCheck() == true)
		{
 			SceneManager::RemoveObject(GetOwner());
		}
		
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
		mSpeed = 1000.0f;
		mDirVector = Vector2::Zero;
		mID = 0;
		if (GetOwner()->GetName()!=L"Player")
		{
			mbParry = rand() % 2;
		}
		mDamage = 1;
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		//3.충돌
	
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
		std::wstring key = mAni->CreateAnimations(_path, _offset, _duration, _alpha);
		mAni->Play(key, true);
	}

	void Bullet::SetColInfo()
	{
		const Vector2 size = mAni->GetSpriteSize();
		mColider->SetCenter(Vector2{ -(size.x / 2),-size.y });
		mColider->SetSize(size);
	}

	void Bullet::CreateInfo(const Vector2& _startpos, const Vector2& _endpos)
	{
		Reset();
		SetPos(_startpos);
		SetEndPos(_endpos);
		SetColInfo();
		mStartPos = _startpos;
	
		mDirVector = mEndPos-mStartPos;
		mDirVector = mDirVector.Normalize();
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
