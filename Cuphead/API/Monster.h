#pragma once
#include "Script.h"
namespace yeram_client
{
	class Monster :public Script
	{
	public:
		Monster();
		virtual ~Monster();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		virtual void Death(Collider* _other);
		virtual void Attack();
		virtual void Intro();
		void SetColCenter();
	
	protected:
		class MoveObject* mMoveObject;
		class Collider* mCol;
		class Animator* mAni;
		class Transform* mTransform;
		double mTime;
	};
}


