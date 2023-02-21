#pragma once
#include "Engine.h"
namespace yeram_client
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND _hWnd);
		void Run();

		void Update();
		void Render();

		void Release();
		
		HWND GetHandle();
		HDC GetHDC();
	private:
		HWND mHwnd;
		HDC mhdc;

		//¹é¹öÆÛ
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		UINT mWidth;
		UINT mHeight;
	};
}

