#include "Chalice.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Camera.h"
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
		mDashVelocity = 1.0f;

	}

	void Chalice::Update()
	{
		if (mAni->GetActive() == false)
		{
			HeadAndRegSetAniPos();
		}
		Input();
	}

	void Chalice::Render(HDC hdc)
	{
	}

	void Chalice::Release()
	{
	}
	void Chalice::Input()
	{
		while (core::Input::KeyMessageQueueEmpty() == false)
		{
			core::Input::PushInfo& push = core::Input::GetQueueFront();
			Animator* ani = mOwner->GetComponent<Animator>();
			std::wstring ani_name;

			core::Input::KeyMessageQueuePop();

			//fix
			fix_start(push);

			shoot_start(push);
			//dash 
			dash_start(push);

			/*
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
			else*/
			{
				if (mbDash == false)
				{
					//duck
					if (duck_start(push) == true)
						return;
					//jump / double jump 
					jump(push);
				}

				switch (mState)
				{
				case ECharacterState::Idle:
					idle(push);
					break;
				case ECharacterState::Move:
					move(push);
					break;
				case ECharacterState::Duck:
					duck(push);
					break;
				case ECharacterState::Shoot:
					shoot(push);
					break;
				case ECharacterState::Dash:
					dash(push);
					break;
				case ECharacterState::Fix:
					fix(push);
					break;
				}
			}
		}
		//position update
		PositionUpdate();
	}
	void Chalice::move(const PushInfo& _push_info)
	{
		std::wstring ani_name;
		Animator* ani = mOwner->GetComponent<Animator>();
		core::EKeyState state = _push_info.state;
		switch (_push_info.keycode)
		{
		case core::EKeyCode::Left:
			if (state == core::EKeyState::Down && core::Input::GetKeyDown(core::EKeyCode::Right))
			{
				return;
			}
			if (state == core::EKeyState::Up && core::Input::GetKey(core::EKeyCode::Right))
			{
				mDirType = EDirType::RIGHT;
				if (mJump == 0)
					ani_name = L"RegularRight";
			}
			else if (state == core::EKeyState::Up && mJump == 0)
			{
				mState = ECharacterState::Idle;
				if (mJump == 0)
					ani_name = ani->GetDirAniKey(L"Idle", mDirType);
			}
			break;
		case core::EKeyCode::Right:
			if (state == core::EKeyState::Down && core::Input::GetKeyDown(core::EKeyCode::Left))
			{
				return;
			}
			if (state == core::EKeyState::Up && core::Input::GetKey(core::EKeyCode::Left))
			{
				mDirType = EDirType::LEFT;
				if (mJump == 0)
					ani_name = L"RegularLeft";
			}
			else if (state == core::EKeyState::Up && mJump == 0)
			{
				mState = ECharacterState::Idle;
				if (mJump == 0)
					ani_name = ani->GetDirAniKey(L"Idle", mDirType);
			}
			break;
			/*	case core::EKeyCode::W:
					if (state == core::EKeyState::Down && core::Input::GetKeyDown(core::EKeyCode::S))
					{
						return;
					}
					break;
				case core::EKeyCode::S:
					if (state == core::EKeyState::Down && core::Input::GetKeyDown(core::EKeyCode::W))
					{
						return;
					}
					break;*/
		}

		if (ani_name.size() > 0)
		{
			ani->Play(ani_name, true);
		}
	}

	void Chalice::idle(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();

		std::wstring ani_name;


		if (mbSit == true)
			return;
		if (mJump >= 1)
			return;

		if (_push_info.state == core::EKeyState::Down)
		{
			//duck이 아닐때, 오른쪽 or 왼쪽 이동 입력 받을 수 있음.
			if (_push_info.keycode == core::EKeyCode::Left || core::Input::GetKey(core::EKeyCode::Left))
			{
				ani_name = L"RegularLeft";
				mDirType = EDirType::LEFT;
				mState = ECharacterState::Move;
			}
			if (_push_info.keycode == core::EKeyCode::Right || core::Input::GetKey(core::EKeyCode::Right))
			{
				ani_name = L"RegularRight";
				mDirType = EDirType::RIGHT;
				mState = ECharacterState::Move;
			}

			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}
		}
	}

	void Chalice::shoot(const PushInfo& _push_info)
	{
		//fix mode 

		//jump mode
		//move mode
		//duck mode
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		bool horizontal_flag = false;
		core::EKeyCode horizontal_key;
		core::EKeyCode vertical_key;
		horizontal_flag = PriorityInput(core::EKeyCode::Left, core::EKeyCode::Right, horizontal_key);
		EDirType h_key = GetDirType(horizontal_key);
		bool vertical_flag = PriorityInput(core::EKeyCode::Up, core::EKeyCode::Down, vertical_key);
		EDirType v_key = GetDirType(vertical_key);
		
		if (core::Input::GetKey(core::EKeyCode::Z) || core::Input::GetKeyDown(core::EKeyCode::Z))
		{
			if (mbDash == false)
			{
				mShooter->SetActive(true);
			}

			if (mJump > 0)
			{
				JumpShoot(horizontal_flag,vertical_flag,h_key,v_key);
			}
			else if (core::Input::GetKey(core::EKeyCode::C)
				|| _push_info.keycode == core::EKeyCode::C && _push_info.state == core::EKeyState::Down)
			{//fix mode
				mbStopPositionUpdate = true;

				if (horizontal_flag == true && vertical_flag == true)
				{
					mDirType = h_key;
					ani_name = ani->GetDirAniKey(L"ShootAim", h_key, v_key);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(2, h_key, v_key));
				}
				else if (horizontal_flag == true)
				{
					mDirType = h_key;
					ani_name = ani->GetDirAniKey(L"ShootStraight", h_key);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, h_key));
				}
				else if (vertical_flag == true)
				{
					ani_name = ani->GetDirAniKey(L"Shoot", mDirType, v_key);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(3, EDirType::STAY, mDirType, v_key));
				}
				else
				{
					ani_name = ani->GetDirAniKey(L"ShootStraight", mDirType);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, mDirType));
				}

			}
			else
			{
				if (_push_info.keycode == core::EKeyCode::Down && _push_info.state == core::EKeyState::Up)
				{
					duck(_push_info);
					mState = ECharacterState::Shoot;
				}
				if (_push_info.keycode == core::EKeyCode::Down && _push_info.state == core::EKeyState::Down
					|| core::Input::GetKey(core::EKeyCode::Down)) // duck mode
				{
					mbSit = true;
					if (horizontal_flag == true)
						mDirType = h_key;
					ani_name = ani->GetDirAniKey(L"ShootDuck", mDirType);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(2, EDirType::SIT, mDirType));
				}
				else if (horizontal_flag == true && vertical_flag == true)//run and up  shoot
				{
					mDirType = h_key;
					if (v_key == EDirType::DOWN)
						return;
					ani_name = ani->GetDirAniKey(L"RunShootDiagonalUp", mDirType);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(3, EDirType::RUN, h_key, v_key));
				}
				else if (horizontal_flag == true) // run shoot
				{
					//뛰는 모션.
					mDirType = h_key;
					ani_name = ani->GetDirAniKey(L"RunShootStraight", h_key);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(2, EDirType::RUN, h_key));
				}
				else if (vertical_flag == true)
				{
					if (v_key == EDirType::DOWN)
						return;
					ani_name = ani->GetDirAniKey(L"Shoot", mDirType, v_key);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(3, EDirType::STAY, mDirType, v_key));
				}
				else//stay straight soot
				{
					ani_name = ani->GetDirAniKey(L"ShootStraight", mDirType);
					mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, mDirType));
				}
			}
		}
		else if (_push_info.keycode == core::EKeyCode::Z && _push_info.state == core::EKeyState::Up)
		{
			mShooter->SetActive(false);

			if (mJump == 0)
			{
				if (mbSit == true)
				{
					mState = ECharacterState::Duck;
					ani_name = ani->GetDirAniKey(L"DuckIdle", mDirType);
				}
				else if (horizontal_flag == true)
				{
					mState = ECharacterState::Move;
					ani_name = ani->GetDirAniKey(L"Regular", mDirType);
				}
				else
				{
					mState = ECharacterState::Idle;
					ani_name = ani->GetDirAniKey(L"Idle", mDirType);
				}
			}
		}


		if (ani_name.size() > 0)
		{
			ani->Play(ani_name, true);
		}
	}

	void Chalice::shoot_start(const PushInfo& _push_info)
	{
		if (_push_info.keycode == core::EKeyCode::Z && _push_info.state == core::EKeyState::Down && mbDash == false)
		{
			mState = ECharacterState::Shoot;
		}

	}

	void Chalice::death(const PushInfo& _push_info)
	{
	}

	void Chalice::duck(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		if (_push_info.keycode == core::EKeyCode::Down && _push_info.state == core::EKeyState::Up)
		{
			mbSit = false;
			bool keydown_flag = false;
			if (core::Input::GetKey(core::EKeyCode::Right) && core::Input::GetKey(core::EKeyCode::Left))
			{
				keydown_flag = true;
				core::EKeyCode key = core::Input::GetFirstPriorityKey(core::EKeyCode::Right, core::EKeyCode::Left);
				switch (key)
				{
				case core::EKeyCode::Left:
					mDirType = EDirType::LEFT;
					break;
				case core::EKeyCode::Right:
					mDirType = EDirType::RIGHT;
					break;
				}
			}
			else if (core::Input::GetKey(core::EKeyCode::Right))
			{
				keydown_flag = true;
				mDirType = EDirType::RIGHT;
			}
			else if (core::Input::GetKey(core::EKeyCode::Left))
			{
				keydown_flag = true;
				mDirType = EDirType::LEFT;
			}
			if (keydown_flag == false)
			{
				ani_name = ani->GetDirAniKey(L"Idle", mDirType);
				mState = ECharacterState::Idle;
			}
			else if (mJump == 0)
			{
				ani_name = ani->GetDirAniKey(L"Regular", mDirType);
				mState = ECharacterState::Move;
			}
			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}
			return;
		}


		if (mbSit == true && _push_info.state == core::EKeyState::Down && _push_info.keycode != core::EKeyCode::SPACE)
		{
			if (_push_info.keycode == core::EKeyCode::Left && core::Input::GetKey(core::EKeyCode::Right) == false)
				mDirType = EDirType::LEFT;
			else if (_push_info.keycode == core::EKeyCode::Right && core::Input::GetKey(core::EKeyCode::Left) == false)
				mDirType = EDirType::RIGHT;

			ani_name = ani->GetDirAniKey(L"DuckIdle", mDirType);
			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}
			return;
		}
	}

	bool Chalice::duck_start(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		if (mState == ECharacterState::Fix)
			return false;
		if (core::Input::GetKey(core::EKeyCode::C))
		{
			return false;
		}
		if (mState == ECharacterState::Shoot)
			return false;
		if (mJump == 0 && _push_info.keycode == core::EKeyCode::Down && _push_info.state == core::EKeyState::Down)
		{
			mbSit = true;
			ani_name = ani->GetDirAniKey(L"Duck", mDirType);
			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
				mState = ECharacterState::Duck;
			}
			return true;
		}
		return false;
	}

	void Chalice::dash(const PushInfo& _push_info)
	{
	}

	void Chalice::dash_start(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;

		if (mbDash == false && _push_info.keycode == core::EKeyCode::SHIFT && _push_info.state == core::EKeyState::Down)
		{
			mbDash = true;
			mOwner->GetComponent<Rigidbody>()->SetActive(false);
			if (core::Input::GetKey(core::EKeyCode::Z))
			{
				if (mJump != 0)
				{
					mHead->SetActive(false);
					mReg->SetActive(false);

					mAni->SetActive(true);
				}
				mShooter->SetActive(false);
			}

			mState = ECharacterState::Dash;
			mDashVelocity = 2.0f;
			if (mJump == 0)
				ani_name = ani->GetDirAniKey(L"GroundDash", mDirType);
			else
				ani_name = ani->GetDirAniKey(L"JumpDash", mDirType);

			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}
			mDashTime = Time::DeltaTime();
		}
	}

	void Chalice::jump(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		if (_push_info.keycode == core::EKeyCode::SPACE && _push_info.state == core::EKeyState::Down)
		{
			mbSit = false;
			if (mJump == 0)
			{
				mJump++;
				mFirstJumpTime = _push_info.Time;

				ani_name = ani->GetDirAniKey(L"Jump", mDirType);
			}
			else if (mJump == 1)
			{
				float offset = _push_info.Time - mFirstJumpTime;
				if (offset <= 1.0f || mbParry == true)
				{
					mJump++;
					ani_name = ani->GetDirAniKey(L"Double Jump", mDirType);
				}
			}

			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
				Rigidbody* rigid = mOwner->GetComponent<Rigidbody>();
				Vector2 velocity = rigid->GetVelocity();

				velocity.y -= 1050.0f;


				rigid->SetVelocity(velocity);
				rigid->SetGround(false);

				//mState = ECharacterState::Move;
			}
		}
	}
	void Chalice::fix(const PushInfo& _push_info)
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		bool horizontal_flag = false;
		core::EKeyCode horizontal_key;
		core::EKeyCode vertical_key;
		horizontal_flag = PriorityInput(core::EKeyCode::Left, core::EKeyCode::Right, horizontal_key);

		EDirType h_key = GetDirType(horizontal_key);


		if (_push_info.keycode == core::EKeyCode::C && _push_info.state == core::EKeyState::Up)
		{
			mbStopPositionUpdate = false;
			if (mJump == 0)
			{
				if (horizontal_flag == false)
				{
					ani_name = ani->GetDirAniKey(L"Idle", mDirType);
					mState = ECharacterState::Idle;
				}
				else
				{
					mDirType = h_key;
					ani_name = ani->GetDirAniKey(L"Regular", mDirType);
					mState = ECharacterState::Move;
				}

			}
			
			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
			}
		}
		else
		{
			bool vertical_flag = PriorityInput(core::EKeyCode::Up, core::EKeyCode::Down, vertical_key);
			EDirType v_key = GetDirType(vertical_key);
			//총알 방향 45도 회전
			if (horizontal_flag == true && vertical_flag == true)
			{
				ani_name = ani->GetDirAniKey(L"Diagonal", h_key, v_key);
				ani->Play(ani_name, true);
				mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(2, h_key, v_key));
			}//horizontal straight
			else if (horizontal_flag == true)
			{
				ani_name = ani->GetDirAniKey(L"AimStraight", h_key);
				ani->Play(ani_name, true);
				mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, h_key));
				mDirType = h_key;
			}
			else if (vertical_flag == true)
			{
				ani_name = ani->GetDirAniKey(L"Aim", mDirType, v_key);
				ani->Play(ani_name, true);
				mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(3, EDirType::STAY, mDirType, v_key));
			}
			else
			{
				if (mJump == 0)
				{
					ani_name = ani->GetDirAniKey(L"Idle", mDirType);
					ani->Play(ani_name, true);
				}
			}
		}
	}
	void Chalice::fix_start(const PushInfo& _push_info)
	{
		if ((_push_info.keycode==core::EKeyCode::C && _push_info.state== core::EKeyState::Down)
			||core::Input::GetKey(core::EKeyCode::C))
		{
			if (mbSit == true)
				mbSit = false;
			if (mbDash == false && mState != ECharacterState::Shoot&&mJump==0)
			{
				mbStopPositionUpdate = true;
				mState = ECharacterState::Fix;
			}
		}
		if (core::Input::GetKeyUp(core::EKeyCode::C))
		{
			mbStopPositionUpdate = false;
		}
	}
	void Chalice::Parrying()
	{
		Character::Parrying();
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();
		Animator* ani = mOwner->GetComponent<Animator>();

		Vector2 velocity = rig->GetVelocity();

		velocity.y -= 1050.0f * 1.2f;

		rig->SetVelocity(velocity);
		rig->SetGround(false);

		ani->Play(L"RegularWithout Streaks", true);
	}
	void Chalice::PositionUpdate()
	{
		if (mbSit == true)
			return;
		Rigidbody* rig = mOwner->GetComponent<Rigidbody>();

		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		Vector2 offset;
		if (mbDash == true)
		{
			if (mDirType == EDirType::LEFT)
			{
				offset.x -= 400.0f * Time::DeltaTime() * mDashVelocity;
			}
			else if (mDirType == EDirType::RIGHT)
			{
				offset.x += 400.0f * Time::DeltaTime() * mDashVelocity;
			}
		}
		else if (mbStopPositionUpdate == true)
		{
			return;
		}
		else if (core::Input::GetKey(core::EKeyCode::Left) && core::Input::GetKey(core::EKeyCode::Right))
		{
			core::EKeyCode code = core::Input::GetFirstPriorityKey(core::EKeyCode::Left, core::EKeyCode::Right);
			switch (code)
			{
			case core::EKeyCode::Left:
				offset.x -= 400.0f * Time::DeltaTime() * mDashVelocity;
				mDirType = EDirType::LEFT;
				break;
			case core::EKeyCode::Right:
				offset.x += 400.0f * Time::DeltaTime() * mDashVelocity;
				mDirType = EDirType::RIGHT;
				break;
			}
		}
		else if (core::Input::GetKey(core::EKeyCode::Left))
		{
			//rig->AddForce(Vector2(-200.0f, 0.0f));
			offset.x -= 400.0f * Time::DeltaTime() * mDashVelocity;
			mDirType = EDirType::LEFT;
		}
		else if (core::Input::GetKey(core::EKeyCode::Right))
		{
			//rig->AddForce(Vector2(+200.0f, 0.0f));
			offset.x += 400.0f * Time::DeltaTime() * mDashVelocity;
			mDirType = EDirType::RIGHT;
		}

		if (mbAir == true)
		{
			if (core::Input::GetKey(core::EKeyCode::Up))
			{
				offset.y -= 400.0f * Time::DeltaTime();
			}
			if (core::Input::GetKey(core::EKeyCode::Down))
			{
				offset.y += 400.0f * Time::DeltaTime();
			}
		}
		mMoveOffset = offset;
		transform->SetPos(pos + offset);
		if (Camera::UseTarget() == true)
		{
			SceneManager::ChagePosGameObjects(offset);
		}
	}

	void Chalice::Create()
	{
		Transform* tf = mOwner->GetComponent<Transform>();

		mState = ECharacterState::Idle;
		mAni = mOwner->GetComponent<Animator>();

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
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\GroundDash\\Right", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\GroundDash\\Left", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\JumpDash\\Right", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Dash\\JumpDash\\Left", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Fall\\Right", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Fall\\Left", Vector2::Zero, 0.03f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Regular\\Without Streaks", Vector2::Zero, 0.05f, true);

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\AimStraight\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\AimStraight\\Left", Vector2::Zero, 0.05f, true);

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\Diagonal\\DiagonalUp\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\Diagonal\\DiagonalUp\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\Diagonal\\DiagonalDown\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\Diagonal\\DiagonalDown\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\AimUp\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\AimUp\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\AimDown\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Aim\\AimDown\\Right", Vector2::Zero, 0.05f, true);

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\Diagonal\\ShootAimDown\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\Diagonal\\ShootAimDown\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\Diagonal\\ShootAimUp\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\Diagonal\\ShootAimUp\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\ShootDown\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\ShootDown\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\ShootStraight\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\ShootStraight\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\ShootUp\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Shoot\\ShootUp\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Shoot\\DuckLeft", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Shoot\\DuckRight", Vector2::Zero, 0.05f, true);

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Shoot\\RunShootStraight\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Shoot\\RunShootStraight\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Shoot\\RunShootDiagonalUp\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Run\\Shoot\\RunShootDiagonalUp\\Right", Vector2::Zero, 0.05f, true);
#pragma endregion

		Vector2 size = ani->FindAnimation(L"AimStraightRight")->GetSpriteSize();
