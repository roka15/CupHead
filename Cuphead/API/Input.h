#pragma once
#include "CommonInclude.h"
namespace core
{
	enum class EKeyCode
	{
		A,S,D,W,K,
		Left,
		Right,
		Up,
		Down,
		MouseLeft,
		MouseRight,
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
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();
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
	private:
		static std::vector<Key> mKeys;
	};
}

