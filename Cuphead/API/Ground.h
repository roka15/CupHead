#pragma once

#include "Script.h"
namespace yeram_client
{
	class Ground:public Script
	{
	public:
		Ground();
		virtual ~Ground();
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		
	private:
		class Collider* mCollider;
	};

}