#pragma region jump head / reg
		GameObject* reg = mOwner->FindChild(L"Reg").get();
		mReg = reg;
		Animator* reg_ani = reg->GetComponent<Animator>();

		GameObject* head = mOwner->FindChild(L"Head").get();
		mHead = head;
		Transform* head_tf = mHead->GetComponent<Transform>();
		
		Animator * head_ani = mHead->GetComponent<Animator>();
	
		//reg
		reg_ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Shoot\\Legs", Vector2::Zero, 0.05f, true);
		reg_ani->Play(L"ShootLegs", true);
		//head
		head_ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Shoot\\Head\\JumpShootHeadStraight\\Right", Vector2::Zero, 0.05f, true);
		head_ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Shoot\\Head\\JumpShootHeadStraight\\Left", Vector2::Zero, 0.05f, true);
		head_ani->Play(L"JumpShootHeadStraightRight",true);

		head_tf->SetOffset(Vector2{ 0.0f,-(reg_ani->GetImageSize().y/1.5f) });

		mReg->SetActive(false);
		mHead->SetActive(false);
#pragma endregion
	
		GameObject* shooter = mOwner->FindChild(L"Shooter").get();
		mShooter = shooter;
		mShooter->SetActive(false);
		RegisterShooterSpawnPos();

		Transform* s_pos = mShooter->GetComponent<Transform>();
		s_pos->SetOffset(GetShooterSpawnPos(1, EDirType::RIGHT));

		Animator* s_ani = shooter->GetComponent<Animator>();
		s_ani->CreateAnimations(L"..\\Resources\\weapon\\shooter_effect", Vector2::Zero, 0.05f, false);
		s_ani->Play(L"weaponshooter_effect", true);

		

