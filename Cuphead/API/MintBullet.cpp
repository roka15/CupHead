#include "MintBullet.h"
#include "GameObject.h"
#include "Ground.h"
yeram_client::MintBullet::MintBullet() :ZigZagBullet()
{
	mbXFlag = true;
	mbYFlag = false;
}

yeram_client::MintBullet::~MintBullet()
{
}

void yeram_client::MintBullet::Initialize()
{
	ZigZagBullet::Initialize();
	mOwner->SetName(L"MintBullet");
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type1", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type2", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type3", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type4", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type1Death", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type2Death", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type3Death", Vector2::Zero, 0.05f);
	CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_AttackType1\\sb_p2_MintBullet\\Type4Death", Vector2::Zero, 0.05f);
	GetCompleteEvent(L"sb_p2_MintBulletType1Death") = std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	});
	GetCompleteEvent(L"sb_p2_MintBulletType2Death") = std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	});
	GetCompleteEvent(L"sb_p2_MintBulletType3Death") = std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	});
	GetCompleteEvent(L"sb_p2_MintBulletType4Death") = std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	});
}

void yeram_client::MintBullet::Update()
{
}

void yeram_client::MintBullet::Render(HDC hdc)
{
}

void yeram_client::MintBullet::Release()
{
	Bullet::Release();
}

void yeram_client::MintBullet::OnCollisionEnter(Collider* other)
{
	Bullet::OnCollisionEnter(other);
}

void yeram_client::MintBullet::OnCollisionStay(Collider* other)
{
}

void yeram_client::MintBullet::OnCollisionExit(Collider* other)
{
}

void yeram_client::MintBullet::Shoot()
{
	ZigZagBullet::Shoot();
}

void yeram_client::MintBullet::Death(Collider* _other)
{
	if (mbDeath == true)
		return;
	Bullet::Death(_other);
	Ground* ground = _other->GetOwner()->GetComponent<Ground>();
	if (ground != nullptr)
	{
		if (mbDeath == false)
		{
			mbDeath = true;
			DeathPlay();
		}
	}
}

void yeram_client::MintBullet::DeathPlay()
{
	std::wstring ani_name = mAni->GetCurAniName();
	mAni->Play(ani_name + L"Death", false);
}
