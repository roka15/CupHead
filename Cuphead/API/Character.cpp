#include "Character.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Resources.h"
#include "Input.h"
#include "Time.h"
namespace yeram_client
{
	void Character::move()
	{
		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2& pos = transform->GetPos();

		Animator* ani = mOwner->GetComponent<Animator>();
	

		switch (mSceneType)
		{
		//case 맵 일때.
		case ESceneType::PlayMap:
			if (core::Input::GetKeyUp(core::EKeyCode::A)
				|| core::Input::GetKeyUp(core::EKeyCode::D)
				|| core::Input::GetKeyUp(core::EKeyCode::W)
				|| core::Input::GetKeyUp(core::EKeyCode::S))
			{
				mState = ECharacterState::Idle;
				ani->Play(L"MapIdle", true);
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
			transform->SetPos(pos);
			
			break;
		}
	 //case 게임중일때
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
			switch (mSceneType)
			{
				//case 맵 일때.
			case ESceneType::PlayMap:
				if (core::Input::GetKeyDown(core::EKeyCode::A))
				{

				}
				if (core::Input::GetKeyDown(core::EKeyCode::D))
				{
					ani_name = L"MapFowardRight";
				}
				if (core::Input::GetKeyDown(core::EKeyCode::W))
				{
					ani_name = L"MapFowardRun";
				}
				if (core::Input::GetKeyDown(core::EKeyCode::S))
				{

				}
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
	void Character::death()
	{
	}

}
