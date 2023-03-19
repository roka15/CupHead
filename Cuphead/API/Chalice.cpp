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
		Collider* col = mOwner->GetComponent<Collider>();
		col->SetCenter(Vector2(-75.0f, -155.0f));
		col->SetSize(Vector2(150.0f, 160.0f));

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
			case ECharacterState::Duck:
				duck();
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
		std::wstring ani_name;
		Animator* ani = mOwner->GetComponent<Animator>();
		if (mbJump == 0)
		{
			if (core::Input::GetKeyUp(core::EKeyCode::A)
				|| core::Input::GetKeyUp(core::EKeyCode::D)
				|| core::Input::GetKeyUp(core::EKeyCode::W)
				|| core::Input::GetKeyUp(core::EKeyCode::SPACE))
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


				if (core::Input::GetKey(core::EKeyCode::A)
					|| core::Input::GetKey(core::EKeyCode::D)
					|| core::Input::GetKey(core::EKeyCode::W)
					|| core::Input::GetKeyDown(core::EKeyCode::S)
					)
				{
					if (mbSit == false && mbJump == 0)
					{
						if (core::Input::GetKeyDown(core::EKeyCode::S))
						{
							mbSit = true;
							switch (mDirType)
							{
							case EDirType::LEFT:
								ani->Play(L"DuckLeft", false);
								break;
							case EDirType::RIGHT:
								ani->Play(L"DuckRight", false);
								break;
							}

							mState = ECharacterState::Duck;
							return;
						}
					}
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
					if (ani_name.size() > 0)
					{
						ani->Play(ani_name, true);
					}
					mState = ECharacterState::Move;
				}
			}


			if (core::Input::GetKeyDown(core::EKeyCode::A)
				|| core::Input::GetKeyDown(core::EKeyCode::D)
				|| core::Input::GetKeyDown(core::EKeyCode::W)
				|| core::Input::GetKeyDown(core::EKeyCode::S)
				)
			{
				if (mbSit == false && mbJump == 0)
				{
					if (core::Input::GetKeyDown(core::EKeyCode::S))
					{
						mbSit = true;
						switch (mDirType)
						{
						case EDirType::LEFT:
							ani->Play(L"DuckLeft", false);
							break;
						case EDirType::RIGHT:
							ani->Play(L"DuckRight", false);
							break;
						}

						mState = ECharacterState::Duck;
						return;
					}
				}

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
		//rigid 이동
		//trans 이동

		jump_check(mState);

		PositionUpdate();
	}

	void Chalice::idle()
	{
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;

		bool flag = jump_check(mState);

		if (mbJump >= 1)
			return;

		if (core::Input::GetKeyDown(core::EKeyCode::A)
			|| core::Input::GetKeyDown(core::EKeyCode::D)
			|| core::Input::GetKeyDown(core::EKeyCode::W)
			|| core::Input::GetKeyDown(core::EKeyCode::S)
			)
		{
			if (mbSit == false && mbJump == 0)
			{
				if (core::Input::GetKeyDown(core::EKeyCode::S))
				{
					mbSit = true;
					switch (mDirType)
					{
					case EDirType::LEFT:
						ani->Play(L"DuckLeft", false);
						break;
					case EDirType::RIGHT:
						ani->Play(L"DuckRight", false);
						break;
					}

					mState = ECharacterState::Duck;
					return;
				}
			}

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
					switch (mDirType)
					{
					case EDirType::LEFT:
						ani->Play(L"Stand UpLeft", false);
						break;
					case EDirType::RIGHT:
						ani->Play(L"Stand UpRight", false);
						break;
					}

				}
			}
		}
		if (core::Input::GetKeyDown(core::EKeyCode::A))
		{
			mDirType = EDirType::LEFT;
			ani->Play(L"DuckIdleLeft", false);
			//ani left duck
		}
		if (core::Input::GetKeyDown(core::EKeyCode::D))
		{
			mDirType = EDirType::RIGHT;
			ani->Play(L"DuckIdleRight", false);
			//ani right duck
		}
	}

	bool Chalice::jump_check(ECharacterState _befor_state)
	{
		mState = _befor_state;
		Animator* ani = mOwner->GetComponent<Animator>();
		std::wstring ani_name;
		if (core::Input::GetKeyDown(core::EKeyCode::SPACE))
		{
			mbJump++;
			if (mbJump > 2)
			{
				mbJump = 2;
				return false;
			}
			if (core::Input::GetKeyDoubleDown(core::EKeyCode::SPACE, 2.0f)
				&& mbJump == 2)
			{
				if (mDirType == EDirType::LEFT)
					ani_name = L"Double JumpLeft";
				else
					ani_name = L"Double JumpRight";
			}
			else if (core::Input::GetKeyDown(core::EKeyCode::SPACE))
			{
				if (mDirType == EDirType::LEFT)
					ani_name = L"JumpLeft";
				else
					ani_name = L"JumpRight";
			}
			if (ani_name.size() > 0)
			{
				ani->Play(ani_name, true);
				mState = ECharacterState::Move;
				Rigidbody* rigid = mOwner->GetComponent<Rigidbody>();
				Vector2 velocity = rigid->GetVelocity();
				velocity.y -= 700.0f;

				rigid->SetVelocity(velocity);
				rigid->SetGround(false);
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
			offset.x -= 400.0f * Time::DeltaTime();
			mDirType = EDirType::LEFT;
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			//rig->AddForce(Vector2(+200.0f, 0.0f));
			offset.x += 400.0f * Time::DeltaTime();
			mDirType = EDirType::RIGHT;
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

		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Double Jump\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Double Jump\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Fall\\Left", Vector2::Zero, 0.08f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Jump\\Fall\\Right", Vector2::Zero, 0.08f, true);


		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\DuckIdle\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\DuckIdle\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Duck\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Duck\\Right", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Stand Up\\Left", Vector2::Zero, 0.05f, true);
		ani->CreateAnimations(L"..\\Resources\\Chalice\\MSChalice\\Duck\\Stand Up\\Right", Vector2::Zero, 0.05f, true);

		ani->GetCompleteEvent(L"DuckLeft") = std::bind([this, ani]()->void
		{
			switch (mDirType)
			{
			case EDirType::LEFT:
				ani->Play(L"DuckIdleLeft", true);
				break;
			case EDirType::RIGHT:
				ani->Play(L"DuckIdleRight", true);
				break;
			}
		});
		ani->GetCompleteEvent(L"DuckRight") = std::bind([this, ani]()->void
		{
			switch (mDirType)
			{
			case EDirType::LEFT:
				ani->Play(L"DuckIdleLeft", true);
				break;
			case EDirType::RIGHT:
				ani->Play(L"DuckIdleRight", true);
				break;
			}
		});
		ani->GetCompleteEvent(L"Stand UpLeft") = std::bind([this]()->void {SetEndJumpInfo(); });
		ani->GetCompleteEvent(L"Stand UpRight") = std::bind([this]()->void {SetEndJumpInfo(); });
	}

	void Chalice::MoveDown()
	{
		if (mbFlyMode == false)
		{
			mState = ECharacterState::Idle;
			mbSit = true;
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
