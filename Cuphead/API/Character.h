#pragma once
#include "CommonInclude.h"
#include "Enums.h"
#include "Input.h"
#include "Engine.h"
namespace yeram_client
{
	class Rigidbody;
	class Animator;
	class GameObject;
	class Character
	{
	public:
		enum class ECharacterState
		{
			Move,
			Shoot,
			Death,
			Idle,
			Duck,
			Dash,
			Fix,
		};
		Character() {}
		virtual ~Character() {}
		virtual void Initialize()=0;
		virtual void Update()=0;
		virtual void Render(HDC hdc)=0;
		virtual void Release()=0;
	public:
		virtual void Create() = 0;
		virtual void idleCompleteEvent() = 0;
		virtual void moveStartEvent() = 0;
		virtual void moveCompleteEvent() = 0;
		std::wstring GetName() { return mName; }
		void SetOwner(GameObject* _owner) { mOwner = _owner; }
		void SetNextAniInfo();
		void SetAirMode(bool _flag);
		void ResetJump() { mJump = 0; }
		virtual void Parrying();
		void ResetDash();
		bool GetDash() { return mbDash; }
		bool GetJump() { return (mJump > 0); }
		void SetParry(bool _flag) { mbParry = _flag; }
		bool GetParry() { return mbParry; }
		void StopTransUpdate(bool _flag, EDirType _type);
		Vector2 GetMoveOffset() { return mMoveOffset; }
	protected:
		typedef core::Input::PushInfo PushInfo;

		virtual void move(const PushInfo& _push_info);
		virtual void idle(const PushInfo& _push_info);
		virtual void shoot(const PushInfo& _push_info);
		virtual void duck(const PushInfo& _push_info);
		virtual void death(const PushInfo& _push_info);
		virtual void fix(const PushInfo& _push_info);
		

		virtual void air_move();
		virtual void air_idle();
		virtual void air_shoot();
		virtual void air_death();

		virtual void PositionUpdate();
		virtual void DashPositionUpdate(EStateType _type);
		bool PriorityInput(core::EKeyCode _code1, core::EKeyCode _code2, core::EKeyCode& _result);
		EDirType GetDirType(const  core::EKeyCode& _code);
		const Vector2& GetShooterSpawnPos(int _count, EDirType ...);

		
	protected:
		std::wstring mName;
		GameObject* mOwner;
		ECharacterState mState;
		EDirType mDirType;
		EDirType mStopDir;
		int mJump;
		bool mbAir;
		bool mbAirStartFlag;
		bool mbSit;
		bool mbDash;
		bool mbParry;
		bool mbStopPositionUpdate;
		float mDashVelocity;
		float mDashTime;
		//Rigidbody* mRigidBody;

		Animator* mAni;
		GameObject* mHead;
		GameObject* mReg;
		GameObject* mShooter;
		std::map<UINT, Vector2> mShooterSpawnPos;

		Vector2 mMoveOffset;
	};
}


