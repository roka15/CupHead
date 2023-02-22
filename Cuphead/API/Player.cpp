#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "Resources.h"
#include "Image.h"
#include "Transform.h"
namespace yeram_client
{
	Player::Player():GameObject()
	{
		
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
		Transform* transform = GetComponent<Transform>();
		Vector2& pos = transform->GetPos();
		if (core::Input::GetKeyState(core::EKeyCode::A) == core::EKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::D) == core::EKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::W) == core::EKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKeyState(core::EKeyCode::S) == core::EKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* transform = GetComponent<Transform>();
		Vector2 pos = transform->GetPos();
		if (mImage != nullptr)
			BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHDC(), 0, 0, SRCCOPY);
	}
	void Player::Release()
	{
		GameObject::Release();
	}
}