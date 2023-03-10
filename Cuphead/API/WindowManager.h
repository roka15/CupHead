#pragma once
#include "Engine.h"
namespace yeram_client
{
	class GameObject;
	class WindowManager
	{
	public:
		static std::pair<EWindowType,GameObject*> FindUIGroup(EWindowType _group_key);
		static void ActiveWindow(UINT _group_key);
		static EWindowType ActiveType();
		//포커스 다운 함수
		static void CursorDownEvent();
		//포커스 업 함수
		static void CursorUpEvent();
		//클릭 함수
		static void CursorClickEvent();
		static void InActiveWindow();
		static void Initialize();
		static void Release();
		
	private:
		WindowManager();
		~WindowManager();
		static void CreateMainMenuWindow();
		
	private:
		static std::map<EWindowType,GameObject*> mRegisterWindows;
		static std::stack<std::pair<EWindowType,GameObject*>> mActiveWindow;
		static int mCursorIndex;
	};

}


