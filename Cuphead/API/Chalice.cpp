#include "Chalice.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"

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

			//dash 
			dash_start(push);
			//fix
			fix_start(push);
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
			//duck�� �ƴҶ�, ������ or ���� �̵� �Է� ���� �� ����.
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

				mState = ECharacterState::Move;
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

			if (horizontal_flag == false)
			{
				ani_name = ani->GetDirAniKey(L"Idle", mDirType);
				mState = ECharacterState::Idle;
			}
			else
			{
				ani_name = ani->GetDirAniKey(L"Regular", mDirType);
				mState = ECharacterState::Move;
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
			//�Ѿ� ���� 45�� ȸ��
			if (horizontal_flag ==true && vertical_flag == true)
			{
				ani_name = ani->GetDirAniKey(L"Diagonal", h_key, v_key);
				ani->Play(ani_name, true);
				mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(2, h_key,v_key));
			}//horizontal straight
			else if (horizontal_flag == true)
			{
				ani_name = ani->GetDirAniKey(L"AimStraight",h_key);
				ani->Play(ani_name, true);
				mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(1, h_key));
				mDirType = h_key;
			}
			else if (vertical_flag == true)
			{
				ani_name = ani->GetDirAniKey(L"Aim", mDirType, v_key);
				ani->Play(ani_name, true);
				mShooter->GetComponent<Transform>()->SetOffset(GetShooterSpawnPos(3,EDirType::STAY,mDirType,v_key));
			}
		}
	}
	void Chalice::fix_start(const PushInfo& _push_info)
	{
		if (core::Input::GetKey(core::EKeyCode::C))
		{
			mbStopPositionUpdate = true;
			mState = ECharacterState::Fix;
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

		Vector2 size = ani->FindAnimation(L"AimStraightRight")->GetSpriteSize();
		GameObject* shooter = mOwner->FindChild(L"Shooter").get();
		mShooter = shooter;
		
		RegisterShooterSpawnPos();
		
		Transform* s_pos = mShooter->GetComponent<Transform>();
		s_pos->SetOffset(GetShooterSpawnPos(1, EDirType::RIGHT));

		Animator* s_ani = shooter->GetComponent<Animator>();
		s_ani->CreateAnimations(L"..\\Resources\\weapon\\shooter_effect", Vector2::Zero, 0.05f, false);
		s_ani->Play(L"weaponshooter_effect", true);
		s_ani->SetActive(true);
#pragma endregion

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
				ani->Play(L"FallRight", true);
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
			//�Ѿ� ���� �����ؼ� ���� �����ϰ� ���󰡰��ϱ�.
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

	bool Chalice::PriorityInput(core::EKeyCode _code1, core::EKeyCode _code2, core::EKeyCode& _result)
	{
		if ((core::Input::GetKeyDown(_code1) && core::Input::GetKeyDown(_code2)) ||(core::Input::GetKey(_code1) && core::Input::GetKey(_code2)))
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

	EDirType Chalice::GetDirType(const core::EKeyCode& _code)
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
		//l,u ���� �ߺ��� bit �����ϱ�.
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::RIGHT, (offset)));
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::LEFT, Vector2{ -(offset.x)-10,offset.y }));

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
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::STAY | (UINT)EDirType::LEFT | (UINT)EDirType::UP, Vector2{ offset.x+dot ,offset.y - (dot*1.7f) }));

		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::STAY | (UINT)EDirType::LEFT | (UINT)EDirType::DOWN, Vector2{ offset.x + dot,offset.y + dot }));

		//l|u

		rotat = math::Rotate(offset, 45);
		dot = math::Dot(rotat, offset);
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::LEFT | (UINT)EDirType::UP, Vector2{ offset.x,offset.y - dot }));

		//l|d
		mShooterSpawnPos.insert(std::make_pair((UINT)EDirType::LEFT | (UINT)EDirType::DOWN, Vector2{ offset.x,offset.y + dot }));
	}

	const Vector2& Chalice::GetShooterSpawnPos(int _count, EDirType ...)
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
}