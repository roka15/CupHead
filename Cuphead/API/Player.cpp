#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "Resources.h"
#include "Image.h"
#include "Transform.h"
#include "Animator.h"
namespace yeram_client
{
	Player::Player() :GameObject()
		,mPlayType(EPlayerType::Cuphead)
		,mState(ECupheadState::Idle)
	{
		
	}
	
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(400.0f, 400.0f)); 
		mState = ECupheadState::Idle;
		
		
		mAnimator = GetComponent<Animator>();
		if (mAnimator == nullptr)
		{
			mAnimator = AddComponent<Animator>();
		}
		Image* mImage = nullptr;
		switch (mPlayType)
		{
		case EPlayerType::Cuphead:
			mImage = Resources::Load<Image>(L"MapFowardRun", L"..\\Resources\\Cuphead_Stage.bmp");//받아오기 시트
			break;
		case EPlayerType::MugMan:
			break;
		case EPlayerType::MsChalice:
			break;
		}
	
		mAnimator->CreateAnimation(L"MapFowardRun", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"MapFowardRight", mImage, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MapIdle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2::Zero, 0.1);
		//mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Idle", Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Aim\\Straight", Vector2::Zero, 0.1f);
		
		//mAnimator->GetStartEvent(L"MapIdle")=std::bind(&Player::idleCompleteEvent,this);
		mAnimator->Play(L"MapIdle", true);
		
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ECupheadState::Death:
			death();
			break;
		case ECupheadState::Idle:
			idle();
			break;
		case ECupheadState::Move:
			move();
			break;
		case ECupheadState::Shoot:
			shoot();
			break;
		}
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Player::Release()
	{
		GameObject::Release();
	}
	void Player::move()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		std::wstring ani_name;
		if (core::Input::GetKeyUp(core::EKeyCode::A)
			|| core::Input::GetKeyUp(core::EKeyCode::D)
			|| core::Input::GetKeyUp(core::EKeyCode::W)
			|| core::Input::GetKeyUp(core::EKeyCode::S))
		{
			mState = ECupheadState::Idle;
			ani_name = L"MapIdle";
		}
		if (core::Input::GetKey(core::EKeyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
			ani_name = L"MapFowardRight";
		}
		if (core::Input::GetKey(core::EKeyCode::W))
		{
			pos.y -= 100.0f * Time::DeltaTime();
			ani_name = L"MapFowardRun";
		}
		if (core::Input::GetKey(core::EKeyCode::S))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		transform->SetPos(pos);
		if (ani_name.size() > 0)
		{
			mAnimator->Play(ani_name.c_str(), true);
		}
	}
	void Player::shoot()
	{
	}
	void Player::death()
	{
	}
	void Player::idle()
	{
		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S))
		{
			mState = ECupheadState::Move;
			//mAnimator->Play(L"Move", true);
		}
		if (core::Input::GetKeyDown(core::EKeyCode::K))
		{
			mState = ECupheadState::Shoot;
			mAnimator->Play(L"AimStraight", true);
		}
	}
	void Player::idleCompleteEvent()
	{
		
	}
}