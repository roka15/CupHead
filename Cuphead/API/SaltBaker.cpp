#include "SaltBaker.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "ObjectPool.h"
#include "Application.h"
extern yeram_client::Application application;

namespace yeram_client
{
	SaltBaker::SaltBaker():Boss()
	{
	}

	SaltBaker::~SaltBaker()
	{
	}

	void SaltBaker::Initialize()
	{
		Boss::Initialize();
		mMoveObject->CreateInfo(Vector2{ 200.0f,20.0f }, Vector2{ -1.0f,-1.0f });
		mMoveObject->SetActive(false);
	
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\idle", Vector2::Zero, 0.1f);

		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\1", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\2", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\3", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\4", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\5", Vector2::Zero, 0.1f);
		mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\6", Vector2::Zero, 0.1f);

		Animator* ani = mAni;
		MoveObject* mv = mMoveObject;
		mAni->GetEndEvent(L"saltbaker_phase_1intro") = std::bind([ani]()->void
		{
			ani->Play(L"saltbaker_phase_1intro2", false);
		});

		mAni->GetEndEvent(L"saltbaker_phase_1intro2") = std::bind([ani, mv]()->void
		{
			mv->SetActive(true);
			std::shared_ptr<GameObject> obj = ani->GetOwner()->FindChild(L"sb_arm");
			obj->SetActive(true);
			ani->Play(L"saltbaker_phase_1intro3", false);
		});
		mAni->GetEndEvent(L"saltbaker_phase_1intro3") = std::bind([ani, mv]()->void
		{
			mv->SetActive(true);
			std::shared_ptr<GameObject> obj = ani->GetOwner()->FindChild(L"sb_arm");
			obj->SetActive(false);
			ani->Play(L"saltbaker_phase_1intro4", false);
		});
		mAni->GetEndEvent(L"saltbaker_phase_1intro4") = std::bind([ani, mv]()->void
		{
			mv->SetActive(false);
			ani->Play(L"saltbaker_phase_1idle", false);
		});

		std::shared_ptr<GameObject> arm = core::ObjectPool<Animator>::Spawn();
		{
			arm->SetName(L"sb_arm");
			Transform* tf = arm->GetComponent<Transform>();
			tf->SetOffset(Vector2{ 300.0f,0.0f });
			Animator* ani = arm->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\intro_arm", Vector2::Zero, 0.1f);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack1", Vector2::Zero, 0.1f);
			ani->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_1\\attack_type1\\dough_attack2", Vector2::Zero, 0.1f);

			ani->Play(L"saltbaker_phase_1intro_arm", false);
			arm->SetActive(false);
		}
		GameObject* owner = GetOwner();
		owner->AddChild(arm);

		ani->Play(L"saltbaker_phase_1intro", false);
		Vector2 pos = application.GetWindowSize();
	
		mTransform->SetPos(Vector2{ pos.x / 2.0f,570.0f });
	}

	void SaltBaker::Update()
	{
	}

	void SaltBaker::Render(HDC hdc)
	{
	}

	void SaltBaker::Release()
	{
	}

	void SaltBaker::OnCollisionEnter(Collider* other)
	{
	}

	void SaltBaker::OnCollisionStay(Collider* other)
	{
	}

	void SaltBaker::OnCollisionExit(Collider* other)
	{
	}
}

