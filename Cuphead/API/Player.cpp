#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "GameObject.h"
#include "Resources.h"
#include "Image.h"
#include "Transform.h"
#include "WorldMapObject.h"
#include "TitleCardUI.h"
#include "Animator.h"
#include "Cuphead.h"
#include "MugMan.h"
#include "Chalice.h"
#include "Camera.h"

namespace yeram_client
{
	Player::Player() :Script()
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
		if (SceneManager::UseUI() == true)
			return;
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
		ESceneType type = SceneManager::GetActiveScene()->GetSceneType();
		switch (type)
		{
		case ESceneType::PlayMap:
			WorldMapObject* wm = other->GetOwner()->GetComponent<WorldMapObject>();
			if (wm != nullptr)
			{
				std::shared_ptr<GameObject> abutton = SceneManager::FindObject(L"mapAButton");
				abutton->SetActive(true);
				Transform* tf = abutton->GetComponent<Transform>();
				Vector2 player_pos = mOwner->GetComponent<Transform>()->GetPos();
				player_pos.x -= 40.0f;
				player_pos.y -= 150.0f;
				tf->SetPos(player_pos);
				tf->SetScale(Vector2{ 0.8f,0.8f });
				if (core::Input::GetKeyDown(core::EKeyCode::A))
				{

					ESceneType type = wm->GetSceneType();
					std::shared_ptr<GameObject> title_card = SceneManager::FindObject(L"title_card");
					title_card->SetActive(true);
					SceneManager::UseUI(true);
					std::shared_ptr<GameObject> title_text = title_card->FindChild(L"title_text");
					std::wstring name;
					std::wstring path;
					switch (type)
					{
					case ESceneType::NONE:
						//연결된 ncp 이벤트 수행
						return;
					case ESceneType::Tutorial:
						name = L"title_tutorial_txt";
						path = L"..\\Resources\\MapObject\\dlc\\title_card\\chalice.bmp";
						break;
					case ESceneType::SaltBakeryShop:
						name = L"title_salt_bakery_txt";
						path = L"..\\Resources\\MapObject\\dlc\\title_card\\title_card_chef_saltbaker_ko.bmp";
						break;
					}
					title_text->GetComponent<SpriteRenderer>()->SetImage(name, path);
					TitleCardUI* tcu = title_card->GetComponent<TitleCardUI>();
					tcu->GetEnterEvent() = std::bind([type]()->void
					{
						SceneManager::UseUI(false);
						SceneManager::SetLoadSceneMessage(std::bind([type]()->void {SceneManager::LoadScene(type); }));
					});
					tcu->GetEscEvent() = std::bind([title_card]()->void
					{
						SceneManager::UseUI(false);
						title_card->SetActive(false);
					});
				}
			}
			break;
		}

	}
	void Player::OnCollisionExit(Collider* other)
	{
		ESceneType type = SceneManager::GetActiveScene()->GetSceneType();
		switch (type)
		{
		case ESceneType::PlayMap:
			WorldMapObject* wm = other->GetOwner()->GetComponent<WorldMapObject>();
			if (wm != nullptr)
			{
				std::shared_ptr<GameObject> abutton = SceneManager::FindObject(L"mapAButton");
				abutton->SetActive(false);
			}
			break;
		}

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
		mCharacter->StopTransUpdate(_flag, EDirType::LEFT);
	}
	Vector2 Player::GetMoveOffset()
	{
		return mCharacter->GetMoveOffset();
	}
}