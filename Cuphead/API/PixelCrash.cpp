#include "PixelCrash.h"
#include "Player.h"
#include "Character.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"
#include "Image.h"
yeram_client::PixelCrash::PixelCrash() :Script()
{
	SetName(L"PixelCrash");
	mSprite = nullptr;
	mCollider = nullptr;
	mTarget = nullptr;
}

yeram_client::PixelCrash::~PixelCrash()
{
}

void yeram_client::PixelCrash::Initialize()
{
	Script::Initialize();
	mSprite = mOwner->AddComponent<SpriteRenderer>();
	mCollider = mOwner->AddComponent<Collider>();
	mSprite->Initialize();
	mCollider->Initialize();
}

void yeram_client::PixelCrash::Update()
{
	if (mTarget == nullptr)
		return;

	Transform* tf = mTarget->GetComponent<Transform>();
	Player* player = mTarget->GetComponent<Player>();
	Rigidbody* rigid = mTarget->GetComponent<Rigidbody>();
	Vector2 offset = player->GetMoveOffset();
	Transform* pixel_tf = mOwner->GetComponent<Transform>();
	Vector2 pos = tf->GetPos();
	Vector2 pixel_pos = pixel_tf->GetPos();
	Vector2 result_pos = (pos - pixel_pos); //* pixel_tf->GetScale();
	Vector2 scale = pixel_tf->GetScale();

	ESceneType type = SceneManager::GetActiveScene()->GetSceneType();
	switch (type)
	{
	case ESceneType::PlayMap:
		result_pos = (pos - pixel_pos);
		break;
	default:
		result_pos = pos;
		break;
	}
	std::wstring imageKey = mSprite->GetImageKey();
	Image* findImage = Resources::Find<Image>(imageKey);
	if (findImage == nullptr)
	{
		std::wstring imagePath = mSprite->GetPath();
		Resources::Load<Image>(imageKey, imagePath);
	}
	COLORREF color = findImage->GetPixel(result_pos.x, result_pos.y);

	if (color == RGB(255, 0, 255))
	{
		if (Camera::UseTarget() == true)
		{
			tf->SetPos(pos - offset);
			SceneManager::ChagePosGameObjects(-offset);
		}
		else 
		{
			//if (pos.y >= pos.y * scale.y)
			{
				Player* player = mTarget->GetComponent<Player>();
				if (player == nullptr)
					return;
				Character* ch = player->GetActiveCharacter();
				ch->ResetJump();
				ch->ResetDash();
				ch->SetNextAniInfo();
				if (ch->GetParry() == true)
				{
					ch->SetParry(false);
				}
				
				Rigidbody* rigid = mTarget->GetComponent<Rigidbody>();
				rigid->SetGround(true);
				pos.y -= 1;
				tf->SetPos(pos);
			}
		}
		
	}
	else
	{
		if (Camera::UseTarget() == false)
		{
			rigid->SetGround(false);
		}
	}
}

void yeram_client::PixelCrash::Render(HDC hdc)
{
}

void yeram_client::PixelCrash::Release()
{
	if (mTarget != nullptr)
		mTarget.reset();
	Script::Release();
}

void yeram_client::PixelCrash::OnCollisionEnter(Collider* other)
{

}

void yeram_client::PixelCrash::OnCollisionStay(Collider* other)
{
}

void yeram_client::PixelCrash::OnCollisionExit(Collider* other)
{

}

void yeram_client::PixelCrash::SetImage(std::wstring _name, std::wstring _path)
{
	mSprite->SetImage(_name, _path);
}
