#pragma once
#include "CommonInclude.h"
namespace core
{
	class Loading
	{
	public:
		 static void Initialize();
	     static DWORD WINAPI LoadingFunc(PVOID _Param);
		 static void Release();
		 static void WakeUpEvent() { SetEvent(mEvent); }
		 static bool ActiveLoading() { return mbLoading; }
	private:
		static bool mbStop;
		static CRITICAL_SECTION mCs;
		static HANDLE mEvent;
		static bool mbLoading;
	};
}


