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
		virtual void Create(ESceneType _type) = 0;
		virtual void idleCompleteEvent() = 0;
		virtual void moveStartEvent() = 0;
		virtual void moveCompleteEvent() = 0;
		std::wstring GetName() { return mName; }
		void SetOwner(GameObject* _owner) { mOwner = _owner; }
		void SetSceneType(ESceneType _scenetype) { mSceneType = _scenetype; }
		void SetEndJumpInfo();
	protected:
		virtual void move();
		virtual void idle();
		virtual void shoot();
		virtual void duck();
		virtual void death();
		virtual bool jump_check(ECharacterState _befor_state);

		virtual void PositionUpdate();

		
	protected:
		std::wstring mName;
		GameObject* mOwner;
		ECharacterState mState;
		ESceneType mSceneType;
		EDirType mDirType;
		int mbJump;
		bool mbFlyMode;
		bool mbSit;
	
		//Rigidbody* mRigidBody;
	};
}


