#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class UI:public GameObject
	{
	public:
		struct UIEvent
		{

		};
		 
		UI();
		void SetImage(const std::wstring& _filename,const std::wstring& _path);
		void SetEvent(std::function<void()> _event_func);
	private:
		//실행할 함수 포인터
		UIEvent* mCurEvent;
		std::map<bool, UIEvent*> mEvents;
	};
}

