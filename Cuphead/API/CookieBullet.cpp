#include "CookieBullet.h"
#include "GameObject.h"
namespace yeram_client
{
	CookieBullet::CookieBullet():ZigZagBullet()
	{
	}
	CookieBullet::~CookieBullet()
	{
	}
	void CookieBullet::Initialize()
	{
		ZigZagBullet::Initialize();
		mOwner->SetName(L"CookieBullet");
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type1\\1s", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type1\\1e", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type1\\2s", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type1\\2e", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\effect", Vector2::Zero, 0.1f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type2\\1s", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type2\\1e", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type2\\2s", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type2\\2e", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type3\\1s", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type3\\1e", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type3\\2s", Vector2::Zero, 0.05f);
		CreateAnimation(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_camel\\camel_type3\\2e", Vector2::Zero, 0.05f);
	    
		SetCompleteEvent(L"camel_type1");
		SetCompleteEvent(L"camel_type2");
		SetCompleteEvent(L"camel_type3");

	}
	void CookieBullet::Update()
	{
	}
	void CookieBullet::Render(HDC hdc)
	{
	}
	void CookieBullet::Release()
	{
	}
	void CookieBullet::OnCollisionEnter(Collider* other)
	{
	}
	void CookieBullet::OnCollisionStay(Collider* other)
	{
	}
	void CookieBullet::OnCollisionExit(Collider* other)
	{
	}
	void CookieBullet::Shoot()
	{
		ZigZagBullet::Shoot();
	}
	void CookieBullet::Death(Collider* _other)
	{
	}
	void CookieBullet::SetColInfo(std::wstring _ani_name)
	{
	}
	void CookieBullet::SetAnimation(std::wstring _name, bool _flag)
	{
		RegisterAniKey(_name + L"1s", _name + L"2s", L"dough_cameleffect");
		Bullet::SetAnimation(_name + L"1s", _flag);
	}
	void CookieBullet::NextInfoSetting()
	{
		ZigZagBullet::NextInfoSetting();
		if (mDir.y <= 0)
		{
			mAni->Play(mUpAnimation, false);
		}
		else if (mDir.y > 0)
		{
			mAni->Play(mDownAnimation, false);
		}
	}
	void CookieBullet::SetCompleteEvent(std::wstring _name)
	{
		std::wstring s1 = _name + L"1s";
		std::wstring s2 = _name + L"2s";

		GetCompleteEvent(_name + L"1s") = std::bind([this,_name]()->void
		{
			Bullet::SetAnimation(_name + L"1e", false);
		});
		GetCompleteEvent(_name + L"2s") = std::bind([this, _name]()->void
		{
			Bullet::SetAnimation(_name + L"2e", false);
		});
	}
}