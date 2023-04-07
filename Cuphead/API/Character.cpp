#include "Character.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Resources.h"
#include "Input.h"
#include "Time.h"
#include "Camera.h"
#include "Rigidbody.h"

namespace yeram_client
{
	void Character::move(const PushInfo& _push_info)
	{
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();

		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		Vector2 offset;
		Animator* ani = mOwner->GetComponent<Animator>();


		if (core::Input::GetKeyUp(core::EKeyCode::Left)
			|| core::Input::GetKeyUp(core::EKeyCode::Right)
			|| core::Input::GetKeyUp(core::EKeyCode::Up)
			|| core::Input::GetKeyUp(core::EKeyCode::Down))
		{
			mState = ECharacterState::Idle;
			ani->Play(L"MapIdle", true);
		}

		//rigid 이동
		//trans 이동
		if (core::Input::GetKey(core::EKeyCode::Left))
		{
			//rig->AddForce(Vector2(-200.0f, 0.0f));
			offset.x -= 200.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::Right))
		{
			//rig->AddForce(Vector2(+200.0f, 0.0f));
			offset.x += 200.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::Up))
		{
			//rig->AddForce(Vector2(0.0f, -200.0f));
			offset.y -= 200.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::Down))
		{
			//rig->AddForce(Vector2(0.0f, +200.0f));
			offset.y += 200.0f * Time::DeltaTime();
		}

		transform->SetPos(pos + offset);
		SceneManager::ChagePosGameObjects(offset);
	}
	void Character::idle(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;

		if (core::Input::GetKeyDown(core::EKeyCode::Left)
			|| core::Input::GetKeyDown(core::EKeyCode::Right)
			|| core::Input::GetKeyDown(core::EKeyCode::Up)
			|| core::Input::GetKeyDown(core::EKeyCode::Down))
		{


			if (core::Input::GetKeyDown(core::EKeyCode::Left))
			{
				ani_name = L"MapFowardLeft";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::Right))
			{
				ani_name = L"MapFowardRight";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::Up))
			{
				ani_name = L"MapFowardUp";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::Down))
			{
				ani_name = L"MapFowardDown";
			}

			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}
			mState = ECharacterState::Move;
		}

		//scene이 게임중일때
		/*
		if (core::Input::GetKeyDown(core::EKeyCode::K))
		{
			mState = ECharacterState::Shoot;
			ani->Play(L"AimStraight", true);
		}
		*/
	}
	void Character::shoot(const PushInfo& _push_info)
	{

	}
	void Character::duck(const PushInfo& _push_info)
	{
	}
	void Character::death(const PushInfo& _push_info)
	{
	}

	bool Character::jump_check(ECharacterState _befor_state)
	{
		return false;
	}

	void Character::air_move()
	{
	}

	void Character::air_idle()
	{
	}

	void Character::air_shoot()
	{
	}

	void Character::air_death()
	{
	}

	void Character::PositionUpdate()
	{

	}

	void Character::DashPositionUpdate(EStateType _type)
	{
	}

	void Character::SetNextAniInfo()
	{
		//mJump = 0;
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		//duck 일경우
		if (core::Input::GetKey(core::EKeyCode::Down) && core::Input::GetKey(core::EKeyCode::Left)
			&& core::Input::GetKey(core::EKeyCode::Right))
		{
			core::EKeyCode code = core::Input::GetFirstPriorityKey(core::EKeyCode::Right, core::EKeyCode::Left);

			switch (code)
			{
			case core::EKeyCode::Left:
				mDirType = EDirType::LEFT;
				break;
			case core::EKeyCode::Right:
				mDirType = EDirType::RIGHT;
				break;
			}
			ani_name = ani->GetDirAniKey(L"Duck", mDirType);
			ani->Play(ani_name, true);
			mState = ECharacterState::Duck;
			mbSit = true;
			return;
		}
		else if (core::Input::GetKey(core::EKeyCode::Down))
		{
			ani_name = ani->GetDirAniKey(L"Duck", mDirType);
			ani->Play(ani_name, true);
			mState = ECharacterState::Duck;
			mbSit = true;
			return;
		}
		//duck 아닐 경우
		switch (mState)
		{
		case ECharacterState::Dash:
			ResetDash();
		case ECharacterState::Move:
			if (core::Input::GetKey(core::EKeyCode::Left) && core::Input::GetKey(core::EKeyCode::Right))
			{
				core::EKeyCode code = core::Input::GetFirstPriorityKey(core::EKeyCode::Left, core::EKeyCode::Right);
				switch (code)
				{
				case core::EKeyCode::Left:
					ani->Play(L"RegularLeft", true);
					break;
				case core::EKeyCode::Right:
					ani->Play(L"RegularRight", true);
					break;
				}
				mState = ECharacterState::Move;
				return;
			}
			if (core::Input::GetKey(core::EKeyCode::Left))
			{
				ani->Play(L"RegularLeft", true);
				mState = ECharacterState::Move;
				return;
			}
			else if (core::Input::GetKey(core::EKeyCode::Right))
			{
				ani->Play(L"RegularRight", true);
				mState = ECharacterState::Move;
				return;
			}
			mState = ECharacterState::Idle;
		case ECharacterState::Idle:
		{
			std::wstring anikey = ani->GetDirAniKey(L"Idle", mDirType);
			ani->Play(anikey, true);
			break;
		}
		case ECharacterState::Duck:
			//duck 일경우

			break;
		}



	}

	void Character::SetAirMode(bool _flag)
	{
		mbAir = _flag;
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();
		rig->Use_Gravity(_flag);
	}


	void Character::Parrying()
	{
		if (mJump == 0)
			mJump++;
		if (mJump == 2)
			mJump--;
		mbParry = true;
		//mbDash = false;
		ResetDash();
	}

	void Character::ResetDash()
	{
		mbDash = false;	
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();
		rig->SetActive(true);
		/*Vector2 vel = rig->GetVelocity();
		vel.y = 0;
		rig->SetVelocity(vel);*/
		mDashVelocity = 1.0f; 
		mDashTime = 0.0f;
	}

	void Character::StopTransUpdate(bool _flag, EDirType _type)
	{
		mbStopPositionUpdate = _flag;
		mStopDir = _type;
	}

}
