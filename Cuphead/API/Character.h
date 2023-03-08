#pragma once
#include "CommonInclude.h"
#include "Enums.h"
namespace yeram_client
{
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
		};
		virtual void Initialize()=0;
		virtual void Update()=0;
		virtual void Render(HDC hdc)=0;
		virtual void Release()=0;

		virtual void move();
		virtual void idle();
		virtual void shoot();
		virtual void death();

		virtual void Create(ESceneType _type)=0;
		virtual void idleCompleteEvent() = 0;
		virtual void moveStartEvent() = 0;
		virtual void moveCompleteEvent() = 0;
		std::wstring GetName() { return mName; }
		void SetOwner(GameObject* _owner) { mOwner = _owner; }
	protected:
		std::wstring mName;
		GameObject* mOwner;
		ECharacterState mState;
		ESceneType mSceneType;
	};
}


