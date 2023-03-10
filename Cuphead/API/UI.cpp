#include "UI.h"
#include "SpriteRenderer.h"
//#include "WindowManager.h"

namespace yeram_client
{
	UI::UI() 
	{
		AddComponent<SpriteRenderer>();
	}
	void UI::Initialize()
	{
		GameObject::Initialize();
	}
	void UI::Update()
	{
		GameObject::Update();
	}
	void UI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void UI::Release()
	{
		GameObject::Release();
	}
	void UI::execute()
	{
		//mClickEvents();
	}
	void UI::SetImage(const std::wstring& _filename, const std::wstring& _path)
	{
		SpriteRenderer* render = GetComponent<SpriteRenderer>();
		render->SetImage(_filename, _path);
	}
	void UI::SetClickEvent(UIFunc _func)
	{
		mClickEvents = std::move(_func);
	}
}

