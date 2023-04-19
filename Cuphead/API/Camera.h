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
		static void FadeIn() { mType = ECameraEffectType::FADE_IN; }
		static void FadeOut() { mType = ECameraEffectType::FADE_OUT; }
		static void SetFadeImage(class Image* _image) { mCutton = _image; }
		static void SetFadeEndTime(float _time) { mEndTime = _time; mAlphaTime = 0.0f; }
		static void SetFadePos(const Vector2& _start, const Vector2& _end) { mAlphaStartPos = _start; mAlphaEndPos = _end; }
		static void InitFadeInfo(); 
		static void Clear();
		
	private:
		
	private: 
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;
		static bool mbHorizonMove;
		static bool mbVerticalMove;
		static float mAlphaTime;
		static float mEndTime;
		static float mCuttonAlpha;
		static class Image* mCutton;
		static Vector2 mAlphaStartPos;
		static Vector2 mAlphaEndPos;
		static ECameraEffectType mType;
	};

}

