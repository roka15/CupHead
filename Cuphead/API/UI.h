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
		//������ �Լ� ������
		UIEvent* mCurEvent;
		std::map<bool, UIEvent*> mEvents;
	};
}

