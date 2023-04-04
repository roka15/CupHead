#pragma once
#include "Script.h"
#include "BulletManager.h"
namespace yeram_client
{
	class Transform;
	class Animator;
	class Collider;
	class Bullet : public Script
	{
	private:
		typedef BulletManager::EShotBulletType ShotType;
	public:
		Bullet();
		virtual ~Bullet();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		void Reset();

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		void SetParry(bool _flag) { mbParry = _flag; }
		void SetID(const UINT& _id) { mID = _id; }
		void SetEndPos(const Vector2& _pos) { mEndPos = _pos; }
		void SetScale(const Vector2& _scale);
		void SetPos(const Vector2& _pos); 
		void SetAnimation(std::wstring _path, Vector2 _offset, float _duration, bool _alpha = false);
		void SetShotType(ShotType _type) { mShotType = _type; }
		
		
		const UINT& GetID() { return mID; }
		const bool& GetParry() { return mbParry; }
	private:
		UINT mID;
		float mDeSpawnDistance;
		Vector2 mStartPos; //spawn À§Ä¡. 
		Vector2 mEndPos;
		Vector2 mSpeed;
		EDirType mDirType;
		ShotType mShotType;
		bool mbParry;
		Collider* mColider;
		Transform* mTransform;
		Animator* mAni;
	};
}

