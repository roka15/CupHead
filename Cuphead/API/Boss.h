#pragma once
#include "Script.h"
namespace yeram_client
{
	class Boss :public Script
	{
	public:
		Boss();
		virtual ~Boss();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	protected:
		class Transform* mTransform;
		class MoveObject* mMoveObject;
		class Animator* mAni;
		class Collider* mCol;
	};
}


