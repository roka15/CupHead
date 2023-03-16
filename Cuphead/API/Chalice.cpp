#include "Chalice.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"
namespace yeram_client
{
	Chalice::Chalice()
	{
	}

	Chalice::~Chalice()
	{
	}

	void Chalice::Initialize()
	{
		mState = ECharacterState::Idle;
		mDirType = EDirType::RIGHT;
		Animator* ani = mOwner->GetComponent<Animator>();
		ani->Play(L"IdleRight", true);
	}

	void Chalice::Update()
	{
		switch (mSceneType)
		{
		case ESceneType::MainMenu:
			break;
			//case ESceneType::PlayMap:
		case ESceneType::BossMedusa:
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

	void Chalice::Render(HDC hdc)
	{
	}

	void Chalice::Release()
	{
	}

	void Chalice::move()
	{
		
		Animator* ani = mOwner->GetComponent<Animator>();
		if (mbJump == 0)
		{
			if (core::Input::GetKeyUp(core::EKeyCode::A)
				|| core::Input::GetKeyUp(core::EKeyCode::D)
				|| core::Input::GetKeyUp(core::EKeyCode::W)
				|| core::Input::GetKeyUp(core::EKeyCode::S)
				||core::Input::GetKeyUp(core::EKeyCode::SPACE))
			{
				mState = ECharacterState::Idle;
				
				switch (mDirType)
				{
				case EDirType::LEFT:
					ani->Play(L"IdleLeft", true);
					break;
				case EDirType::RIGHT:
					ani->Play(L"IdleRight", true);
					break;
				}
			}
		}
		

		//rigid 이동
		//trans 이동

		jump_check(mState);

		PositionUpdate();
	}

	void Chalice::idle()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;

		bool flag=jump_check(mState);

		if (mbJump >= 1)
			return;
		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S)
			)
		{
			if (core::Input::GetKeyDown(core::EKeyCode::A))
			{
				ani_name = L"RegularLeft";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::D))
			{
				ani_name = L"RegularRight";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::W))
			{
				ani_name = L"MapFowardUp";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::S))
			{
				ani_name = L"MapFowardDown";
			}


			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}

			mState = ECharacterState::Move;
		}
	}

	void Chalice::shoot()
	{
	}

	void Chalice::death()
	{
	}

	bool Chalice::jump_check(ECharacterState _befor_state)
	{
		mState = _befor_state;
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		if (core::Input::GetKeyDown(core::EKeyCode::SPACE))
		{
			if (core::Input::GetKeyDoubleDown(core::EKeyCode::SPACE, 2.0f))
			{
				mbJump++;
				if (mbJump > 2)
				{
					mbJump = 2;
					return false;
				}
				if (mDirType == EDirType::LEFT)
					ani_name = L"Double JumpLeft";
				else
					ani_name = L"Double JumpRight";
			}
			else if (core::Input::GetKeyDown(core::EKeyCode::SPACE))
			{
				mbJump++;

				if (mDirType == EDirType::LEFT)
					ani_name = L"JumpLeft";
				else
					ani_name = L"JumpRight";
			}
			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, false);
				mState = ECharacterState::Move;
				return true;
			}
		}
		return false;
	}

	void Chalice::PositionUpdate()
	{
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();

		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		Vector2 offset;
		if (core::Input::GetKey(core::EKeyCode::A))
		{
			//rig->AddForce(Vector2(-200.0f, 0.0f));
			offset.x -= 200.0f * Time::DeltaTime();
			mDirType = EDirType::LEFT;
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			//rig->AddForce(Vector2(+200.0f, 0.0f));
			offset.x += 200.0f * Time::DeltaTime();
			mDirType = EDirType::RIGHT;
		}
		if (core::Input::GetKey(core::EKeyCode::W))
		{
			//rig->AddForce(Vector2(0.0f, -200.0f));
			offset.y -= 200.0f * Time::DeltaTime();
			mDirType = EDirType::UP;
		}
		if (core::Input::GetKey(core::EKeyCode::S))
		{
			//rig->AddForce(Vector2(0.0f, +200.0f));
			offset.y += 200.0f * Time::DeltaTime();
			mDirType = EDirType::DOWN;
		}
		transform->SetPos(pos + offset);
	}

	void Chalice::Create(ESceneType _type)
	{
		mSceneType = _type;

		Transform* tf = mOwner->GetComponent<Transform>();

		mState = ECharacterState::Idle;


		Animator* ani = mOwner->GetComponent<Animator>();
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Idle\\Right", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Idle\\Left", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Regular\\Right", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Regular\\Left", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Regular\\Turn\\Right", Vector2::Zero, 0.1f, true);

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Right", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Left", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Double Jump\\Right", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Double Jump\\Left", Vector2::Zero, 0.1f, true);

		ani->GetCompleteEvent(L"JumpRight") = std::bind([this]()->void {this->SetEndJumpInfo(); });
		ani->GetCompleteEvent(L"JumpLeft") = std::bind([this]()->void {this->SetEndJumpInfo(); });
		ani->GetCompleteEvent(L"Double JumpRight") = std::bind([this]()->void {this->SetEndJumpInfo(); });
		ani->GetCompleteEvent(L"Double JumpLeft") = std::bind([this]()->void {this->SetEndJumpInfo(); });
	}

	void Chalice::idleCompleteEvent()
	{
	}

	void Chalice::moveStartEvent()
	{
	}

	void Chalice::moveCompleteEvent()
	{
	}

}
