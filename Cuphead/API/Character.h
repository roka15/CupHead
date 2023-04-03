#pragma once
#include "CommonInclude.h"
#include "Enums.h"
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
		void ResetDash() { mbDash = false; }
	protected:
		virtual void move();
		virtual void idle();
		virtual void shoot();
		virtual void duck();
		virtual void death();
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
		int mJump;
		bool mbAir;
		bool mbAirStartFlag;
		bool mbSit;
		bool mbDash;
		float mDashVelocity;
		//Rigidbody* mRigidBody;
	};
}


