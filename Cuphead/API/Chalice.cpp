#include "Chalice.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"
#include "ObjectPool.h"
#include "Bullet.h"
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
		Collider* col = mOwner->GetComponent<Collider>();
		Transform* tf = mOwner->GetComponent<Transform>();
		if (mbAir == true)
		{
			ani->Play(L"AirIdleStraight", true);
		}
		else
		{
			ani->Play(L"IdleRight", true);
		}
		const Vector2& pos = tf->GetPos();
		const Vector2& size = ani->GetSpriteSize();
		col->SetCenter(Vector2{ -(size.x / 2),-size.y });
		col->SetSize(size);

	}

	void Chalice::Update()
	{
		if (mbAir == true)
		{
			switch (mState)
			{
			case ECharacterState::Idle:
				air_idle();
				break;
			case ECharacterState::Move:
				air_move();
				break;
			case ECharacterState::Death:
				air_death();
				break;
			case ECharacterState::Shoot:
 				air_shoot();
				break;
			}
		}
		else
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
			case ECharacterState::Duck:
				duck();
				break;
			}
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
		std::wstring ani_name;
		Animator* ani = mOwner->GetComponent<Animator>();

		if (execute_dash(dash_check()))
			return;

		//점프중이지 않을 때
		if (mJump == 0)
		{
			//key up 발생 시 
			if (core::Input::GetKeyUp(core::EKeyCode::A)
				|| core::Input::GetKeyUp(core::EKeyCode::D)
				|| core::Input::GetKeyUp(core::EKeyCode::W)
				|| core::Input::GetKeyUp(core::EKeyCode::SPACE))
			{
				mState = ECharacterState::Idle;

				ani_name = ani->GetDirAniKey(L"Idle", mDirType);

				//key up 발생과 key press 상태가 동시에 일어났을 때 처리. 
				if (core::Input::GetKey(core::EKeyCode::A)
					|| core::Input::GetKey(core::EKeyCode::D)
					|| core::Input::GetKey(core::EKeyCode::W)
					|| core::Input::GetKeyDown(core::EKeyCode::S)
					)
				{
					//앉기 가능 
					if (duck_check() == true)
						return;
					//키가 press or push 일때 처리
					if (core::Input::GetKey(core::EKeyCode::A) || core::Input::GetKeyDown(core::EKeyCode::A))
					{
						mbSit = false;
						ani_name = L"RegularLeft";
					}
					if (core::Input::GetKey(core::EKeyCode::D) || core::Input::GetKeyDown(core::EKeyCode::D))
					{
						mbSit = false;
						ani_name = L"RegularRight";
					}

					mState = ECharacterState::Move;
				}
				if (ani_name.size() > 0)
				{
					ani->Play(ani_name, true);
				}
			}

			//key up과 동시에 발생하지 않고 move 상태일때 keydown 입력이 들어오면 처리
			if (core::Input::GetKeyDown(core::EKeyCode::A)
				|| core::Input::GetKeyDown(core::EKeyCode::D)
				|| core::Input::GetKeyDown(core::EKeyCode::W)
				|| core::Input::GetKeyDown(core::EKeyCode::S)
				)
			{
				//앉기 가능 
				if (duck_check() == true)
					return;
				//키가 push 일때 처리
				if (core::Input::GetKeyDown(core::EKeyCode::A))
				{
					mbSit = false;
					ani_name = L"RegularLeft";
				}
				if (core::Input::GetKeyDown(core::EKeyCode::D))
				{
					mbSit = false;
					ani_name = L"RegularRight";
				}


				if (ani_name.size() > 0)
				{
					ani->Play(ani_name, true);
				}

				mState = ECharacterState::Move;
			}
		}

		jump_check(mState);
		PositionUpdate();
	}

	void Chalice::idle()
	{
		Animator* ani = mOwner->GetComponent<Animator>();

		std::wstring ani_name;

		jump_check(mState);

		if (execute_dash(dash_check()) == true)
			return;

		if (mJump >= 1)
			return;

		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S)
			)
		{
			//앉기 가능.
			if (duck_check() == true)
				return;

			//duck이 아닐때, 오른쪽 or 왼쪽 이동 입력 받을 수 있음.
			if (core::Input::GetKeyDown(core::EKeyCode::A))
			{
				mbSit = false;
				ani_name = L"RegularLeft";
			}
			if (core::Input::GetKeyDown(core::EKeyCode::D))
			{
				mbSit = false;
				ani_name = L"RegularRight";
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

	void Chalice::duck()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		if (core::Input::GetKeyUp(core::EKeyCode::S))
		{
			if (mbSit == true)
			{
				if (core::Input::GetKeyUp(core::EKeyCode::S))
				{
					mbSit = false;
					mState = ECharacterState::Move;
					std::wstring anikey = ani->GetDirAniKey(L"Stand Up", mDirType);

					ani->Play(anikey, false);
				}
			}
		}
		if (core::Input::GetKeyDown(core::EKeyCode::A))
		{
			mDirType = EDirType::LEFT;
			ani->Play(L"DuckIdleLeft", true);
			//ani left duck
		}
		if (core::Input::GetKeyDown(core::EKeyCode::D))
		{
			mDirType = EDirType::RIGHT;
			ani->Play(L"DuckIdleRight", true);
			//ani right duck
		}
	}

	bool Chalice::jump_check(ECharacterState _befor_state)
	{
		//mState = _befor_state;
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		if (core::Input::GetKeyDown(core::EKeyCode::SPACE))
		{
			mJump++;
			if (mJump > 2)
			{
				mJump = 2;
				return false;
			}
			if (core::Input::GetKeyDoubleDown(core::EKeyCode::SPACE, 2.0f)
				&& mJump == 2)
			{
				ani_name = ani->GetDirAniKey(L"Double Jump", mDirType);
			}
			else if (core::Input::GetKeyDown(core::EKeyCode::SPACE))
			{
				ani_name = ani->GetDirAniKey(L"Jump", mDirType);
			}

			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
				mState = ECharacterState::Move;
				Rigidbody* rigid = mOwner->GetComponent<Rigidbody>();
				Vector2 velocity = rigid->GetVelocity();
				velocity.y -= 1050.0f;

				rigid->SetVelocity(velocity);
				rigid->SetGround(false);
				return true;
			}
		}
		return false;
	}

	bool Chalice::duck_check()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		//앉기 가능 
		if (mbSit == false && mJump == 0)
		{
			if (core::Input::GetKeyDown(core::EKeyCode::S))
			{
				mbSit = true;
				std::wstring anikey = ani->GetDirAniKey(L"Duck", mDirType);
				ani->Play(anikey, false);
				mState = ECharacterState::Duck;
				return true;
			}
		}
		return false;
	}

	EStateType Chalice::dash_check()
	{
		if (mbDash == true)
			return EStateType::ING;
		Animator* ani = mOwner->GetComponent<Animator>();
		if (core::Input::GetKeyDown(core::EKeyCode::SHIFT))
		{
			Rigidbody* rigid = mOwner->GetComponent<Rigidbody>();
			std::wstring aniname;
			if (rigid->GetGround() == true)
			{
				aniname = ani->GetDirAniKey(L"GroundDash", mDirType);
			}
			else if (rigid->GetGround() == false)
			{
				aniname = ani->GetDirAniKey(L"JumpDash", mDirType);
			}
			mbDash = true;
			if (aniname.size() > 0)
			{
				ani->Play(aniname, false);
				return EStateType::START;
			}

		}
		return EStateType::NOTHING;
	}

	void Chalice::air_move()
	{
		std::wstring ani_name;
		Animator* ani = mOwner->GetComponent<Animator>();

		AirMove();
		AirShoot();
		//PositionUpdate();
	}

	void Chalice::air_idle()
	{
		std::wstring aniname;
		Animator* ani = mOwner->GetComponent<Animator>();

		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S)
			|| core::Input::GetKey(core::EKeyCode::A)
			|| core::Input::GetKey(core::EKeyCode::D)
			|| core::Input::GetKey(core::EKeyCode::W)
			|| core::Input::GetKey(core::EKeyCode::S)
			)
		{
			mState = ECharacterState::Move;
			if (core::Input::GetKeyDown(core::EKeyCode::W))
			{
				aniname = L"AirTransitionsUp";
			}
			else if (core::Input::GetKeyDown(core::EKeyCode::S))
			{
				aniname = L"AirTransitionsDown";
			}
			if (aniname.size() > 0)
				ani->Play(aniname, false);
		}

		AirShoot();
	}  

	void Chalice::air_shoot()
	{
		AirMove();
		if (core::Input::GetKeyUp(core::EKeyCode::SPACE))
		{
			Animator* ani = mOwner->FindChild(L"Shooter")->GetComponent<Animator>();
			ani->SetActive(false);
		}
		else if (core::Input::GetKey(core::EKeyCode::SPACE)|| core::Input::GetKeyDown(core::EKeyCode::SPACE))
		{
			mState = ECharacterState::Shoot;
		}
		else
		{
			mState = ECharacterState::Idle;
		}
	}

	void Chalice::air_death()
	{
	}

	bool Chalice::execute_dash(EStateType _type)
	{
		switch (_type)
		{
		case EStateType::ING:
			if (core::Input::GetKeyDown(core::EKeyCode::A))
			{
				mDirType = EDirType::LEFT;
			}
			if (core::Input::GetKeyDown(core::EKeyCode::D))
			{
				mDirType = EDirType::RIGHT;
			}
		case EStateType::START:
			DashPositionUpdate(_type);
			return true;
		case EStateType::NOTHING:
			return false;
		}

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
			offset.x -= 400.0f * Time::DeltaTime();
			mDirType = EDirType::LEFT;
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			//rig->AddForce(Vector2(+200.0f, 0.0f));
			offset.x += 400.0f * Time::DeltaTime();
			mDirType = EDirType::RIGHT;
		}
		if (mbAir == true)
		{
			if (core::Input::GetKey(core::EKeyCode::W))
			{
				offset.y -= 400.0f * Time::DeltaTime();
			}
			if (core::Input::GetKey(core::EKeyCode::S))
			{
				offset.y += 400.0f * Time::DeltaTime();
			}
		}
		transform->SetPos(pos + offset);
	}

	void Chalice::DashPositionUpdate(EStateType _type)
	{
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();

		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		Vector2 offset;
		float dash_valocity = 2.5f;

		if (_type == EStateType::START)
		{
			mDashVelocity = 0.0f;
			if ((mbDash == true && mDirType == EDirType::LEFT))
			{
				mDashVelocity -= 400.0f * dash_valocity * Time::DeltaTime();
			}
			if ((mbDash == true && mDirType == EDirType::RIGHT))
			{
				mDashVelocity += 400.0f * dash_valocity * Time::DeltaTime();
			}
		}

		offset.x = mDashVelocity;
		transform->SetPos(pos + offset);
	}

	void Chalice::Create()
	{
		Transform* tf = mOwner->GetComponent<Transform>();

		mState = ECharacterState::Idle;


		Animator* ani = mOwner->GetComponent<Animator>();
#pragma region nomal ani
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Idle\\Right", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Idle\\Left", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Regular\\Right", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Regular\\Left", Vector2::Zero, 0.1f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Regular\\Turn\\Right", Vector2::Zero, 0.1f, true);

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Double Jump\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Double Jump\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Fall\\Left", Vector2::Zero, 0.08f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Fall\\Right", Vector2::Zero, 0.08f, true);


		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\DuckIdle\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\DuckIdle\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Duck\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Duck\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Stand Up\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Stand Up\\Right", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\GroundDash\\Right", Vector2::Zero, 0.02f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\GroundDash\\Left", Vector2::Zero, 0.02f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\JumpDash\\Right", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\JumpDash\\Left", Vector2::Zero, 0.04f, true);
