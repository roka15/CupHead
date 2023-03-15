#pragma once
#include "Script.h"

namespace yeram_client
{
	class MoveObject : public Script
	{
	public:
		MoveObject();
		~MoveObject();
		void SetInfo(const Vector2& _distance, const Vector2& _speed, float _time);
		void Move(const Vector2& _other);
	private:
		void CheckMapOut();
	private:
		Vector2 mDistance;
		Vector2 mSpeed;
		float mTime;
	};
}

