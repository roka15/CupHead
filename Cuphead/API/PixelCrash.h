#pragma once
#include "Script.h"
namespace yeram_client
{
	class PixelCrash :public Script
	{
	public:
		PixelCrash();
		virtual ~PixelCrash();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		void SetImage(std::wstring _name, std::wstring _path);
		void SetTarget(std::shared_ptr<GameObject>& _target) { mTarget = _target; }
	private:
		class SpriteRenderer* mSprite;
		class Collider* mCollider;
		class std::shared_ptr<GameObject> mTarget;
	};
}


