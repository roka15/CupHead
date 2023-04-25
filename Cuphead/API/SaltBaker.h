#pragma once
#include "Boss.h"

namespace yeram_client
{
	class SaltBaker :public Boss
	{
	public:
		SaltBaker();
		virtual ~SaltBaker();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	private:
		void RegisterPattern1();
		void RegisterPattern2();
		void RegisterPattern3();
	private:
		EGameObjectType mobjType;
	};
}


