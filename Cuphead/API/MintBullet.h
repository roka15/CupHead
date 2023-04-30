#pragma once
#include "ZigZagBullet.h"
namespace yeram_client
{
	class MintBullet :
		public ZigZagBullet
	{
	public:
		MintBullet();
		virtual ~MintBullet();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		virtual void Shoot()override;
		virtual void Death(Collider* _other)override;
	private:
	};

}

