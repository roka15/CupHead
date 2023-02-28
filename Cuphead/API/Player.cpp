#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "Resources.h"
#include "Image.h"
#include "Transform.h"
#include "Animator.h"
namespace yeram_client
{
	Player::Player():GameObject()
	{
	
	}
	Player::Player(ERenderType _type): GameObject(_type)
	{
		
	}
	Player::~Player()
	{
	}
	void Player::Initalize()
	{
		mRenderType = ERenderType::TransParentBlt;
<<<<<<< HEAD
		GameObject::Initalize();
		Image* mImage;//받아오기 시트
		Animator* animator = AddComponent<Animator>();
		//animator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8,16, Vector2::Zero, 0.1f);
		//animator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8,15, Vector2::Zero, 0.1f);
		animator->Play(L"FowardRun", true);

=======
		mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\chalice_idle_0001.bmp");
		Transform* tf = GetComponent<Transform>();
		tf->SetPos(Vector2(0, 0));
		tf->SetSize(Vector2(100, 100));
		GameObject::Initalize();
		AddComponent<Animator>();
>>>>>>> 85c5f662ccfb749ecd2ef53254f5677e801cc315
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
		
		
		
	}
	void Player::Release()
	{
		GameObject::Release();
	}
}