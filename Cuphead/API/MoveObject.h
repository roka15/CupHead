#pragma once
#include "Script.h"

namespace yeram_client
{
	class MoveObject : public Script
	{
	public:
		MoveObject();
		~MoveObject();

		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		void CreateInfo(
			const Vector2& _speed,
			float _dspawn_time,
			const Vector2& _diff,
			const byte _outdir,
			const Vector2& _dir,
			const bool& _regular);

		void Move();
		const Vector2& GetDiff() { return mDiff; }
		const bool& GetRegular() { return mbRegular; }
		const Vector2& GetStartPos() { return mStartPos; }
		const byte GetOutCheckDir() { return mOutDirbit; }
		const UINT& GetID() { return mID; }
	private:

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
	private:
		static UINT create_numbers;
		Vector2 mStartPos;
		Vector2 mDiff;
		Vector2 mSpeed;
		Vector2 mDir;
		float mDspawnTime;
		float mTime;
		byte mOutDirbit;
		bool mbRegular;
		UINT mID;
	};
}

