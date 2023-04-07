#include "Cuphead.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Resources.h"
#include "Rigidbody.h"
namespace yeram_client
{
	Cuphead::Cuphead()
	{

	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		mState = ECharacterState::Idle;
		Animator* ani = mOwner->GetComponent<Animator>();
		ani->Play(L"MapIdle", true);
		Collider* col = mOwner->GetComponent<Collider>();
		col->SetCenter(Vector2(-30.0f, -100.0f));
		col->SetSize(Vector2(60.0f, 90.0f));
	}

	void Cuphead::Update()
	{
		PushInfo push;
			switch (mState)
			{
			case ECharacterState::Idle:
				idle(push);
				break;
			case ECharacterState::Move:
				move(push);
				break;
			case ECharacterState::Death:
				death(push);
				break;
			case ECharacterState::Shoot:
				shoot(push);
				break;
			}
	}

	void Cuphead::Render(HDC hdc)
	{
	}

	void Cuphead::Release()
	{
	}

	

	void Cuphead::Create()
	{
		Transform* tf = mOwner->GetComponent<Transform>();
	
		mState = ECharacterState::Idle;


		Animator* ani = mOwner->GetComponent<Animator>();

		Image* mImage = nullptr;
		Image* mLImage = nullptr;

		//mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Idle", Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Aim\\Straight", Vector2::Zero, 0.1f);

		//mAnimator->GetStartEvent(L"MapIdle")=std::bind(&Player::idleCompleteEvent,this);
		
		//map 
		mImage = Resources::Load<Image>(L"MapMoveBase", L"..\\Resources\\Cuphead_Stage_base.bmp");//받아오기 시트
		mLImage = Resources::Load<Image>(L"MapMoveLeft", L"..\\Resources\\Cuphead_Stage_left.bmp");

		ani->CreateAnimation(L"MapFowardUp", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1f);
		ani->CreateAnimation(L"MapFowardRight", mImage, Vector2(0.0f, 113.0f * 3), 16, 8, 14, Vector2::Zero, 0.1f);
		ani->CreateAnimation(L"MapFowardDown", mImage, Vector2(0.0f, 113.0f * 6), 16, 8, 13, Vector2::Zero, 0.1f);
		ani->CreateAnimation(L"MapIdle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 16, Vector2::Zero, 0.1f);

		ani->GetStartEvent(L"MapFowardRight") = std::bind(&Cuphead::moveStartEvent, this);
		ani->GetCompleteEvent(L"MapFowardRight") = std::bind(&Cuphead::moveCompleteEvent, this);

		ani->GetCompleteEvent(L"MapFowardUp") = std::bind(&Cuphead::moveCompleteEvent, this);

		ani->CreateAnimation(L"MapFowardLeft", mLImage, Vector2(0.0f, 113.0f * 3), 16, 8, 14, Vector2::Zero, 0.1f);
		ani->GetCompleteEvent(L"MapFowardLeft") = std::bind(&Cuphead::moveCompleteEvent, this);
		//stage

	}

	void Cuphead::idleCompleteEvent()
	{

	}

	void Cuphead::moveStartEvent()
	{

	}

	void Cuphead::moveCompleteEvent()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		Animation* obj = ani->FindAnimation(ani->GetCurAniName());
		obj->SetSpriteIndex(3);
	}

	void Cuphead::move(const PushInfo& _push_info)
	{
		Character::move(_push_info);
	}

	void Cuphead::idle(const PushInfo& _push_info)
	{
		Character::idle(_push_info);
	}

	void Cuphead::shoot(const PushInfo& _push_info)
	{
		Character::shoot(_push_info);
	}

	void Cuphead::death(const PushInfo& _push_info)
	{
		Character::death(_push_info);
	}
	void Cuphead::duck(const PushInfo& _push_info)
	{
	}
	
	void Cuphead::air_move()
	{
	}
	void Cuphead::air_idle()
	{
	}
	void Cuphead::air_shoot()
	{
	}
	void Cuphead::air_death()
	{
	}
}