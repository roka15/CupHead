#include "TitleCardUI.h"
#include "Input.h"
yeram_client::TitleCardUI::TitleCardUI() :Script()
{
	SetName(L"TitleCardUI");
}

yeram_client::TitleCardUI::~TitleCardUI()
{
}

void yeram_client::TitleCardUI::Initialize()
{
}

void yeram_client::TitleCardUI::Update()
{
	if (core::Input::GetKeyDown(core::EKeyCode::ENTER))
	{
		if (mEnterEvent != nullptr)
			mEnterEvent();
	}
	else if (core::Input::GetKeyDown(core::EKeyCode::ESC))
	{
		if (mEscEvent != nullptr)
			mEscEvent();
	}
}

void yeram_client::TitleCardUI::Render(HDC hdc)
{
}

void yeram_client::TitleCardUI::Release()
{
}

void yeram_client::TitleCardUI::OnCollisionEnter(Collider* other)
{
}

void yeram_client::TitleCardUI::OnCollisionStay(Collider* other)
{
}

void yeram_client::TitleCardUI::OnCollisionExit(Collider* other)
{
}
