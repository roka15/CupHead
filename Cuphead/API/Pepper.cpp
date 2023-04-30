#include "Pepper.h"
#include "GameObject.h"
#include "Application.h"
#include "MoveObject.h"
extern yeram_client::Application application;
namespace yeram_client
{
	std::vector<Pepper::SpawnInfo> Pepper::mSpawners;
	bool Pepper::mbSpawnInit = false;
	const int Pepper::mSpawnMax = 4;
	Pepper::Pepper() :Monster()
	{
		SetName(L"Pepper");
	}

	Pepper::~Pepper()
	{
	}

	void Pepper::Initialize()
	{
		mOwner->SetName(L"Pepper");
		Vector2 winsize = application.GetWindowSize();
		if (mbSpawnInit == false)
		{
			mbSpawnInit = true;
			mSpawners.push_back(SpawnInfo{ false,Vector2{100.0f,250.0f} });
			mSpawners.push_back(SpawnInfo{ false,Vector2{winsize.x-100.0f,250.0f} });
			mSpawners.push_back(SpawnInfo{ false,Vector2{100.0f,winsize.y-50.0f} });
			mSpawners.push_back(SpawnInfo{ false,Vector2{winsize.x - 100.0f,winsize.y-50.0f} });
		}
		Monster::Initialize();
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\intro", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\Idle", Vector2::Zero, 0.05f);
		
		mAni->GetCompleteEvent(L"sb_p2_pepperintro") = std::bind([this]()->void
		{
			mAni->Play(L"sb_p2_pepperIdle", true);
		});
		
		mMoveObject->SetActive(false);
	}

	void Pepper::Update()
	{
	}

	void Pepper::Render(HDC hdc)
	{
	}

	void Pepper::Release()
	{
	}

	void Pepper::OnCollisionEnter(Collider* other)
	{
	}

	void Pepper::OnCollisionStay(Collider* other)
	{
	}

	void Pepper::OnCollisionExit(Collider* other)
	{
	}

	void Pepper::Death(Collider* _other)
	{
	}

	void Pepper::Attack()
	{
	}

	void Pepper::Intro()
	{
		mAni->Play(L"sb_p2_pepperintro", false);
		SetColCenter();
	}


	void Pepper::SetSpawnPos()
	{
		for (auto& spawner : mSpawners)
		{
			if (spawner.mbSpawn == false)
			{
				spawner.mbSpawn = true;
				mTransform->SetPos(spawner.mPos);
				return;
			}
		}
	}



}
