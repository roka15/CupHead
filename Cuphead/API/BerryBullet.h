#pragma once
#include "Bullet.h"
namespace yeram_client
{
    class BerryBullet :
        public Bullet
    {
    public:
        BerryBullet();
        virtual ~BerryBullet();
        virtual void Initialize()override;
        virtual void Update()override;
        virtual void Render(HDC hdc)override;
        virtual void Release()override;

        virtual void OnCollisionEnter(class Collider* other)override;
        virtual void OnCollisionStay(class Collider* other)override;
        virtual void OnCollisionExit(class Collider* other)override;
        virtual void Shoot();
        virtual void Death(Collider* _other);

        void CreateInfo(const Vector2& _speed);
    private:
        Vector2 mDistance;
        const Vector2 mRange;
    };
}

