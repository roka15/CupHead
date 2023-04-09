#pragma once
#include "Script.h"
namespace yeram_client
{
	class Animator;
	class Transform;
	class OriginalImagePos :public Script
	{
	public:
		OriginalImagePos();
		virtual ~OriginalImagePos();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	private:
		Animator* mAni;
		Transform* mTf;
		Vector2 mSpriteSize;
		Vector2 mOffset;
		double mTime;
		int index = 0;
	};
}

