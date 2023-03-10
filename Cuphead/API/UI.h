#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class UI:public GameObject
	{
	public:
		
		typedef  std::function<void(UINT)> UIFunc;
	
		UI();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Release();
		void execute();

		void SetImage(const std::wstring& _filename,const std::wstring& _path);
		void SetClickEvent(UIFunc _func);
	
	private:
		UIFunc mClickEvents;
	};
}

