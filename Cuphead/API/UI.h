#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class UI:public GameObject
	{
	public:
		enum class EUIState
		{
			None,
			Enter,
			Exit,
			Click,
			MAX
		};
		typedef  std::function<void()> UIFunc;
		struct UIEvent
		{
			UIFunc EnterEvent; //커서 활성화
			UIFunc ExitEvent;  //커서 비활성화
			UIFunc ClickEvent; //클릭
		};
		UI();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Release();
		void execute(EUIState _state);

		void SetImage(const std::wstring& _filename,const std::wstring& _path);
		void SetEnterEvent(UIFunc _func);
		void SetExitEvent(UIFunc _func);
		void SetClickEvent(UIFunc _func);
	private:
		UIFunc& GetEnterEvent(std::wstring _name);
		UIFunc& GetExitEvent(std::wstring _name);
		UIFunc& GetClickEvent(std::wstring _name);
	private:
		EUIState mState;
		UIEvent mEvents;
	};
}

