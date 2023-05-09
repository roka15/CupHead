#pragma once
#include "ZigZagBullet.h"
namespace yeram_client
{
    class CookieBullet :public ZigZagBullet
    {
    public:
        CookieBullet();
        virtual ~CookieBullet();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
	

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		virtual void Shoot()override;
		virtual void Death(Collider* _other)override;
		virtual void DeathPlay()override;
		virtual void SetColInfo(std::wstring _ani_name)override;

		virtual void SetAnimation(std::wstring _name, bool _flag)override;
		virtual void NextInfoSetting()override;
	protected:
		void SetCompleteEvent(std::wstring _name);
    private:

    };
}

