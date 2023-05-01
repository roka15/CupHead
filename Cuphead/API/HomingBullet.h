#pragma once
#include "Bullet.h"
namespace yeram_client
{
    class HomingBullet :
        public Bullet
    {
    public:
        HomingBullet();
        virtual ~HomingBullet();
        virtual void Initialize()override;
        virtual void Update()override;
        virtual void Render(HDC hdc)override;
        virtual void Release()override;

        virtual void OnCollisionEnter(class Collider* other)override;
        virtual void OnCollisionStay(class Collider* other)override;
        virtual void OnCollisionExit(class Collider* other)override;
        virtual void Shoot();
        virtual void SetColInfo(std::wstring _ani_name);
        virtual void Death(Collider* _other);
        void GetTargetPos(Vector2 _target); 
    private:
        Vector2 mSpeed;
    };
}


