#pragma once
#include "Engine.h"
namespace yeram_client
{
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();
		static void SetTarger(GameObject* _target) { mTarget = _target; }
		//operator ±¸Çö.
		static Vector2& CaluatePos(Vector2 _pos) { return _pos - mDistance; }
		static void Clear();
	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

	};

}

