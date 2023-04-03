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
	void Character::move()
	{
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();

		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		Vector2 offset;
		Animator* ani = mOwner->GetComponent<Animator>();


		if (core::Input::GetKeyUp(core::EKeyCode::A)
			|| core::Input::GetKeyUp(core::EKeyCode::D)
			|| core::Input::GetKeyUp(core::EKeyCode::W)
			|| core::Input::GetKeyUp(core::EKeyCode::S))
		{
			mState = ECharacterState::Idle;
			ani->Play(L"MapIdle", true);
		}

		//rigid 이동
		//trans 이동
		if (core::Input::GetKey(core::EKeyCode::A))
		{
			//rig->AddForce(Vector2(-200.0f, 0.0f));
			offset.x -= 200.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			//rig->AddForce(Vector2(+200.0f, 0.0f));
			offset.x += 200.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::W))
		{
			//rig->AddForce(Vector2(0.0f, -200.0f));
			offset.y -= 200.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::S))
		{
			//rig->AddForce(Vector2(0.0f, +200.0f));
			offset.y += 200.0f * Time::DeltaTime();
		}

		transform->SetPos(pos + offset);
		SceneManager::ChagePosGameObjects(offset);
	}
	void Character::idle()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;

		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S))
		{


			if (core::Input::GetKeyDown(core::EKeyCode::A))
			{
				ani_name = L"MapFowardLeft";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::D))
			{
				ani_name = L"MapFowardRight";
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

		//scene이 게임중일때
		/*
		if (core::Input::GetKeyDown(core::EKeyCode::K))
		{
			mState = ECharacterState::Shoot;
			ani->Play(L"AimStraight", true);
		}
		*/
	}
	void Character::shoot()
	{

	}
	void Character::duck()
	{
	}
	void Character::death()
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

		switch (mState)
		{
		case ECharacterState::Move:
			if (core::Input::GetKey(core::EKeyCode::A))
			{
				ani->Play(L"RegularLeft", true);
				return;
			}
			else if (core::Input::GetKey(core::EKeyCode::D))
			{
				ani->Play(L"RegularRight", true);
				return;
			}
			mState = ECharacterState::Idle;
		case ECharacterState::Idle:
			std::wstring anikey = ani->GetDirAniKey(L"Idle", mDirType);
			ani->Play(anikey, true);
			break;
		}



	}

	void Character::SetAirMode(bool _flag)
	{
		mbAir = _flag;
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();
		rig->Use_Gravity(_flag);
	}

}
