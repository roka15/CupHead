#include "Player.h"
#include "Time.h"
#include "Input.h"
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
	Player::Player() :GameObject()
	{
		mAnimator = AddComponent<Animator>();
	}

	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		for (auto c : mCharacters)
		{
			if (c.second == nullptr)
				continue;
			c.second->Initialize();
		}
	}
	void Player::Update()
	{
		GameObject::Update();
		mCharacter->Update();
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Player::Release()
	{
		for (auto c : mCharacters)
		{
			if (c.second == nullptr)
				continue;
			c.second->Release();
			delete c.second;
			c.second = nullptr;
		}
		GameObject::Release();
	}
	void Player::CreateCharacter(ESceneType _scenetype,EPlayerType _type)
	{
		Character* c = nullptr;
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
			c = new MugMan();
			mCharacters.insert(std::make_pair(EPlayerType::MugMan, c));
			break;
		}
		c->SetOwner(this);
		c->Create(_scenetype);
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
}