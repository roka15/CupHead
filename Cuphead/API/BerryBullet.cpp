#include "BerryBullet.h"
#include "Application.h"
#include "GameObject.h"
#include "Ground.h"
#include "MoveObject.h"
extern yeram_client::Application application;
namespace yeram_client
{
	yeram_client::BerryBullet::BerryBullet() :mRange(Vector2{ (int)application.GetWindowSize().x, 0 })
	{

	}
	BerryBullet::~BerryBullet()
	{
	}
	void BerryBullet::Initialize()
	{
		Bullet::Initialize();
		Vector2 winsize = application.GetWindowSize();
		mDistance.x = 800.0f;
		mDistance.y = winsize.y;

		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type1", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type2", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type3", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type4", Vector2::Zero, 0.05f);

		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type1Death", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type2Death", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type3Death", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type5\\berrybullet\\Type4Death", Vector2::Zero, 0.05f);
	
		mAni->GetCompleteEvent(L"berrybulletType1Death") = std::bind([this]()->void
		{
			SceneManager::RemoveObjectRequest(GetOwner());
		});
		mAni->GetCompleteEvent(L"berrybulletType2Death") = std::bind([this]()->void
		{
			SceneManager::RemoveObjectRequest(GetOwner());
		});
		mAni->GetCompleteEvent(L"berrybulletType3Death") = std::bind([this]()->void
		{
			SceneManager::RemoveObjectRequest(GetOwner());
		});
		mAni->GetCompleteEvent(L"berrybulletType4Death") = std::bind([this]()->void
		{
			SceneManager::RemoveObjectRequest(GetOwner());
		});
	}
	void BerryBullet::Update()
	{
	}
	void BerryBullet::Render(HDC hdc)
	{
	}
	void BerryBullet::Release()
	{
	}
	void BerryBullet::OnCollisionEnter(Collider* other)
	{
		Bullet::OnCollisionEnter(other);
	}

	void BerryBullet::OnCollisionStay(Collider* other)
	{
	}

	void BerryBullet::OnCollisionExit(Collider* other)
	{
		Bullet::OnCollisionExit(other);
	}
	void BerryBullet::Shoot()
	{
		Bullet::Shoot();
	}
	void BerryBullet::Death(Collider* _other)
	{
		Bullet::Death(_other);
		GameObject* other_owner = _other->GetOwner();
		if (other_owner->GetName().compare(L"Player") == 0)
		{
			//데미지 주기
		}
		Ground* ground = other_owner->GetComponent<Ground>();
		if (ground != nullptr)
		{
			mMoveObject->SetActive(false);
			std::wstring aniname = mAni->GetCurAniName();
			mAni->Play(aniname + L"Death", false);
		}
	}
	
	void BerryBullet::CreateInfo(const Vector2& _speed)
	{
		const int x = mRange.x - mDistance.x;
		Vector2 spawn_point;
		Vector2 arrive_point;
		spawn_point.x = rand() % x+ mDistance.x;
		spawn_point.y = 0.0f;

		arrive_point.x = spawn_point.x - mDistance.x;
		arrive_point.y = spawn_point.y + mDistance.y;

		Vector2 dir = arrive_point - spawn_point;
		dir.Normalize();
		Vector2 dummyendpos = { -100.0f,1000.0f };
		Bullet::CreateInfo(_speed,spawn_point,dir,dummyendpos,true);
	}
}
