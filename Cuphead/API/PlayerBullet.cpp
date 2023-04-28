#include "PlayerBullet.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "CookieBullet.h"
#include "SaltBaker.h"
namespace yeram_client
{
	PlayerBullet::PlayerBullet() :Bullet()
	{
	}

	PlayerBullet::~PlayerBullet()
	{
	}
	void PlayerBullet::Initialize()
	{
		Bullet::Initialize();
		SetScale(Vector2{ 0.5f,0.5f });
		mSpeed = Vector2{ 800.0f,600.0f };
		mOwner->SetActive(false);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\Right", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\Left", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\Down", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\Up", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\DownLeft", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\UpLeft", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\DownRight", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_intro\\UpRight", Vector2::Zero, 0.01);

		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\Right", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\Left", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\Down", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\Up", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\DownLeft", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\UpLeft", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\DownRight", Vector2::Zero, 0.01);
		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_main\\UpRight", Vector2::Zero, 0.01);


		mAni->CreateAnimations(L"..\\Resources\\weapon\\normal_shot_death", Vector2::Zero, 0.01);

		mAni->GetCompleteEvent(L"normal_shot_introRight") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainRight", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introLeft") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainLeft", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introDown") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainDown", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introUp") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainUp", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introUpLeft") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainUpLeft", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introDownLeft") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainDownLeft", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introUpRight") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainUpRight", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"normal_shot_introDownRight") = std::bind([this]()->void
		{
			mAni->Play(L"normal_shot_mainDownRight", true);
			mColider->SetActive(true);
		});
		mAni->GetCompleteEvent(L"weaponnormal_shot_death") = std::bind([this]()->void
		{
			SceneManager::RemoveObjectRequest(mOwner);
		});
		//mAni->Play(L"normal_shot_introRight",false);
	}
	void PlayerBullet::Update()
	{
	}
	void PlayerBullet::Render(HDC hdc)
	{
	}
	void PlayerBullet::Release()
	{
	}
	void PlayerBullet::Shoot()
	{
		Bullet::Shoot();

		std::wstring key = mAni->GetDirAniKey(L"normal_shot_intro", mDirType);
		mAni->Play(key, false);
	}
	void PlayerBullet::Shoot(std::wstring _dirstr)
	{
		Bullet::Shoot();
		std::wstring key = L"normal_shot_intro" + _dirstr;
		std::wstring colanikey = L"normal_shot_main" + _dirstr;
		EDirType h_key = EDirType::STAY, v_key = EDirType::STAY;
		mAni->GetDirAniKey(h_key, v_key, _dirstr);

		if (v_key != EDirType::STAY && h_key != EDirType::STAY)
		{
			SetDiagonalColInfo(v_key, colanikey);
		}
		else
		{
			SetColInfo(colanikey);
		}
		mAni->Play(key, false);
		SetEndPos();
		mColider->SetActive(true);
	}
	void PlayerBullet::Death(Collider* _other)
	{
		Bullet::Death(_other);
		CookieBullet* cookie = _other->GetOwner()->GetComponent<CookieBullet>();
		SaltBaker* salt = _other->GetOwner()->GetComponent<SaltBaker>();
		if (cookie != nullptr||salt!=nullptr)
		{
			mMoveObject->SetActive(false);
			mColider->SetActive(false);
			mAni->Play(L"weaponnormal_shot_death", false);
		}
	}
	void PlayerBullet::CreateInfo(const Vector2& _startpos, const Vector2 _dir)
	{
		if (_dir.x > 0)
			mDirType = EDirType::RIGHT;
		else
			mDirType = EDirType::LEFT;
		mMoveObject->SetArriveEvent(std::bind([this]()->void
		{
			mAni->Play(L"weaponnormal_shot_death", false);
		}));
		Bullet::CreateInfo(mSpeed, _startpos, _dir, true);
	}
	void PlayerBullet::SetDiagonalColInfo(EDirType _vertical_dir, std::wstring _ani_name)
	{
		Vector2 size = mAni->GetSpriteSize(_ani_name);
		const Vector2& scale = mTransform->GetScale();
		size *= scale;
		Vector2 half_size = size / 2.0f;
		mColider->SetSize(half_size);

		if (_vertical_dir == EDirType::UP)
		{
			mColider->SetCenter(Vector2{ (-size.x / 4.0f) ,(-size.y) + (size.y / 4) });
		}
		else if (_vertical_dir == EDirType::DOWN)
		{
			mColider->SetCenter(Vector2{ (-size.x / 4.0f) ,(-size.y) + (size.y / 4) });
		}
		//mColider->SetCenter(Vector2{ -(size.x / 2),-size.y });

	}
}

