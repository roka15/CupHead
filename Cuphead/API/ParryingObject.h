#pragma once
#include "Script.h"
namespace yeram_client
{
	//parrying test object
	class ParryingObject :public Script
	{
	public:
		ParryingObject();
		virtual ~ParryingObject();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		bool mbActive;
	};
}


