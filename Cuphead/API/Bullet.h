#pragma once
#include "Script.h"

namespace yeram_client
{
	class Transform;
	class Animator;
	class Collider;
	class MoveObject;
	class Bullet : public Script
	{
	
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
		virtual void Shoot();
		virtual void Death(Collider* _other);

		void SetParry(bool _flag) { mbParry = _flag; }
		void SetID(const UINT& _id) { mID = _id; }
		void SetScale(const Vector2& _scale);
		void SetPos(const Vector2& _pos); 
		void CreateAnimation(std::wstring _path, Vector2 _offset, float _duration, bool _alpha = false);
		void SetAnimation(std::wstring _name, bool _flag);
		void SetAnimation(std::wstring _name,bool _flag,EDirType _dir);
	
		void SetColInfo(std::wstring _ani_name);
		void SetShotType(EShotBulletType _type) { mShotType = _type; }
		
		virtual void CreateInfo(const Vector2& _speed,const Vector2& _startpos, const Vector2& _endpos);
		virtual void CreateInfo(const Vector2& _speed, const Vector2& _startpos, const Vector2& _dirpos,bool _dir);
		bool MapOutCheck();
		const UINT& GetID() { return mID; }
		const bool& GetParry() { return mbParry; }
	protected:
		UINT mID;
		UINT mDamage;
		EShotBulletType mShotType;
		bool mbParry;
		MoveObject* mMoveObject;
		Collider* mColider;
		Transform* mTransform;
		Animator* mAni;
	};
}

