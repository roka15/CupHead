#pragma once
#include "Bullet.h"
namespace yeram_client
{
    class LemonBullet :public Bullet
    {
    public:
        LemonBullet();
        virtual ~LemonBullet();
        virtual void Initialize()override;
        virtual void Update()override;
        virtual void Render(HDC hdc)override;
        virtual void Release()override;

        virtual void OnCollisionEnter(class Collider* other)override;
        virtual void OnCollisionStay(class Collider* other)override;
        virtual void OnCollisionExit(class Collider* other)override;
        virtual void Shoot();
        virtual void Death(Collider* _other);
        virtual void DeathPlay()override;
        void CreateInfo(const Vector2& _dirpos, bool _dir);
        void NextInfo();
    private:
        std::queue<Vector2> mDir;
        std::queue<Vector2> mArrivePos;
        Vector2 mSpeed;
    };
}


