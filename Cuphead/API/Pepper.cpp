#include "Pepper.h"
#include "GameObject.h"
#include "Application.h"
#include "MoveObject.h"
#include "ObjectPool.h"
#include "PepperBullet.h"
extern yeram_client::Application application;
namespace yeram_client
{
	std::vector<Pepper::SpawnInfo> Pepper::mSpawners;
	bool Pepper::mbSpawnInit = false;
	bool Pepper::mbAttackActive = false;
	const int Pepper::mSpawnMax = 4;
	Pepper::Pepper() :Monster(),mSkill(5.0,0.0)
	{
		SetName(L"Pepper");
		mHP = 4;
		mReSpawnTime = 5.0;
		mbReSpawn = false;
		mbDeath = false;
	}

	Pepper::~Pepper()
	{
	}

	void Pepper::Initialize()
	{
		mOwner->SetName(L"Pepper");
		mHP = 4;
		mReSpawnTime = 5.0;
		mbReSpawn = false;
		mbDeath = false;
		Audio* audio = GetOwner()->AddComponent<Audio>();
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
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\attackaniLeft", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\attackaniRight", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\DeathLeftDown", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\DeathRightDown", Vector2::Zero, 0.01f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\DeathLeftUp", Vector2::Zero, 0.05f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_2\\sb_p2_pepper\\DeathRightUp", Vector2::Zero, 0.01f);
		
