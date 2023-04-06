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
		//operator ����.
		static Vector2 CaluatePos(Vector2 _pos) 
		{ 
			return _pos - mDistance; 
		}
		static void SetHorizontalMove(bool _flag) { mbHorizonMove = _flag; }
		static void SetVerticalMove(bool _flag) { mbVerticalMove = _flag; }
		static bool GetHorizontalMove() { return mbHorizonMove; }
		static bool GetVerticalMove() { return mbVerticalMove; }
		static bool UseTarget() { return mTarget != nullptr; }
		static void Clear();
	
	private:
		static bool CheckActive();
	private: 
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;
		static bool mbHorizonMove;
		static bool mbVerticalMove;
	};

}

