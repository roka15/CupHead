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
	void UI::InitComponent()
	{
		std::vector<Component*> comps = GetComponents();

		for (int i = 0; i < comps.size(); i++)
		{
			if (comps[i] == nullptr)
				continue;
			if (dynamic_cast<Transform*>(comps[i]) != nullptr)
				continue;
			if (dynamic_cast<SpriteRenderer*>(comps[i]) != nullptr)
				continue;
			comps[i]->Release();
			delete comps[i];
			comps[i] = nullptr;
		}
	}
}