#pragma region air ani 
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\Straight", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\AirTransitions\\Up", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\AirTransitions\\Down", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\Up", Vector2::Zero, 0.04f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\AirIdle\\Down", Vector2::Zero, 0.04f, true);

		/*Vector2 size = ani->FindAnimation(L"AirIdleStraight")->GetSpriteSize();
		GameObject* shooter = mOwner->FindChild(L"Shooter").get();
		Transform* s_pos = shooter->GetComponent<Transform>();
		s_pos->SetOffset(Vector2{ size.x / 1.5f,-(size.y / 5.0f) });
		Animator* s_ani = shooter->GetComponent<Animator>();
		s_ani->CreateAnimations(L"..\\Resources\\Chalice\\Ms.Chalice_Air\\Shoot Sparks", Vector2::Zero, 0.05f, false);
		s_ani->Play(L"Ms.Chalice_AirShoot Sparks", true);
		s_ani->SetActive(false);*/
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
			if (mJump == 2)
				ani->Play(L"Double JumpRight", true);
			else if (mJump == 1)
				ani->Play(L"FallRight", true);
		});
		ani->GetCompleteEvent(L"JumpDashLeft") = std::bind([this, ani]()->
			void
		{
			ResetDash();
			if (mJump == 2)
				ani->Play(L"Double JumpLeft", true);
			else if (mJump == 1)
				ani->Play(L"FallLeft", true);
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
		else if (core::Input::GetKey(core::EKeyCode::SPACE) || core::Input::GetKeyDown(core::EKeyCode::SPACE))
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

	void Chalice::AirShoot()
	{
		GameObject* shooter = mOwner->FindChild(L"Shooter").get();
		Animator* ani = shooter->GetComponent<Animator>();
		Transform* tf = shooter->GetComponent<Transform>();
		if (core::Input::GetKeyDown(core::EKeyCode::SPACE) || core::Input::GetKey(core::EKeyCode::SPACE))
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

	void Chalice::RegisterShooterSpawnPos()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		Vector2 size = ani->FindAnimation(L"AimStraightRight")->GetSpriteSize();

		Vector2 offset = { size.x / 2.0f,-(size.y / 5.5f) };
		//l,u 같은 중복은 bit 연산하기.
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RIGHT, (offset)));
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::LEFT, Vector2{ -(offset.x) - 10,offset.y }));

		//r|u
		Vector2 rotat = math::Rotate(offset, 45);
		float dot = math::Dot(rotat, offset);
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RIGHT | (UINT)EDirType::UP, Vector2{ offset.x,offset.y - dot }));
		//r|d
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RIGHT | (UINT)EDirType::DOWN, Vector2{ offset.x,offset.y + dot }));

		//s|r|u
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::STAY | (UINT)EDirType::RIGHT | (UINT)EDirType::UP, Vector2{ offset.x - (offset.x / 2.0f),offset.y - (size.y / 2.0f) }));

		//s|r|d
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::STAY | (UINT)EDirType::RIGHT | (UINT)EDirType::DOWN, Vector2{ offset.x - (offset.x / 2.0f),(offset.y * 2.0f) + (size.y / 2.0f) }));

		//s|l|u
		offset = mShooterSpawnPos[(UINT)EDirType::LEFT];
		rotat = math::Rotate(offset, -45);
		dot = math::Dot(offset, rotat);
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::STAY | (UINT)EDirType::LEFT | (UINT)EDirType::UP, Vector2{ offset.x + dot ,offset.y - (dot * 1.7f) }));

		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::STAY | (UINT)EDirType::LEFT | (UINT)EDirType::DOWN, Vector2{ offset.x + dot,offset.y + dot }));

		//l|u

		rotat = math::Rotate(offset, 45);
		dot = math::Dot(rotat, offset);
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::LEFT | (UINT)EDirType::UP, Vector2{ offset.x,offset.y - dot }));

		//l|d
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::LEFT | (UINT)EDirType::DOWN, Vector2{ offset.x,offset.y + dot }));

		size = ani->FindAnimation(L"ShootDuckRight")->GetSpriteSize();
		offset = { size.x / 2.0f,-(size.y / 5.5f) };
		//duck left
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::SIT | (UINT)EDirType::RIGHT, (offset)));
		//duck right
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::SIT | (UINT)EDirType::LEFT, Vector2{ -(offset.x), offset.y }));

		size = ani->FindAnimation(L"RunShootDiagonalUpRight")->GetSpriteSize();
		offset = { size.x / 2.0f,-(size.y / 5.5f) };
		//run up left
		rotat = math::Rotate(offset, 45);
		dot = math::Dot(offset, rotat);
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RUN | (UINT)EDirType::LEFT | (UINT)EDirType::UP, Vector2{ offset.x - (dot * 2.5f) ,offset.y - (dot) }));
		//run up right
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RUN | (UINT)EDirType::RIGHT | (UINT)EDirType::UP, Vector2{ offset.x ,offset.y - (size.y / 3.5f) }));

		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RUN | (UINT)EDirType::RIGHT, Vector2{ offset.x - 10,offset.y }));
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RUN | (UINT)EDirType::LEFT, Vector2{ -(offset.x) + 10,offset.y }));
	}

	
	void Chalice::JumpShoot(bool h_flag, bool v_flag, EDirType h_key, EDirType v_key)
	{
		mOwner->GetComponent<Animator>()->SetActive(false);
		mHead->SetActive(true);
		mReg->SetActive(true);

		Animator* head_ani = mHead->GetComponent<Animator>();
		Animator* reg_ani = mReg->GetComponent<Animator>();
		std::wstring h_name;
		std::wstring r_name =L"ShootLegs";
		Transform* head_tf = mHead->GetComponent<Transform>();
		Vector2 offset = head_tf->GetOffset();
		if (h_flag == true)
		{
			h_name = head_ani->GetDirAniKey(L"JumpShootHeadStraight", h_key);
			
			if (h_key == EDirType::LEFT)
			{
				offset.x = -10.0f;
			}
			else
			{
				offset.x = 10.0f;
			}
			mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, h_key));
		}
		else if (h_flag == false)
		{
			if (mDirType == EDirType::LEFT)
			{
				offset.x = -10.0f;
			}
			else
			{
				offset.x = 10.0f;
			}
			h_name = head_ani->GetDirAniKey(L"JumpShootHeadStraight", mDirType);
			mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, mDirType));
		}

	
		head_tf->SetOffset(offset);

		head_ani->Play(h_name, true);
		reg_ani->Play(r_name, false);
	}

	void Chalice::HeadAndRegSetAniPos()
	{
		Animator* head_ani = mHead->GetComponent<Animator>();
		Transform* head_tf = mHead->GetComponent<Transform>();
		Animator* reg_ani = mReg->GetComponent<Animator>();

		Vector2 pos = head_tf->GetOffset();
		Vector2 size2 = reg_ani->GetImageSize();
		head_tf->SetOffset(Vector2{ pos.x,-(size2.y / 1.5f) });
	}

}