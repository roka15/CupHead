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
	{

	}
	Player::Player(ERenderType _type) : GameObject(_type)
	{

	}
	Player::~Player()
	{
	}
	void Player::Initalize()
	{
		mState = ECupheadState::Idle;
		mRenderType = ERenderType::TransParentBlt;
		GameObject::Initalize();
		Image* mImage = Resources::Load<Image>(L"MapFowardRun", L"..\\Resources\\cuphead_move.bmp");//받아오기 시트
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"MapFowardRun", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1f);
		//animator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8,15, Vector2::Zero, 0.1f);
		animator->Play(L"MapFowardRun", true);

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

		/*Transform* transform = GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		if (core::Input::GetKeyState(core::EKeyCode::A) == core::EKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::D) == core::EKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::W) == core::EKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::S) == core::EKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}*/
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

		if (core::Input::GetKeyUp(core::EKeyCode::A)
			|| core::Input::GetKeyUp(core::EKeyCode::D)
			|| core::Input::GetKeyUp(core::EKeyCode::W)
			|| core::Input::GetKeyUp(core::EKeyCode::S))
		{
			mState = ECupheadState::Idle;
			mAnimator->Play(L"Idle", true);
		}
		if (core::Input::GetKey(core::EKeyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::W))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::S))
		{
			pos.y += 100.0f * Time::DeltaTime();
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
			mAnimator->Play(L"Move", true);
		}
	}
}