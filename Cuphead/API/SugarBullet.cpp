#include "SugarBullet.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Player.h"
namespace yeram_client
{
	SugarBullet::SugarBullet() :ZigZagBullet()
	{
	}
	SugarBullet::~SugarBullet()
	{
	}
	void SugarBullet::Initialize()
	{
		ZigZagBullet::Initialize();
		mOwner->SetName(L"SugarBullet");
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\sugarbullet\\type1", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\sugarbullet\\type2", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\sugarbullet\\type3", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type2\\sugarbullet\\type4", Vector2::Zero, 0.05f);
	}
	void SugarBullet::Update()
	{
	}
	void SugarBullet::Render(HDC hdc)
	{
	}
	void SugarBullet::Release()
	{
	}
	void SugarBullet::OnCollisionEnter(Collider* other)
	{
		ZigZagBullet::OnCollisionEnter(other);
	}
	void SugarBullet::OnCollisionStay(Collider* other)
	{
		Death(other);
		ZigZagBullet::OnCollisionStay(other);
	}
	void SugarBullet::OnCollisionExit(Collider* other)
	{
	}
	void SugarBullet::Shoot()
	{
		ZigZagBullet::Shoot();
	}
	void SugarBullet::Death(Collider* _other)
	{
		if (mbDeath == true)
			return;
		Bullet::Death(_other);
		
	}
	void SugarBullet::DeathPlay()
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	}
	void SugarBullet::SetColInfo(std::wstring _ani_name)
	{
		Vector2 size = mAni->GetSpriteSize(_ani_name);
		const Vector2& scale = mTransform->GetScale();
		mColider->SetCenter(Vector2{ -size.x +((size.x/3)*2),-size.y + (size.y/5) });
		size *= scale;
		size.y -= size.y / 3;
		size.x -= size.x / 4;
		mColider->SetSize(size);
	}

	void SugarBullet::CreateInfo(const Vector2& _speed, const Vector2& _distance, const Vector2& _start_dir)
	{
		ZigZagBullet::CreateInfo(_speed, _distance, _start_dir);
		mMoveObject->SetWave(true); 
		SetColInfo(mAni->GetCurAniName());
	}
	
}