#pragma endregion

#pragma region air ani 
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\Straight", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\AirTransitions\\Up", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\AirTransitions\\Down", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\Up", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\Down", Vector2::Zero, 0.04f, true);
		
		Vector2 size = ani->FindAnimation(L"AirIdleStraight")->GetSpriteSize();
		GameObject* shooter = mOwner->FindChild(L"Shooter").get();
		Transform* s_pos = shooter->GetComponent<Transform>();
		s_pos->SetOffset(Vector2{ size.x/1.5f,-(size.y / 5.0f) });
		Animator* s_ani = shooter->GetComponent<Animator>();
		s_ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\Shoot Sparks", Vector2::Zero, 0.05f, false);
		s_ani->Play(L"Ms.Chalice_AirShoot Sparks", true);
		s_ani->SetActive(false);
#pragma endregion

		ani->GetCompleteEvent(L"DuckLeft") = std::bind([this, ani]()->void
		{
			std::wstring anikey = ani->GetDirAniKey(L"DuckIdle", mDirType);
			ani->Play(anikey, true);
		});
		ani->GetCompleteEvent(L"DuckRight") = std::bind([this, ani]()->void
		{
			std::wstring anikey = ani->GetDirAniKey(L"DuckIdle", mDirType);
			ani->Play(anikey, true);
		});
		ani->GetCompleteEvent(L"Stand UpLeft") = std::bind([this]()->void {SetNextAniInfo(); });
		ani->GetCompleteEvent(L"Stand UpRight") = std::bind([this]()->void {SetNextAniInfo(); });
		ani->GetCompleteEvent(L"GroundDashRight") = std::bind([this]()->
			void
		{
			SetNextAniInfo();
			ResetDash();
		}
		);
		ani->GetCompleteEvent(L"GroundDashLeft") = std::bind([this]()->
			void
		{
			SetNextAniInfo();
			ResetDash();
		});
		ani->GetCompleteEvent(L"JumpDashRight") = std::bind([this, ani]()->
			void
		{
			ResetDash();
			ani->Play(L"Double JumpRight", false);
		});
		ani->GetCompleteEvent(L"JumpDashLeft") = std::bind([this, ani]()->
			void
		{
			ResetDash();
			ani->Play(L"Double JumpLeft", false);
		});

		ani->GetCompleteEvent(L"AirTransitionsUp") = std::bind([this, ani]()->
			void
		{
			ani->Play(L"AirIdleUp", true);
		});

		ani->GetCompleteEvent(L"AirTransitionsDown") = std::bind([this, ani]()->
			void
		{
			ani->Play(L"AirIdleDown", true);
		});
	}


	void Chalice::AirMove()
	{
		std::wstring ani_name;
		Animator* ani = mOwner->GetComponent<Animator>();

		if (core::Input::GetKeyUp(core::EKeyCode::A)
			|| core::Input::GetKeyUp(core::EKeyCode::D)
			|| core::Input::GetKeyUp(core::EKeyCode::W)
			|| core::Input::GetKeyUp(core::EKeyCode::S)
			)
		{
			if (core::Input::GetKeyUp(core::EKeyCode::W)
				|| core::Input::GetKeyUp(core::EKeyCode::S))
			{
				mbAirStartFlag = false;
			}
			ani->Play(L"AirIdleStraight", true);
			mState = ECharacterState::Idle;
		}

		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S)
			|| core::Input::GetKey(core::EKeyCode::A)
			|| core::Input::GetKey(core::EKeyCode::D)
			|| core::Input::GetKey(core::EKeyCode::W)
			|| core::Input::GetKey(core::EKeyCode::S)
			)
		{
			mState = ECharacterState::Move;
			bool flag = false;
			std::wstring cur_ani = ani->GetCurAniName();
			if (core::Input::GetKeyDown(core::EKeyCode::W))
			{
				ani_name = L"AirTransitionsUp";
			}
			else if (core::Input::GetKeyDown(core::EKeyCode::S))
			{
				ani_name = L"AirTransitionsDown";
			}
			else if (core::Input::GetKey(core::EKeyCode::W))
			{
				if (mbAirStartFlag == false)
				{
					ani_name = L"AirTransitionsUp";
				}
			}
			else if (core::Input::GetKey(core::EKeyCode::S))
			{
				if (mbAirStartFlag == false)
				{
					ani_name = L"AirTransitionsDown";
				} 
			}
			mbAirStartFlag = true;
			if (ani_name.size() > 0)
				ani->Play(ani_name, false);
		}
		PositionUpdate();
	}

	void Chalice::AirShoot()
	{
		GameObject* shooter = mOwner->FindChild(L"Shooter").get();
		Animator* ani = shooter->GetComponent<Animator>();
		Transform* tf = shooter->GetComponent<Transform>();
		if (core::Input::GetKeyDown(core::EKeyCode::SPACE)|| core::Input::GetKey(core::EKeyCode::SPACE))
		{
			mState = ECharacterState::Shoot;

			ani->SetActive(true);

			const Vector2 pos = tf->GetPos();
			Bullet* bullet = nullptr;
			//총알 세개 스폰해서 정보 셋팅하고 날라가게하기.
			std::shared_ptr<GameObject> obj1 = core::ObjectPool<Bullet>::Spawn();
			bullet = obj1->GetComponent<Bullet>();
			bullet->SetAnimation(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\Shoot\\AirBullet\\A", Vector2::Zero, 0.04f);
			bullet->CreateInfo(pos, Vector2{ 2000.0f,-100.0f });
			
			std::shared_ptr<GameObject> obj2 = core::ObjectPool<Bullet>::Spawn();
			bullet = obj2->GetComponent<Bullet>();
			bullet->SetAnimation(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\Shoot\\AirBullet\\B", Vector2::Zero, 0.04f);
			bullet->CreateInfo(pos, Vector2{ 2000.0f,pos.y });

			std::shared_ptr<GameObject> obj3 = core::ObjectPool<Bullet>::Spawn();
			bullet = obj3->GetComponent<Bullet>();
			bullet->SetAnimation(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\Shoot\\AirBullet\\B", Vector2::Zero, 0.04f);
			bullet->CreateInfo(pos, Vector2{ 2000.0f,1000.0f });

			//bullet->SetEndPos(Vector2{ 1000.0f,tf->GetPos().y });
			SceneManager::GetActiveScene()->AddGameObject(obj1, ELayerType::Bullet);
			SceneManager::GetActiveScene()->AddGameObject(obj2, ELayerType::Bullet);
			SceneManager::GetActiveScene()->AddGameObject(obj3, ELayerType::Bullet);
		}
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
