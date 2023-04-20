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
		mMoveOffset = offset;
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

	void Character::fix(const PushInfo& _push_info)
	{
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

	bool Character::PriorityInput(core::EKeyCode _code1, core::EKeyCode _code2, core::EKeyCode& _result)
	{
		if ((core::Input::GetKeyDown(_code1) || core::Input::GetKey(_code1)) &&(core::Input::GetKeyDown(_code2)|| core::Input::GetKey(_code2)))
		{
			_result = core::Input::GetFirstPriorityKey(_code1, _code2);
			return true;
		}
		else if (core::Input::GetKey(_code1) || core::Input::GetKeyDown(_code1))
		{
			_result = _code1;
			return true;
		}
		else if (core::Input::GetKey(_code2) || core::Input::GetKeyDown(_code2))
		{
			_result = _code2;
			return true;
		}

		return false;
	}

	EDirType Character::GetDirType(const core::EKeyCode& _code)
	{
		switch (_code)
		{
		case core::EKeyCode::Left:
			return EDirType::LEFT;
		case core::EKeyCode::Right:
			return EDirType::RIGHT;
		case core::EKeyCode::Down:
			return EDirType::DOWN;
		case core::EKeyCode::Up:
			return EDirType::UP;
		}
	}

	const Vector2& Character::GetShooterSpawnPos(int _count, EDirType ...)
	{
		std::queue<EDirType> queue;
		assert(_count >= 0);
		va_list list;
		va_list copy;

		va_start(list, _count);
		va_copy(copy, list);

		for (int i = 0; i != _count; ++i)
		{
			queue.push(va_arg(copy, EDirType));
		}

		va_end(list);
		va_end(copy);

		UINT result_key = 0;
		while (queue.empty() == false)
		{
			EDirType type = queue.front();
			queue.pop();

			result_key |= (UINT)type;
		}

		return mShooterSpawnPos[result_key];
	}

	void Character::SetNextAniInfo()
	{
		//mJump = 0;
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		core::EKeyCode horizontal_key;
		core::EKeyCode vertical_key;
		bool horizontal_flag = PriorityInput(core::EKeyCode::Left, core::EKeyCode::Right, horizontal_key);
		bool vertical_flag = PriorityInput(core::EKeyCode::Up, core::EKeyCode::Down, vertical_key);
		EDirType h_key = GetDirType(horizontal_key);
		EDirType v_key = GetDirType(vertical_key);
		if (mAni->GetActive() == false)
		{
			mHead->GetComponent<Animator>()->ActiveReset();
			mReg->GetComponent<Animator>()->ActiveReset();
			mHead->SetActive(false);
			mReg->SetActive(false);

			mAni->SetActive(true);
		}
		//duck 일경우
		if (core::Input::GetKey(core::EKeyCode::Down) && horizontal_flag == true)
		{
			mDirType = h_key;
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
		PushInfo info;
		//duck 아닐 경우
	 	switch (mState)
		{
		case ECharacterState::Dash:
		{
			if (core::Input::GetKey(core::EKeyCode::Z))
			{
				mState = ECharacterState::Shoot;
				PushInfo info;
				mShooter->SetActive(true);
				shoot(info);
				return;
			}
		}
		case ECharacterState::Move:
			if (horizontal_flag == true)
			{
				mDirType = h_key;
				ani_name = ani->GetDirAniKey(L"Regular", h_key);
				ani->Play(ani_name, true);
				mState = ECharacterState::Move;
				return;
			}
		case ECharacterState::Idle:
		{
			if (horizontal_flag == true)
				mDirType = h_key;
			else
			{
				mState = ECharacterState::Idle;
			}
			ani_name = ani->GetDirAniKey(L"Idle", mDirType);
			ani->Play(ani_name, true);
		
			break;
		}
		case ECharacterState::Duck:
			//duck 일경우

			break;
		case ECharacterState::Fix:
			if (core::Input::GetKey(core::EKeyCode::C))
			{
				if (horizontal_flag == true)
					mDirType = h_key;
				ani_name = ani->GetDirAniKey(L"Idle", mDirType);
				ani->Play(ani_name, true);
			}
			else if (core::Input::GetKey(core::EKeyCode::C) == false &&
				core::Input::GetKeyDown(core::EKeyCode::C) == false)
			{
				info.keycode = core::EKeyCode::C;
				info.state = core::EKeyState::Up;
				fix(info);
			}
			break;
		case ECharacterState::Shoot:
			
			if (core::Input::GetKey(core::EKeyCode::Z) == false &&
				core::Input::GetKeyDown(core::EKeyCode::Z) == false)
			{
				info.keycode = core::EKeyCode::Z;
				info.state = core::EKeyState::Up;
			}
			shoot(info);
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
		Vector2 vel = rig->GetVelocity();
		vel.y = 0;
		rig->SetVelocity(vel);
		mDashVelocity = 1.0f; 
		mDashTime = 0.0f;
	}

	void Character::StopTransUpdate(bool _flag, EDirType _type)
	{
		mbStopPositionUpdate = _flag;
		mStopDir = _type;
	}

}
