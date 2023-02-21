#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "Resources.h"
#include "Image.h"
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
		mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\chalice_idle_0002.bmp");
		GameObject::Initalize();
	}
	void Player::Update()
	{
		GameObject::Update();
		if (core::Input::GetKeyState(core::EKeyCode::A) == core::EKeyState::Pressed)
		{
			mPos.x -= 100.0f * Time::DeltaTime();
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
		if (mImage != nullptr)
			BitBlt(hdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHDC(), 0, 0, SRCCOPY);
	}
	void Player::Release()
	{
		GameObject::Release();
	}
}