		mAni->GetCompleteEvent(L"sb_p2_pepperintro") = std::bind([this]()->void
		{
			mAni->Play(L"sb_p2_pepperIdle", true);
		});
		mAni->GetCompleteEvent(L"sb_p2_pepperattackaniLeft") = std::bind([this]()->void
		{
			mAni->Play(L"sb_p2_pepperIdle", true);
			mbAttackActive = false;
		});
		mAni->GetCompleteEvent(L"sb_p2_pepperattackaniRight") = std::bind([this]()->void
		{
			mAni->Play(L"sb_p2_pepperIdle", true);
			mbAttackActive = false;
		});
		mMoveObject->SetActive(false);
	}

	void Pepper::Update()
	{
		if (mbSceneDeath == true)
		{
			GetOwner()->SetActive(false);
			return;
		}
		Monster::Update();
		if (mbReSpawn == true)
		{
			if (mTime - mDeSpawnStartTime >= mReSpawnTime)
			{
				GetOwner()->SetActive(true);
				SetSpawnPos();
				Idle();
				mAni->SetActive(true);
				mCol->SetActive(true);
				Init();
			}
			else
			{
				return;
			}
		}
	
		if (mTime - mSkill.GetUseTime() >= mSkill.GetCoolTime())
		{
			if (mbAttackActive == true)
				return;
			mSkill.SetUseTime(mTime);
			Attack();
			mbAttackActive = true;
		}
	}

	void Pepper::Render(HDC hdc)
	{
	}

	void Pepper::Release()
	{
	}

	void Pepper::OnCollisionEnter(Collider* other)
	{
		Monster::OnCollisionEnter(other);
	}

	void Pepper::OnCollisionStay(Collider* other)
	{
	}

	void Pepper::OnCollisionExit(Collider* other)
	{
	}

	void Pepper::Death(Collider* _other)
	{
		Audio* audio = GetOwner()->GetComponent<Audio>();
		Vector2 center = application.GetWindowSize()/2.0f;
		Vector2 pos = mTransform->GetPos();
		if (pos.x < center.x && pos.y<center.y)//left up
		{
			mSpawners[0].mbSpawn = false;
			mAni->Play(L"sb_p2_pepperDeathLeftUp", false);
			
			mMoveObject->CreateInfo(Vector2{ 800.0f,400.0f }, Vector2{ 1.0f,1.0f }, Vector2{ 1000.0f,500.0f }, true, true);
			mMoveObject->SetArriveEvent(std::bind([this,audio]()->void
			{
				mbReSpawn = true;
				mAni->SetActive(false);
				mCol->SetActive(false);
				mMoveObject->SetActive(false);
				mDeSpawnStartTime = mTime;
				audio->Play(L"boss_p2_pepper_death1", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_Disappear_01.wav", false);
				audio->Play(L"boss_p2_pepper_deathimpact1", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_LaunchImpact_01.wav", false);
				audio->Play(L"boss_p2_pepper_saltdamage1", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Vocal_Pain_01.wav", false);
			}));
			mMoveObject->SetActive(true);
		}
		else if (pos.x<center.x && pos.y>center.y)//left down
		{
			mSpawners[2].mbSpawn = false;
			mAni->Play(L"sb_p2_pepperDeathLeftDown", false);
			
			mMoveObject->CreateInfo(Vector2{ 800.0f,400.0f }, Vector2{ 1.0f,-1.0f }, Vector2{ 1000.0f,500.0f }, true, true);
			mMoveObject->SetArriveEvent(std::bind([this,audio]()->void
			{
				mbReSpawn = true;
				mAni->SetActive(false);
				mCol->SetActive(false);
				mMoveObject->SetActive(false);
				mDeSpawnStartTime = mTime;
				audio->Play(L"boss_p2_pepper_death2", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_Disappear_02.wav", false);
				audio->Play(L"boss_p2_pepper_deathimpact2", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_LaunchImpact_02.wav", false);
				audio->Play(L"boss_p2_pepper_saltdamage2", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Vocal_Pain_02.wav", false);

			})); 
			mMoveObject->SetActive(true);
		}
		else if (pos.x > center.x && pos.y < center.y)//right up
		{
			mSpawners[1].mbSpawn = false;
			mAni->Play(L"sb_p2_pepperDeathRightUp", false);
		
			mMoveObject->CreateInfo(Vector2{ 800.0f,400.0f }, Vector2{ -1.0f,1.0f }, Vector2{ 1000.0f,500.0f }, true, true);
			mMoveObject->SetArriveEvent(std::bind([this, audio]()->void
			{
				mbReSpawn = true;
				mAni->SetActive(false);
				mCol->SetActive(false);
				mMoveObject->SetActive(false);
				mDeSpawnStartTime = mTime;
				audio->Play(L"boss_p2_pepper_death3", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_Disappear_03.wav", false);
				audio->Play(L"boss_p2_pepper_deathimpact3", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_LaunchImpact_03.wav", false);
				audio->Play(L"boss_p2_pepper_saltdamage3", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Vocal_Pain_03.wav", false);
			}));
			mMoveObject->SetActive(true);
		}
		else if (pos.x > center.x && pos.y > center.y)//right down
		{
			mSpawners[3].mbSpawn = false;
			mAni->Play(L"sb_p2_pepperDeathRightUp", false);
			
			mMoveObject->CreateInfo(Vector2{ 800.0f,400.0f }, Vector2{ -1.0f,-1.0f }, Vector2{ 1000.0f,500.0f }, true, true);
			mMoveObject->SetArriveEvent(std::bind([this, audio]()->void
			{
				mbReSpawn = true;
				mAni->SetActive(false);
				mCol->SetActive(false);
				mMoveObject->SetActive(false);
				mDeSpawnStartTime = mTime;
				audio->Play(L"boss_p2_pepper_death4", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_Disappear_04.wav", false);
				audio->Play(L"boss_p2_pepper_deathimpact1", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_LaunchImpact_01.wav", false);
				audio->Play(L"boss_p2_pepper_saltdamage4", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Vocal_Pain_04.wav", false);
			}));
			mMoveObject->SetActive(true);
		}
	}

	void Pepper::Attack()
	{
		Audio* audio = GetOwner()->GetComponent<Audio>();
		Vector2 center = application.GetWindowSize();
		center.x /= 2.0f;

		Vector2 pos = mTransform->GetPos();
		if (pos.x < center.x)
		{
			mAni->Play(L"sb_p2_pepperattackaniLeft", false);
			audio->Play(L"boss_p2_pepper_sneeze3", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_SneezeAttack_03.wav", false);
		}
		else
		{
			mAni->Play(L"sb_p2_pepperattackaniRight", false);
			audio->Play(L"boss_p2_pepper_sneeze1", L"..\\Resources\\AudioSource\\AudioClip\\sfx_DLC_Saltbaker_P2_Saltshaker_SneezeAttack_01.wav", false);
		}
		std::shared_ptr<GameObject> obj = core::ObjectPool<PepperBullet>::Spawn();
		PepperBullet* pb = obj->GetComponent<PepperBullet>();
		Vector2 pos2 = mTransform->GetPos();
		pb->SetPos(Vector2{ pos2.x,pos2.y-100.0f});
		pb->Shoot();
		
		SceneManager::GetActiveScene()->AddGameObject(obj, ELayerType::Bullet);
	}

	void Pepper::Intro()
	{
		mAni->Play(L"sb_p2_pepperintro", false);
		SetColCenter();
	}

	void Pepper::Idle()
	{
		mAni->Play(L"sb_p2_pepperIdle", true);
		SetColCenter();
	}

	void Pepper::Init()
	{
		mHP = 4;
		mbReSpawn = false;
		mbDeath = false;
		mbAttackActive = false;
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

	bool Pepper::IsSpawn()
	{
		for (auto& spawn : mSpawners)
		{
			if (spawn.mbSpawn == false)
				return true;
		}
		return false;
	}

	

	void Pepper::TakeDamage(Collider* other)
	{
		Monster::TakeDamage(other);
		if (mHP <= 0)
		{
			if (mbDeath == true)
				return;
			Death(other);
			mbDeath = true;
		}
	}



}
