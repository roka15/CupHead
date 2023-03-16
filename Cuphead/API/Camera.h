#pragma once
#include "Engine.h"
namespace yeram_client
{
	class GameObject;
	class Camera
	{
	public:
		enum class ECameraEffectType
		{
			NONE,
			FADE_IN,
			FADE_OUT,
			SHAKE,
			END,
		};
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();
		static void SetTarget(GameObject* _target);
		static void SetCameraDistance(float _distance);
		//operator ±¸Çö.
		static Vector2 CaluatePos(Vector2 _pos) 
		{ 
			return _pos - mDistance; 
		}
		
		static void Clear();
	
	private:
		static bool CheckActive();
	private: 
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;
	};

}

