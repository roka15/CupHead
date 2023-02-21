#include "Player.h"
#include "Time.h"
#include "Input.h"
namespace yeram_client
{
	Player::Player()
	{
		mPos.x = 100;
		mPos.y = 100;
	}
	Player::~Player()
	{
	}
	void Player::Initalize()
	{
		GameObject::Initalize();
	}
	void Player::Update()
	{
		GameObject::Update();
		if (core::Input::GetKeyState(core::EKeyCode::A)== core::EKeyState::Pressed)
		{
			mPos.x -= 100.0f*Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::D) == core::EKeyState::Pressed)
		{
			mPos.x += 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::W) == core::EKeyState::Pressed)
		{
			mPos.y -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::S) == core::EKeyState::Pressed)
		{
			mPos.y += 100.0f * Time::DeltaTime();
		}
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		HBRUSH OldBrush;
		HPEN OldPen;
		//브러쉬 생성
		//브러쉬 선택
		//렌더
		//브러쉬 원래대로 복구
		//만든 브러쉬 delete

		OldBrush = (HBRUSH)SelectObject(hdc, brush);
		OldPen = (HPEN)SelectObject(hdc, pen);
		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);
		SelectObject(hdc, OldBrush);
		Ellipse(hdc, 300, 300, 400, 400);
		SelectObject(hdc, OldPen);
		DeleteObject(brush);
		DeleteObject(pen);
	}
	void Player::Release()
	{
		GameObject::Release();
	}
}