#pragma once
#include "Script.h"
namespace yeram_client
{
	class WorldMapObject :public Script
	{
	public:
		WorldMapObject();
		virtual ~WorldMapObject();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetColliderInfo();
		const ESceneType& GetSceneType() { return mSceneType; }
		void SetSceneType(ESceneType _type) { mSceneType = _type; }
	private:
		class Collider* mCollider;
		class Animator* mAni;
		ESceneType mSceneType;
	};
}

