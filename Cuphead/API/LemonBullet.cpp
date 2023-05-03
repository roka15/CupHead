#include "LemonBullet.h"
#include "GameObject.h"
#include "Application.h"
#include "MoveObject.h"
extern yeram_client::Application application;
namespace yeram_client
{
	LemonBullet::LemonBullet() :Bullet(), mSpeed(300.0f, 100.0f)
	{
	}

	LemonBullet::~LemonBullet()
	{
	}

	void LemonBullet::Initialize()
	{
		Bullet::Initialize();
		Vector2 winsize = application.GetWindowSize();
	
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\lemonbullet\\type1", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\lemonbullet\\type2", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\lemonbullet\\type3", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type4\\lemonbullet\\type4", Vector2::Zero, 0.05f);


	}

	void LemonBullet::Update()
	{
	}

	void LemonBullet::Render(HDC hdc)
	{
	}

	void LemonBullet::Release()
	{
	}

	void LemonBullet::OnCollisionEnter(Collider* other)
	{
		Bullet::OnCollisionEnter(other);
	}

	void LemonBullet::OnCollisionStay(Collider* other)
	{
	}

	void LemonBullet::OnCollisionExit(Collider* other)
	{
	}

	void LemonBullet::Shoot()
	{
		Bullet::Shoot();
	}

	void LemonBullet::Death(Collider* _other)
	{
		if (mbDeath == true)
			return;
		Bullet::Death(_other);
	}

	void LemonBullet::DeathPlay()
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	}

	void LemonBullet::CreateInfo(const Vector2& _dirpos, bool _dir)
	{
		//목표1 도달시 y 증가 위/아래 랜덤 저장.
		Vector2 dir = _dirpos;
		bool flag = rand() % 2;
		dir.Normalize();
		if (flag == true)
		{
			dir.y = -1.0f;
		}
		else
		{
			dir.y = 1.0f;
		}
		dir.x = 0.0f;
		mDir.push(dir);
		//목표2 도달 시 왼/오 정보 저장. + 스폰 x 값 저장.
		dir = _dirpos;
		Vector2 startpos;
		Vector2 endpos[3];

		if (_dirpos.x < 0)
		{
			dir.x = 1.0f;
			endpos[2].x= startpos.x = application.GetWindowSize().x;
			endpos[0].x = 0.0f;
		}
		else
		{
			dir.x = -1.0f;
			endpos[2].x = startpos.x = 0.0f;
			endpos[0].x = application.GetWindowSize().x;
		}
		mDir.push(dir);
		endpos[1].x = endpos[0].x;
		endpos[1].y = flag == true ? endpos[0].y - 100 : endpos[0].y + 100;
		mArrivePos.push(endpos[1]);
		endpos[2].y = endpos[1].y;
		mArrivePos.push(endpos[2]);
		
		startpos.y = rand() % (int)(application.GetWindowSize().y-10)+10;
		endpos[0].y = startpos.y;
		mMoveObject->SetArriveEvent(std::bind([this]()->void
		{
			NextInfo();
		}));
	
		Bullet::CreateInfo(mSpeed, startpos, _dirpos, endpos[0],true);
	}

	void LemonBullet::NextInfo()
	{
		if (mArrivePos.empty() == true)
		{
			SceneManager::RemoveObjectRequest(GetOwner());
			return;
		}
		else
		{
			bool flag = mDir.size() % 2 == 0 ? true : false;
			Vector2 dir = mDir.front();
			mDir.pop();
			Vector2 startpos = mTransform->GetPos();
			Vector2 endpos = mArrivePos.front();
			if (flag == true)
			{
				endpos.x = startpos.x;
				endpos.y = startpos.y + endpos.y;
			}
			else
			{
				endpos.y = startpos.y;
			}
	
			mArrivePos.pop();
			mMoveObject->SetArriveEvent(std::bind([this]()->void
			{
				NextInfo();
			}));
			Bullet::CreateInfo(mSpeed, startpos, dir, endpos, true);
		}
	}

	

	
}
