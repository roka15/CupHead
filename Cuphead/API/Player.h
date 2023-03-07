#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class Animator;
	class Player :public GameObject
	{
	public:
		enum class ECupheadState
		{
			Move,
			Shoot,
			Death,
			Idle,
		};

		Player();
		virtual ~Player();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		void ChangeCharacter(EPlayerType _type)
		{
			mPlayType = _type;
		}
	private:
		void move();
		void shoot();
		void death();
		void idle();

		void idleCompleteEvent();
	private:
		ECupheadState mState;
		EPlayerType mPlayType;
		Animator* mAnimator;
		/*float mTime;
		int midx;*/
	};
}


