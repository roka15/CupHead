#include "PepperBullet.h"
#include "GameObject.h"
#include "Ground.h"
#include "Player.h"
#include "MoveObject.h"
yeram_client::PepperBullet::PepperBullet()
{
}

yeram_client::PepperBullet::~PepperBullet()
{
}

void yeram_client::PepperBullet::Initialize()
{
	Bullet::Initialize();
	mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\pepperbullet\\Type1", Vector2::Zero, 0.05f);
	mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\pepperbullet\\Type2", Vector2::Zero, 0.05f);
	mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\pepperbullet\\Type3", Vector2::Zero, 0.05f);
	mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\pepperbullet\\Type1Death", Vector2::Zero, 0.05f);
	mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\pepperbullet\\Type3Death", Vector2::Zero, 0.05f);

	mAni->GetCompleteEvent(L"pepperbulletType1Death") = std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	});
	mAni->GetCompleteEvent(L"pepperbulletType3Death") = std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	});
	mAnis.push_back(L"pepperbulletType1");
	mAnis.push_back(L"pepperbulletType2");
	mAnis.push_back(L"pepperbulletType3");

	mMoveObject->SetArriveEvent(std::bind([this]()->void
	{
		GetOwner()->SetActive(false);
		SceneManager::RemoveObjectRequest(GetOwner());
	}));
}

void yeram_client::PepperBullet::Update()
{
}

void yeram_client::PepperBullet::Render(HDC hdc)
{
}

void yeram_client::PepperBullet::Release()
{
}

void yeram_client::PepperBullet::OnCollisionEnter(Collider* other)
{
	HomingBullet::OnCollisionEnter(other);
}

void yeram_client::PepperBullet::OnCollisionStay(Collider* other)
{
}

void yeram_client::PepperBullet::OnCollisionExit(Collider* other)
{
}

void yeram_client::PepperBullet::SetColInfo(std::wstring _ani_name)
{
	
}

void yeram_client::PepperBullet::Shoot()
{
	int index = rand() % mAnis.size();
	std::wstring ani_name = mAnis[index];
	mAni->Play(ani_name, false);

	Bullet::SetColInfo(ani_name);

	std::shared_ptr<GameObject> player_obj = SceneManager::GetActiveScene()->FindObject(L"Player");
	Vector2 target = player_obj->GetComponent<Transform>()->GetPos();
	GetTargetPos(target);
}

void yeram_client::PepperBullet::Death(Collider* _other)
{
	if (mbDeath == true)
		return;
	GameObject* owner = _other->GetOwner();
	Player* player = owner->GetComponent<Player>();
	Ground* ground = owner->GetComponent<Ground>();
	if (player != nullptr|| ground != nullptr)
	{
		std::wstring aniname = mAni->GetCurAniName();

		if (aniname == L"pepperbulletType3")
		{
			mAni->Play(aniname + L"Death", false);
		}
		else
		{
			mAni->Play(L"pepperbulletType1Death", false);
		}
		mbDeath = true;
	}
	
}
