#include "Cuphead.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Resources.h"
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
	}

	void Cuphead::Update()
	{
		
		switch (mSceneType)
		{
		case ESceneType::MainMenu:
			break;
		case ESceneType::PlayMap:
		case ESceneType::PlayStage:
		{
			switch (mState)
			{
			case ECharacterState::Idle:
				idle();
				break;
			case ECharacterState::Move:
				move();
				break;
			case ECharacterState::Death:
				death();
				break;
			case ECharacterState::Shoot:
				shoot();
				break;
			}
		}
		break;
		}

	}

	void Cuphead::Render(HDC hdc)
	{
	}

	void Cuphead::Release()
	{
	}

	

	void Cuphead::Create(ESceneType _type)
	{
		mSceneType = _type;

		Transform* tf = mOwner->GetComponent<Transform>();
	
		mState = ECharacterState::Idle;


		Animator* ani = mOwner->GetComponent<Animator>();

		Image* mImage = nullptr;
		Image* mLImage = nullptr;

		//mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Idle", Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Aim\\Straight", Vector2::Zero, 0.1f);

		//mAnimator->GetStartEvent(L"MapIdle")=std::bind(&Player::idleCompleteEvent,this);
		
		switch (_type)
		{
		case ESceneType::PlayMap://map일때
			mImage = Resources::Load<Image>(L"MapMoveBase", L"..\\Resources\\Cuphead_Stage_base.bmp");//받아오기 시트
			mLImage = Resources::Load<Image>(L"MapMoveLeft", L"..\\Resources\\Cuphead_Stage_left.bmp");

			ani->CreateAnimation(L"MapFowardUp", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1f);
			ani->CreateAnimation(L"MapFowardRight", mImage, Vector2(0.0f, 113.0f*3), 16, 8, 14, Vector2::Zero, 0.1f);
			ani->CreateAnimation(L"MapFowardDown", mImage, Vector2(0.0f, 113.0f * 6), 16, 8, 13, Vector2::Zero, 0.1f);
			ani->CreateAnimation(L"MapIdle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 16, Vector2::Zero, 0.1f);
	
			ani->GetStartEvent(L"MapFowardRight") = std::bind(&Cuphead::moveStartEvent, this);
			ani->GetCompleteEvent(L"MapFowardRight") = std::bind(&Cuphead::moveCompleteEvent, this);

			ani->GetCompleteEvent(L"MapFowardUp") = std::bind(&Cuphead::moveCompleteEvent, this);

			ani->CreateAnimation(L"MapFowardLeft", mLImage, Vector2(0.0f, 113.0f * 3), 16, 8, 14, Vector2::Zero, 0.1f);
			ani->GetCompleteEvent(L"MapFowardLeft") = std::bind(&Cuphead::moveCompleteEvent, this);
			ani->Play(L"MapIdle", true);
			break;
		case ESceneType::PlayStage:
			break;
		//stage 중일때
		}
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

	void Cuphead::move()
	{
		Character::move();
	}

	void Cuphead::idle()
	{
		Character::idle();
	}

	void Cuphead::shoot()
	{
		Character::shoot();
	}

	void Cuphead::death()
	{
		Character::death();
	}
}