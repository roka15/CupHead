#pragma once
#include "CommonInclude.h"

namespace core
{
	enum class EKeyCode
	{
		A, S, D, W, K,Z,
		Left,
		Right,
		Up,
		Down,
		MouseLeft,
		MouseRight,
		SPACE,
		SHIFT,
		MAX
	};

	enum class EKeyState
	{
		NONE,
		Down,
		Pressed,
		Up,
		Max,
	};
	class Input
	{
	public:
		struct Key
		{
			//키
			EKeyCode keycode;
			EKeyState state;
			//키 상태
			bool bPressed;
		};
		struct PushInfo
		{
			EKeyCode mkeycode;
			float mTime;
		};
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();
		static EKeyCode GetBeforKeyCode() { return mBeforPush.mkeycode; }
		
		inline static EKeyState GetKeyState(EKeyCode _keycode)
		{
			return mKeys[(UINT)_keycode].state;
		}
		static __forceinline bool GetKey(EKeyCode _keycode)
		{
			if (mKeys[(UINT)_keycode].state == EKeyState::Pressed)
			{
				return true;
			}
			else return false;
		}
		static __forceinline bool GetKeyDown(EKeyCode _keycode)
		{
			if (mKeys[(UINT)_keycode].state == EKeyState::Down)
			{
 				if (mBeforPush.mTime == 0.0f || mBeforPush.mkeycode !=_keycode)
				{
					PushInfo info;
					info.mkeycode = _keycode;
					info.mTime = mTime;
					mBeforPush = info;
				}
				return true;
			}
			else return false;
		}
		static __forceinline bool GetKeyUp(EKeyCode _keycode)
		{
			if (mKeys[(UINT)_keycode].state == EKeyState::Up)
			{
				return true;
			}
			else return false;
		}
		static __forceinline bool GetKeyDoubleDown(EKeyCode _keycode, float _second)
		{
			float befor_time = mBeforPush.mTime;
		
			if (mBeforPush.mkeycode == _keycode)
			{
				float diff = mTime - befor_time;
				mBeforPush.mTime = 0.0f;
				if (mTime == befor_time)
					return false;
				else if (befor_time == 0.0f)
					return false;
				if (diff <= _second)
				{
					return true;
				}
			}
			return false;
		}
	private:
		static std::vector<Key> mKeys;
		static PushInfo mBeforPush;
		static float mTime;
	};
}

