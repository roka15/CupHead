#pragma once
#include "Script.h"

namespace yeram_client
{
	class MoveObject : public Script
	{
	public:
		MoveObject();
		~MoveObject();
		void Create(std::wstring _ani_path,
					Vector2 _ani_offset, 
					float _ani_duration,
					bool _ani_alpha,
					const Vector2& _speed, 
					float _dspawn_time, 
					const Vector2& _diff);

		void Move(const Vector2& _other);
	private:
		bool CheckMapOut();
		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
	private:
		Vector2 mDiff;
		Vector2 mSpeed;
		Vector2 mDspawnTime;
		float mTime;
	};
}

