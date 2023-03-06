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
		Player(ERenderType _type);
		virtual ~Player();
		virtual void Initalize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
	private:
		void move();
		void shoot();
		void death();
		void idle();
	private:
		ECupheadState mState;
		Animator* mAnimator;
		/*float mTime;
		int midx;*/
	};
}


