#pragma once
#include "CommonInclude.h"
#include "Enums.h"
#include "Input.h"
namespace yeram_client
{
	class Rigidbody;
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
		};
		
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
		void SetParry(bool _flag) { mbParry = _flag; }
		bool GetParry() { return mbParry; }
		void StopTransUpdate(bool _flag, EDirType _type);
	protected:
		typedef core::Input::PushInfo PushInfo;

		virtual void move(const PushInfo& _push_info);
		virtual void idle(const PushInfo& _push_info);
		virtual void shoot(const PushInfo& _push_info);
		virtual void duck(const PushInfo& _push_info);
		virtual void death(const PushInfo& _push_info);
		virtual bool jump_check(ECharacterState _befor_state);

		virtual void air_move();
		virtual void air_idle();
		virtual void air_shoot();
		virtual void air_death();

		virtual void PositionUpdate();
		virtual void DashPositionUpdate(EStateType _type);

		
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
	};
}


