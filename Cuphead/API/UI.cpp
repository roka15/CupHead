#include "UI.h"
#include "SpriteRenderer.h"
#include "UIManager.h"
namespace yeram_client
{
	UI::UI() :mState(EUIState::None)
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
	void UI::execute(EUIState _state)
	{
		switch (_state)
		{
		case EUIState::Enter:
			mEvents.EnterEvent();
			break;
		case EUIState::Exit:
			mEvents.ExitEvent();
			break;
		case EUIState::Click:
			mEvents.ClickEvent();
			break;
		}
	}
	void UI::SetImage(const std::wstring& _filename, const std::wstring& _path)
	{
		SpriteRenderer* render = GetComponent<SpriteRenderer>();
		render->SetImage(_filename, _path);
	}
	void UI::SetEnterEvent(UIFunc _func)
	{
	}
	void UI::SetExitEvent(UIFunc _func)
	{
	}
	void UI::SetClickEvent(UIFunc _func)
	{
	}
	UI::UIFunc& UI::GetEnterEvent(std::wstring _name)
	{
		return mEvents.EnterEvent;
	}
	UI::UIFunc& UI::GetExitEvent(std::wstring _name)
	{
		return mEvents.ExitEvent;
	}
	UI::UIFunc& UI::GetClickEvent(std::wstring _name)
	{
		return mEvents.ClickEvent;
	}
}

