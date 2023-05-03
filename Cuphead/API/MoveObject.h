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
		void CreateInfo(const Vector2& _speed, EDirType _dir, const Vector2& _kill_pos,bool _despawn=false, bool _outcheck=false);
		void CreateInfo(const Vector2& _speed,const Vector2& _dir, bool _despawn = false, bool _outcheck = false);
		void CreateInfo(const Vector2& _speed, const Vector2& _dir, const Vector2& _kill_pos, bool _despawn = false, bool _outcheck = false);
		void WaveMove();
		void Move();
		bool IsArrive() { return mbArrive; }
		void SetWave(bool _flag) { mbWave = _flag; }
		const UINT& GetID() { return mID; }
		void SetArriveEvent(std::function<void()> _func) { mArriveEvent = _func; }
		void SetEndPos();
		void SetYFlag(bool _flag) { mbYFlag = _flag; }
		
	private:

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
	private:
		static UINT create_numbers;
		Vector2 mSpeed;
		Vector2 mEndPos;
		Vector2 mStartPos;
		Vector2 mDirpos;
		bool mbWave;
		bool mbEndFlag;
		bool mbOutCheck;
		bool mbDespawn;
		bool mbArrive;
		UINT mID;
		Transform* mTf;
		EDirType mDir;
		std::function<void()> mArriveEvent;
		bool mbYFlag;
	};
}

