#pragma once
#include "HomingBullet.h"
namespace yeram_client
{
	class PepperBullet :
		public HomingBullet
	{
	public:
		PepperBullet();
		virtual ~PepperBullet();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		virtual void SetColInfo(std::wstring _ani_name);
		virtual void Shoot();
		virtual void Death(Collider* _other);
		virtual void DeathPlay();
	private:
		std::vector<std::wstring> mAnis;
	
	};
}


