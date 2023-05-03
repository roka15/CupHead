#pragma once
#include "Monster.h"
namespace yeram_client
{
    class SlatPhase3 :
        public Monster
    {
    public:
		SlatPhase3();
		virtual ~SlatPhase3();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		virtual void Death(Collider* _other);
		virtual void Attack();
		virtual void Idle();
		virtual void Intro();
		virtual void TakeDamage(Collider* other);
		void ChangeDir();
		void SetCompleteEvent(); 
    private:
		class Rigidbody* mRigid;
		Vector2 mDir;
    };

}

