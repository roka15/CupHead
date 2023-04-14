#pragma once
#include "Script.h"

namespace yeram_client
{
	class Transform;
	class MoveObject : public Script
	{
	public:
		MoveObject();
		~MoveObject();

		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		void CreateInfo(const Vector2& _speed,EDirType _dir);
		void CreateInfo(const Vector2& _speed, EDirType _dir, const Vector2& _kill_pos);
		void Move();
		const UINT& GetID() { return mID; }
	private:

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
	private:
		static UINT create_numbers;
		Vector2 mSpeed;
		Vector2 mEndPos;
		bool mbEndFlag;
		UINT mID;
		Transform* mTf;
		EDirType mDir;
	};
}

