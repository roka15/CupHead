#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "GameObject.h"
#include "Resources.h"
#include "Image.h"
#include "Transform.h"
#include "Animator.h"
#include "Cuphead.h"
#include "MugMan.h"
#include "Chalice.h"
#include "Camera.h"

namespace yeram_client
{
	Player::Player():Script()
	{	
		SetName(L"Player");
	}

	Player::~Player()
	{ 
	}
	void Player::Initialize()
	{
		mAnimator = GetOwner()->AddComponent<Animator>();
		Collider* col = GetOwner()->AddComponent<Collider>();
		Rigidbody* rig = GetOwner()->AddComponent<Rigidbody>();
		rig->SetMass(1.0f);
		for (auto c : mCharacters)
		{
			if (c.second == nullptr)
				continue;
			c.second->Initialize();
		}
	}
	void Player::Update()
	{
		mCharacter->Update();
	}
	void Player::Render(HDC hdc)
	{
	}
	void Player::Release()
	{
		for (auto& c : mCharacters)
		{
			if (c.second == nullptr)
				continue;
			c.second->Release();
			delete c.second;
			c.second = nullptr;
		}
	}
	void Player::CreateCharacter(EPlayerType _type)
	{
		Character* c = nullptr;
		if (mCharacters.find(_type) != mCharacters.end())
			return;
		switch (_type)
		{
		case EPlayerType::Cuphead:
			c = new Cuphead();
			mCharacters.insert(std::make_pair(EPlayerType::Cuphead, c));
			break;
		case EPlayerType::MsChalice:
			
			c = new Chalice();
			mCharacters.insert(std::make_pair(EPlayerType::MsChalice, c));
			break;
		case EPlayerType::MugMan:
			/*c = new MugMan();
			mCharacters.insert(std::make_pair(EPlayerType::MugMan, c));*/
			break;
		}
		c->SetOwner(GetOwner());
		c->Create();
		mCharacter = c;
	}
	void Player::ChangeCharacter(EPlayerType _type)
	{
		auto itr = mCharacters.find(_type);
		if (itr != mCharacters.end())
		{
			mCharacter = itr->second;
		}
		mCharacter->Initialize();
	}
	void Player::OnCollisionEnter(Collider* other)
	{
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}
	void Player::Parry_Check()
	{
		if (mCharacter->GetDash() == true)
		{
			mCharacter->Parrying();
		}
	}
	void Player::Stop_PositionUpdate(bool _flag, EDirType _type)
	{
		mCharacter->StopTransUpdate(_flag,EDirType::LEFT);
	}
	Vector2 Player::GetMoveOffset()
	{
		return mCharacter->GetMoveOffset();
	}
}