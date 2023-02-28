#pragma once
#include "CommonInclude.h"
namespace core
{
	enum class EKeyCode
	{
		A,S,D,W,
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
	private:
		static std::vector<Key> mKeys;
	};
}

