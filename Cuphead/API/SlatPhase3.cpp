#include "SlatPhase3.h"
#include "GameObject.h"
#include "MoveObject.h"
#include "Ground.h"
#include "Application.h"
extern yeram_client::Application application;
yeram_client::SlatPhase3::SlatPhase3():Monster()
{
	SetName(L"SaltPhase3");
}

yeram_client::SlatPhase3::~SlatPhase3()
{
}

void yeram_client::SlatPhase3::Initialize()
{
	Monster::Initialize();
	mDir.x = 1.0f;
	mRigid = GetOwner()->AddComponent<Rigidbody>();
	mRigid->Use_Gravity(true);
	mRigid->SetMass(1.0f);
	mRigid->SetGround(false);
	//mRigid->SetGravity(100.0);
	mAni->CreateAnimations(L"..\\Resources\\scene\\dlc\\saltbaker_boss_scene\\saltbaker_phase_3\\sb_p3_boss\\idle", Vector2::Zero, 0.05f);
	mAni->Play(L"sb_p3_bossidle", true);
	mTransform->SetPos(Vector2{ 800.0f,100.0f });
	mMoveObject->CreateInfo(Vector2{ 400.0f,0.0f }, Vector2{ mDir.x,0.0f }, false, false);
	mMoveObject->SetEndPos();
	mMoveObject->SetYFlag(false);
	
}

void yeram_client::SlatPhase3::Update()
{
}

void yeram_client::SlatPhase3::Render(HDC hdc)
{
}

void yeram_client::SlatPhase3::Release()
{
}

void yeram_client::SlatPhase3::OnCollisionEnter(Collider* other)
{
	Monster::OnCollisionEnter(other);
	Ground* ground = other->GetOwner()->GetComponent<Ground>();
	if (ground != nullptr)
	{
		Vector2 velocity = mRigid->GetVelocity();

		velocity.y = -2000.0f;

		mRigid->SetVelocity(velocity);
		mRigid->SetGround(false);
	}
}

void yeram_client::SlatPhase3::OnCollisionStay(Collider* other)
{
	Ground* ground = other->GetOwner()->GetComponent<Ground>();
	if (ground != nullptr)
	{
		Vector2 velocity = mRigid->GetVelocity();

		velocity.y = -2000.0f;

		mRigid->SetVelocity(velocity);
		mRigid->SetGround(false);
	}
}

void yeram_client::SlatPhase3::OnCollisionExit(Collider* other)
{
}

void yeram_client::SlatPhase3::Death(Collider* _other)
{
}

void yeram_client::SlatPhase3::Attack()
{
}

void yeram_client::SlatPhase3::Idle()
{
}

void yeram_client::SlatPhase3::Intro()
{
}

void yeram_client::SlatPhase3::TakeDamage(Collider* other)
{
	Monster::TakeDamage(other);
}

void yeram_client::SlatPhase3::ChangeDir()
{
	mDir.x *= -1.0f;
	Vector2 endpos;
	if (mDir.x < 0.0f)
	{
		endpos.x = 0.0f;
	}
	else
	{
		endpos.x = application.GetWindowSize().x;
	}
	mMoveObject->CreateInfo(Vector2{ 400.0f,0.0f }, Vector2{ mDir.x,0.0f },endpos, false, false);
	mMoveObject->SetEndPos();
}

void yeram_client::SlatPhase3::SetCompleteEvent()
{
	 mMoveObject->SetArriveEvent(std::bind([this]()->void {ChangeDir(); })); 
}
